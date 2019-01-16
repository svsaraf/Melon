// Fill out your copyright notice in the Description page of Project Settings.

#include "SPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SWeapon.h"
#include "Engine/World.h"

// Sets default values
ASPlayer::ASPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);



	BackSocket = "BackSocket";
	HandSocket = "HandSocket";

	ZoomedFOV = 65.f;
	ZoomInterpSpeed = 20.f;
	ZoomedMultiplyer = 2.3;

	SprintMultipler = 1.6;

}

// Called when the game starts or when spawned
void ASPlayer::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV = CameraComp->FieldOfView;
	bHasWeaponOut = false;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	

	CurrentWeapon = GetWorld()->SpawnActor<ASWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	
	if (CurrentWeapon)
	{

		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);
		CurrentWeapon->SetOwner(this);
	}


}

void ASPlayer::MoveForward(float Value)
{

	AddMovementInput(GetActorForwardVector() * Value);
}

void ASPlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ASPlayer::BeginCrouch()
{
	Crouch();
}

void ASPlayer::EndCrouch()
{
	UnCrouch();
}

void ASPlayer::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintMultipler;
}

void ASPlayer::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintMultipler;
}

void ASPlayer::Fire()
{
	if (CurrentWeapon&&bHasWeaponOut)
	{
		CurrentWeapon->Fire();
	}
}

void ASPlayer::Reload()
{
	bIsRealoding = true;
}



void ASPlayer::ToggleWeaponOut()
{
	if (bHasWeaponOut)
	{
		bHasWeaponOut = false;
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);
	}
	else
	{
		bHasWeaponOut = true;
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
	}
}




void ASPlayer::BeginZoom()
{
	bWantsToZoom = true;
	GetCharacterMovement()->MaxWalkSpeed /= ZoomedMultiplyer;

}

void ASPlayer::EndZoom()
{
	bWantsToZoom = false;
	GetCharacterMovement()->MaxWalkSpeed *= ZoomedMultiplyer;
}

// Called every frame
void ASPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFov = bWantsToZoom ? ZoomedFOV : DefaultFOV;
	float NewFov = FMath::FInterpTo(CameraComp->FieldOfView, TargetFov, DeltaTime, ZoomInterpSpeed);
	CameraComp->SetFieldOfView(NewFov);
	//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, FString::Printf((bHasWeaponOut ? "True" : "False") ));
}

// Called to bind functionality to input
void ASPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASPlayer::AddControllerYawInput);


	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ASPlayer::Jump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASPlayer::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASPlayer::EndCrouch);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ASPlayer::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ASPlayer::EndZoom);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASPlayer::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASPlayer::StopSprint);
	PlayerInputComponent->BindAction("PullOut", IE_Pressed, this, &ASPlayer::ToggleWeaponOut);

	

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASPlayer::Fire);
}

FVector ASPlayer::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}


