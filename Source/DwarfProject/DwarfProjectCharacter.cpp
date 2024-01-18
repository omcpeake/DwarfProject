// Copyright Epic Games, Inc. All Rights Reserved.

#include "DwarfProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADwarfProjectCharacter

ADwarfProjectCharacter::ADwarfProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("DwarfProjectCharacter"));
}

void ADwarfProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	if(HasWeapon==true)
	{ 
		AttachWeapon();
	}
	//TODO if saves are added then save the current health to that
	CurrentHealth = MaxHealth;
	
	AttackCount = 1;

}



//////////////////////////////////////////////////////////////////////////
// Input

void ADwarfProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADwarfProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADwarfProjectCharacter::Look);

		//Dashing
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ADwarfProjectCharacter::Dash);

		//Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ADwarfProjectCharacter::Attack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADwarfProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADwarfProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADwarfProjectCharacter::Dash(const FInputActionValue& Value)
{		
}

void ADwarfProjectCharacter::Attack(const FInputActionValue& Value)
{
	// use attack 1 by default
	UAnimMontage* CurrentAttack = Attack1Montage;

	if (AttackCount == 2)
	{
		CurrentAttack = Attack2Montage;
	}
	else if (AttackCount == 3)
	{
		CurrentAttack = Attack3Montage;
		AttackCount = 0;
	}
	//verify that the attack is not null
	if (IsValid(CurrentAttack))
	{
		PlayAnimMontage(CurrentAttack);
		AttackCount++;
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Attack Montage!"), *GetNameSafe(this));
	}	
	
}

void ADwarfProjectCharacter::AttachWeapon()
{
	// You should ensure the Actor class is valid before spawning, otherwise you'll most likely crash the application!
	if (IsValid(MyActorClass))
	{
		// We need a pointer to the level we want to spawn the Actor in. You can get the persistent level from any Actor or Component with GetWorld()
		UWorld* MyLevel = GetWorld();

		// You should ensure the level is valid before spawning, or you could crash the engine! This is important if your spawn code could run from the Editor by any reason.
		if (IsValid(MyLevel))
		{
			// You can determine the spawned Actor's initial location, rotation and scale.
			// Here we're just setting it to the spawner's transform.
			// NOTE: depending on your Actor settings, this could prevent spawning if the location is obstructed! //FTransform SpawnTransform = GetActorTransform();
			FTransform SocketTransform = GetMesh()->GetSocketTransform(WeaponSocketName, RTS_World);

			// Use UWorld->SpawnActor<>() to spawn. It will return a cast pointer of the Actor type you specified.
			//  There's several variants of the function that allow extra customization. Here we just pass the Actor class for reflection support, and the transform.
			AWeaponBase* SpawnedActor = MyLevel->SpawnActor<AWeaponBase>(MyActorClass, SocketTransform);

			// You should validate the actor pointer before accessing it in case the Spawn failed.
			if (IsValid(SpawnedActor))
			{
				UE_LOG(LogTemp, Log, TEXT("Spawned successfully! New Actor: %s"), *SpawnedActor->GetName());
				SpawnedActor->SetOwner(this);
				SpawnedActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
				//SpawnedActor->SetActorEnableCollision(false);
				SpawnedActor->UpdateWeaponMesh(WeaponMesh);

			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Spawn failed!"));
			}				
		}
	}	
}

float ADwarfProjectCharacter::GetBaseDamage()
{
	return BaseDamage;
}


void ADwarfProjectCharacter::RecieveDamage(float Damage)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		Die();
	}
}

void ADwarfProjectCharacter::Die()
{
	//TODO: Play death animation
	Destroy();
}

void ADwarfProjectCharacter::DetectHit()
{
	//UKismetSystemLibrary::SphereTraceSingleForObjects
}

void ADwarfProjectCharacter::DashForward(float DashAmount)
{
	LaunchCharacter(GetActorForwardVector() * DashAmount, false, false);
	
}


