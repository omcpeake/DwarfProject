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

#include "DrawDebugHelpers.h"
#define ENABLE_DEBUG_DRAW 1

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADwarfProjectCharacter

ADwarfProjectCharacter::ADwarfProjectCharacter()
{
	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("DwarfProjectCharacter"));
		
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

	
	AttackAnimResetTime = 1.5f;

	

	//Setup checks
	AttackCount = 1;
	CanAttack = true;
	CanDodge = true;
	CanParry = true;
	MovementDisabled = false;
	IsInvincible = false;
	ParryActive = false;
	ParryOnCooldown = false;
	IframeTime = 0.5f;
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
	//If weapon is selected in blueprint then attach it here
	if(HasWeapon==true)
	{ 
		AttachWeapon();
	}	

	//TODO if saves are added then save the current health to that
	CurrentHealth = MaxHealth;
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
		EnhancedInputComponent->BindAction(DodgeRollAction, ETriggerEvent::Started, this, &ADwarfProjectCharacter::DodgeRoll);
			
		//Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ADwarfProjectCharacter::Attack);

		//Spin Attacking
		EnhancedInputComponent->BindAction(SpinAttackAction, ETriggerEvent::Started, this, &ADwarfProjectCharacter::Parry);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADwarfProjectCharacter::Move(const FInputActionValue& Value)
{
	//if movement is disabled then don't move
	if (MovementDisabled == false)
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


void ADwarfProjectCharacter::Attack(const FInputActionValue& Value)
{
	//Putting attack in seperate function so that it can be called classes which dont take input
	MakeAttack();
}

void ADwarfProjectCharacter::MakeAttack()
{
	//Only attack if the player is not already attacking
	if (CanAttack)
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
			//Timer to reset back to attack anim 1 after a certain amount of time of not attacking
			//Reset the attack timer when we start attack
			GetWorld()->GetTimerManager().ClearTimer(AttackAnimResetTimerHandle);
			DashForward(AttackDashVal);
			PlayAnimMontage(CurrentAttack);
			//cant change direction once attack has started
			MovementDisabled = true;

			AttackCount++;

			CanAttack = false;
			CanDodge = false;
			CanParry = false;

			//Start the timer again at the end of the attack
			GetWorld()->GetTimerManager().SetTimer(AttackAnimResetTimerHandle, this, &ADwarfProjectCharacter::ResetAttackCount, AttackAnimResetTime, false);
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Attack Montage!"), *GetNameSafe(this));
		}
	}
}

void ADwarfProjectCharacter::DodgeRoll(const FInputActionValue& Value)
{
	if (CanDodge)
	{
		MovementDisabled = true;
		if (IsValid(DodgeRollMontage))
		{
			PlayAnimMontage(DodgeRollMontage);
		}
		DashForward(DashVal);

		IsInvincible = true;
		CanDodge = false;
		CanAttack = false;
		CanParry = false;
	}
}

void ADwarfProjectCharacter::Parry(const FInputActionValue& Value)
{
	//TODO add add visual feedback for parry
	if (CanParry)
	{		
		if (IsValid(ParryMontage))
		{
			PlayAnimMontage(ParryMontage);
		}
		ParryActive = true;
		CanParry = false;
		CanAttack = false;
		CanDodge = false;

		//Parry has a cooldown
		GetWorld()->GetTimerManager().SetTimer(ParryCooldownTimerHandle, this, &ADwarfProjectCharacter::ParryCooldownEnd, ParryCooldown, false);
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

bool ADwarfProjectCharacter::GetIsHostile()
{
	return IsHostile;
}

UBehaviorTree* ADwarfProjectCharacter::GetBehaviourTree()
{
	return BTAsset;
}


void ADwarfProjectCharacter::RecieveDamage(float Damage, FVector KnockbackDirection, float KnockbackAmount)
{
	//Do not take damage if invincible
	if (!IsInvincible)
	{
		CurrentHealth -= Damage;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" / %f = Health"), CurrentHealth));
		if (CurrentHealth <= 0)
		{
			CurrentHealth = 0;
			Die();
		}
		else
		{
			//If youre not dead get invincibility frames
			IsInvincible = true;
			GetWorld()->GetTimerManager().SetTimer(IFrameTimerHandle, this, &ADwarfProjectCharacter::IFrameEnd, IframeTime, false);

			//And get knocked back
			LaunchCharacter(KnockbackDirection * KnockbackAmount, false, false);
			
		}
	}
	else
	{
		//TODO do stuff, like play a sound or something
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("hehehe")));
	}	
}

