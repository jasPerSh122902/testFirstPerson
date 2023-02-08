// Fill out your copyright notice in the Description page of Project Settings.


#include "WallActor.h"
#include <Components/BoxComponent.h>
// Sets default values
AWallActor::AWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	m_Collision->InitBoxExtent(Size);
	m_Collision->BodyInstance.SetCollisionProfileName("Trigger");
	m_Collision->OnComponentBeginOverlap.AddDynamic(this, &AWallActor::OnOverLapBegin);
	m_Collision->OnComponentEndOverlap.AddDynamic(this, &AWallActor::OnOverlapEnd);
	m_Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	m_Collision->SetupAttachment(RootComponent);
	m_Collision->SetGenerateOverlapEvents(true);
	UpdateOverlapsMethodDuringLevelStreaming;
	// Object 1
	meshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	meshA->CastShadow = false;
	meshA->SetupAttachment(m_Collision);
	meshA->SetRelativeLocation(m_Collision->GetComponentLocation());
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAssest(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	UStaticMesh* Asset = MeshAssest.Object;
	meshA->SetStaticMesh(Asset);
}

// Called when the game starts or when spawned
void AWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallActor::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != this) && (OtherActor != nullptr))
	{
		
	}
}

void AWallActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}