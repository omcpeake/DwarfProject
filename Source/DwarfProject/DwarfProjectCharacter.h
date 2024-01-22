// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "WeaponBase.h"
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

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Dash Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;


	//Custom Properties
	//Unit Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

	//Attack Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack1Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack2Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Attack3Montage;

	//Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	bool HasWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName WeaponSocketName;

	//Dash Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash", meta = (AllowPrivateAccess = "true"))
	float DashVal;

	// Use TSubclassOf to determine the base type of the Actor you want to spawn.
	// You can expose the variable to the editor with UPROPERTY()
	// You can also get the class type of any object with its StaticClass() function
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeaponBase> MyActorClass = AWeaponBase::StaticClass();

protected:
	float CurrentHealth;
	//counts the number of attacks for selecting animation
	int32 AttackCount;

public:
	ADwarfProjectCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Dash(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void AttachWeapon();

	void Die();
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	//UFunctions
	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetBaseDamage();
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void RecieveDamage(float Damage);
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void DetectHit();
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void DashForward(float DashAmount);


};

