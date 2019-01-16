// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPlayer.generated.h"


class UCameraComponent;
class USpringArmComponent;
class ASWeapon;


//class UCharacterMovementComponent;
UCLASS()
class SHOOTER_API ASPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Movement
	void MoveForward(float Value);
	void MoveRight(float Value);
	void BeginCrouch();
	void EndCrouch();
	void StartSprint();
	void StopSprint();
	void Fire();
	void Reload();
	void Holster();



	//Camera stuff
	void BeginZoom();
	void EndZoom();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	//UCharacterMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float SprintMultipler;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float ZoomedFOV;


	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 100.0))
		float ZoomInterpSpeed;

	float DefaultFOV;
	float ZoomedMultiplyer;

	ASWeapon* CurrentWeapon;
	ASWeapon* StoreWeapon;

	

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
		FName WeaponAttachmentSocketBack;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<ASWeapon> StarterWeaponClass;

	void ToggleWeaponOut();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	bool bWantsToZoom;
	bool bSprinting;
	bool bIsRealoding;
	bool bHasWeaponOut;
	//bool bIsStoringWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "ObjectInteraction")
		float MaxUseDistance;



	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
		FName BackSocket;
	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
		FName HandSocket;


	class ASWeapon* PreviousWeapon;

};