void ADwarfProjectCharacter::Die()
{
	//TODO: Play death animation
	Destroy();
}

void ADwarfProjectCharacter::ResetAttackCount()
{
	AttackCount = 1;
}

void ADwarfProjectCharacter::IFrameEnd()
{
	IsInvincible = false;
}

void ADwarfProjectCharacter::DetectHit()
{
	//https://medium.com/@coderfromnineteen/unreal-from-zero-to-hero-10-collision-detection-and-damage-5b9934af1029
	FHitResult HitResult;
	FCollisionQueryParams QueryParams(NAME_None, false, this);
	bool bHit = GetWorld()->SweepSingleByChannel(HitResult,
		GetActorLocation() + GetActorForwardVector() * HitboxOffset,
		GetActorLocation() + GetActorForwardVector() * (AttackRange + HitboxOffset),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		QueryParams);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * (AttackRange + HitboxOffset);
	//FVector Center = GetActorLocation() + GetActorForwardVector() * HitboxOffset + TraceVec * 0.5f;
	FVector Center = GetActorLocation() + GetActorForwardVector() * HitboxOffset;
	float HalfHeight = TraceVec.Size() * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bHit ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, CapsuleRot, DrawColor, false, DebugLifeTime);
#endif

	
	if (bHit)
	{
		if (HitResult.GetActor()->IsA(ADwarfProjectCharacter::StaticClass()))
		{
			
			//UE_LOG(LogTemp, Warning, TEXT("Hit Enemy"));
			ADwarfProjectCharacter* Target = Cast<ADwarfProjectCharacter>(HitResult.GetActor());

			

			//Check if target allignment is the same as ours, dont try to damage them
			if (IsHostile != Target->GetIsHostile())
			{
				if (Target->ParryActive == false)
				{
					//if target is not parrying, deal damage
					Target->RecieveDamage(GetBaseDamage(), GetActorForwardVector(),	AttackKnockback);
				}
				else
				{
					//else take half the damage yourself, idiot
					RecieveDamage(GetBaseDamage()/2, GetActorForwardVector()*-1, 800.0f);
					//TODO - Play sound on parry
				}				
			}			
		}
	}
}

void ADwarfProjectCharacter::DashForward(float DashAmount)
{
	//Moves the target forward by the amount specified
	LaunchCharacter(GetActorForwardVector() * DashAmount, false, false);	
}

void ADwarfProjectCharacter::AttackEnd()
{
	CanAttack = true;
	CanDodge = true;
	MovementDisabled = false;
	//Only enable parry if it is not on cooldown
	if (ParryOnCooldown == false)
	{
		CanParry = true;
	}		
}



void ADwarfProjectCharacter::DodgeEnd()
{
	CanDodge = true;
	CanAttack = true;
	MovementDisabled = false;
	IsInvincible = false;
	//Only enable parry if it is not on cooldown
	if (ParryOnCooldown == false)
	{
		CanParry = true;
	}		
}

void ADwarfProjectCharacter::ParryEnd()
{
	ParryActive = false;
	CanAttack = true;
	CanDodge = true;
	ParryOnCooldown = true;
}

void ADwarfProjectCharacter::ParryCooldownEnd()
{
	ParryOnCooldown = false;
	CanParry = true;
}

bool ADwarfProjectCharacter::GetIsInvincible()
{
	return IsInvincible;
}