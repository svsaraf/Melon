// Fill out your copyright notice in the Description page of Project Settings.

#include "AniminPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SPlayer.h"

void UAniminPlayer::UpdateAnimationProperties()
{
	APawn* Pawn = TryGetPawnOwner();
	ASPlayer* Char = Cast<ASPlayer>(Pawn);

	

	if (Pawn)
	{

		FVector Vel = Pawn->GetVelocity();
		FVector Forward = Pawn->GetActorForwardVector();
		FVector Right = Pawn->GetActorRightVector();

		bIsZoomed = Char->bWantsToZoom;
		bIsFalling = Pawn->GetMovementComponent()->IsFalling();
		MovementSpeed = Pawn->GetVelocity().Size();
		MovementDirection = FVector::DotProduct(Vel, Right);

		if (Char->bHasWeaponOut)
		{
			bWeaponOut = true;
		}
		else
		{
			bWeaponOut = false;
		}

		if (Char->bIsRealoding)
		{
			bWantsToReload = true;
		}
		if (!Char->bIsRealoding)
		{
			bWantsToReload = false;
		}
	}
}
