// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "WeaponBase.h"
#include "AlertRadius.h"
#include "EGameStates.h"

#include "DwarfProjectCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UAnimMontage;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ADwarfProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	/** Dash Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DodgeRollAction;
	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;
	/** Parry Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ParryAction;
	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

private:

	

	//Custom Properties
	bool CanAttack;
	bool CanDodge;
	bool CanParry;
	bool ParryActive;
	bool CanSprint;
	bool IsSprinting;
	bool IsDead;

	FTimerHandle ParryCooldownTimerHandle;
	FTimerHandle IFrameTimerHandle;
	float IframeTime;
	bool ParryOnCooldown;
	bool MovementDisabled;
	bool IsInvincible;
	float ParryKnockback;

	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	float WalkSpeed;
	float SprintSpeed;

	//UDwarfGameInstance* GameInstance;
	
	//ConstructorHelpers::FClassFinder<UUserWidget> WBPClassFinder(TEXT("/Game/UI/WB_UI"));


public:
	

	//Unit Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	bool IsHostile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float AttackKnockback;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float AttackDashVal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float AttackRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float HitboxOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float ParryCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float DashVal;
	

	//Attack Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack1Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack2Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack3Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DodgeRollMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ParryMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ParryStunMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;
	FTimerHandle AttackAnimResetTimerHandle;
	float AttackAnimResetTime;

	//Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	bool HasWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName WeaponSocketName;
	

	// Use TSubclassOf to determine the base type of the Actor you want to spawn.
	// You can expose the variable to the editor with UPROPERTY()
	// You can also get the class type of any object with its StaticClass() function
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeaponBase> MyActorClass = AWeaponBase::StaticClass();

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AAlertRadius> AlertRadiusClass = AAlertRadius::StaticClass();

	class AAlertRadius* AlertRadius;

	/////////////////////////////////////UI and HUD
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UDwarfHud> PlayerHUDClass;
	UPROPERTY()
	class UDwarfHud* PlayerHUD;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UMainMenu> MainMenuClass;
	UPROPERTY()
	class UMainMenu* MainMenu;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UPauseMenu> PauseMenuClass;
	UPROPERTY()
	class UPauseMenu* PauseMenu;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UDeathScreen> DeathScreenClass;
	UPROPERTY()
	class UDeathScreen* DeathScreen;

	/////////////////////////////////////////// AUDIO
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* SwingSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* InjuredSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* ParrySound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* FootstepSound;

	


	///////////////////////////////////////////AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool HasAI;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BTAsset;


protected:
	float CurrentHealth;
	//counts the number of attacks for selecting animation
	int32 AttackCount;

public:
	ADwarfProjectCharacter();	

protected:
	void SetupPlayer();
	void EnableMainMenu();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void DodgeRoll(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void Parry(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);

	void Pause(const FInputActionValue& Value);


	void AttachWeapon();
	
	void ResetAttackCount();

	void IFrameEnd();

	void SetupStimulusSource();

	void SetupAlertRadius();

	bool HandleDamage(float Damage);				

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	//UFunctions
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetBaseDamage();
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void RecieveDamage(float Damage, FVector KnockbackDirection, float KnockbackAmount);
	void RecieveDamage(float Damage);
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void RecieveHealth(float Healing);

	UFUNCTION(BlueprintCallable, Category = "Util")
	void DetectHit();
	UFUNCTION(BlueprintCallable, Category = "Util")
	void DashForward(float DashAmount);
	UFUNCTION(BlueprintCallable, Category = "Util")
	void Die();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackEnd();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void MakeAttack(bool Rand);
	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void DodgeEnd();
	UFUNCTION(BlueprintCallable, Category = "Parry")
	void ParryEnd();
	UFUNCTION(BlueprintCallable, Category = "Parry")
	void ParryCooldownEnd();
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayFootstep();
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySwingSound();


	UFUNCTION(BlueprintCallable, Category = "UnitInfo")
	bool GetIsInvincible();
	UFUNCTION(BlueprintCallable, Category = "UnitInfo")
	bool GetIsHostile();
	UFUNCTION(BlueprintCallable, Category = "UnitInfo")
	bool GetHasAI();
	UFUNCTION(BlueprintCallable, Category = "UnitInfo")
	bool GetIsSprinting();
	UFUNCTION(BlueprintCallable, Category = "UnitInfo")
	bool GetCanAttack();
	UFUNCTION(BlueprintCallable, Category = "AI")
	UBehaviorTree* GetBehaviourTree();
	UFUNCTION(BlueprintCallable, Category = "AI")
	AAlertRadius* GetAlertRadius();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void EnableDeathScreen();

	UFUNCTION(BlueprintCallable, Category = "UI")
	UDwarfHud* GetPlayerHUD();

};

