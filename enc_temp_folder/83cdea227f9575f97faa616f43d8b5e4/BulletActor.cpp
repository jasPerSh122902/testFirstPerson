// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Engine.h>
#include <testFirstPerson/TestPlayer.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
// Sets default values
ABulletActor::ABulletActor()
{
	MakeCollision();
	MakeMesh();
	MakeMovement();
	// Die after 3 secomponents
	InitialLifeSpan = 3.0f;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABulletActor::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0") && (OtherActor != nullptr))
	{
		if (OtherActor != GetOwner())
		{
			// Get the larget location
			FVector targetForward = OtherActor->GetActorForwardVector();
			FVector targetLocation = OtherActor->GetActorLocation();
			// Gets the direction Vector
			FVector direction = (startLocation - targetLocation);
			// This is for ricishay off of a object.
			//if (FVector::DotProduct(targetLocation, startLocation) <= 1)
				Movement->AddRadialImpulse(this->GetActorLocation(), 10,(direction.Normalize() * 300000), ERadialImpulseFalloff::RIF_Linear, true);//Movement->AddForce(-targetForward * (direction.Normalize() * (BounceOff * 300000)));
			///else
				//Movement->AddForce((direction.Normalize() * (BounceOff * 3000)));
		}
	}

}

void ABulletActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0") && (OtherActor != nullptr))
	{
		if (OtherActor != GetOwner())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap End");
			//GEngine->ClearOnScreenDebugMessages();
			
		}
	}

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();

}

void ABulletActor::MakeCollision()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Circle"));
	// Set the radius
	Collision->InitSphereRadius(5.0f);
	Collision->BodyInstance.SetCollisionProfileName("Trigger");
	// Makes it so it has collision
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnOverLapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABulletActor::OnOverlapEnd);
	// Makes player unable to walk on object
	Collision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Collision->CanCharacterStepUpOn = ECB_No;

	// Makes the collision not trigger on pawns
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	// Allow triggers to work
	Collision->SetGenerateOverlapEvents(true);
	// Makes the root comp to the collider
	RootComponent = Collision;
}


void ABulletActor::MakeMovement()
{
	// Makes a default movement
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Walk"));
	Movement->UpdatedComponent = Collision;
	// Set the movements speed
	Movement->InitialSpeed = 3000.f;
	Movement->MaxSpeed = 3000.f;
	// Allows for rotations
	Movement->bRotationFollowsVelocity = true;
	// Allows for bounce
	Movement->bShouldBounce = true;
	Movement->Bounciness = 0.3f;
}

void ABulletActor::MakeMesh()
{
	// Make a default sub object of mesh
	MeshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	// Allow all to see it
	MeshA->SetOnlyOwnerSee(false);
	// Attach it to something
	MeshA->SetupAttachment(Collision);
	// Shadows
	MeshA->bCastDynamicShadow = false;
	// Case a shadow
	MeshA->CastShadow = false;
	// Set the place it is in
	MeshA->SetRelativeLocation(Collision->GetComponentLocation());
	// Set the mesh to a preset assest
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	// Make the mesh asset in to a pointer of asset
	UStaticMesh* Asset = MeshAsset.Object;
	// Set the staticMesh
	MeshA->SetStaticMesh(Asset);

}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}