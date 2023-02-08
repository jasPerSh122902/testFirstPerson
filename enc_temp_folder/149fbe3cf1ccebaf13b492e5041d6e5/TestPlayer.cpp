// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayer.h"
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/InputSettings.h>
#include <Components/CapsuleComponent.h>
#include <testFirstPerson/BulletActor.h>
#include <testFirstPerson/TraceComponent.h>

// Sets default values
ATestPlayer::ATestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(CamLocation); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	// Show the controles
	GEngine->AddOnScreenDebugMessage(1, 1000000.0f, FColor::Emerald, "Press Left mouse to shoot projectile\nPress Right mouse to shoot ray\nTo Move WASD");
}

void ATestPlayer::OnFire()
{
	// Get the world
	UWorld* World = GetWorld();
	// Gets the rotation
	FRotator SpawnRotation = GetControlRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	FVector SpawnLocation = ((MeshA != nullptr) ? MeshA->GetComponentLocation() : GetActorLocation());
	// Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	ActorSpawnParams.Owner = this;
	// spawn the projectile at the muzzle
	World->SpawnActor<ABulletActor>(SpawnLocation, SpawnRotation, ActorSpawnParams);

}

void ATestPlayer::OnFireRay()
{
	//TraceComp->GetTraceBullet(100,FColor::Orange,false,1.5f,0,5.0f);
	TraceComp->DoTrace(GetActorLocation(),FindComponentByClass<UCameraComponent>()->GetComponentRotation(), GetWorld());

}

void ATestPlayer::MoveX(float value)
{
	if (value != 0.0f)// Add movement in that direction
		AddMovementInput(GetActorRightVector(), value);

}

void ATestPlayer::MoveY(float value)
{
	if (value != 0.0f)// Add movement in that direction
		AddMovementInput(GetActorForwardVector(), value);

}

// Called every frame
void ATestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/// <summary>
	/// Binds the jump to Space
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	/// <summary>
	/// Binds the axis movement to the WASD keys
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestPlayer::MoveY);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestPlayer::MoveX);
	/// <summary>
	/// Bind fire event
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATestPlayer::OnFire);
	PlayerInputComponent->BindAction("RayCast", IE_Pressed, this, &ATestPlayer::OnFireRay);
	/// <summary>
	/// Binds the rotation of the charactor to the mouse
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

