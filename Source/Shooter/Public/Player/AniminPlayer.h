// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AniminPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UAniminPlayer : public UAnimInstance
{
	GENERATED_BODY()

protected:
	/*True means that we're currently in air - or falling*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsFalling;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsZoomed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bWantsToReload;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bWeaponOut;



	/*Holds the current speed of our character*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MovementDirection;

	/*Updates the above properties*/
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties();

};
