// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallActor.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class AProjectileBullet;

UCLASS()
class TESTFIRSTPERSON_API AWallActor : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* meshA;
	UPROPERTY(EditAnywhere, Category = Collider)
		UBoxComponent* m_Collision;
	UPROPERTY(EditAnywhere)
		FVector Size;
	UPROPERTY(EditAnywhere, Category = Bounce)
		FVector BounceOff = FVector(0, 10, 10);
	FVector posistion;
public:	
	// Sets default values for this actor's properties
	AWallActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/// <summary>
	/// Called when it hits somthing
	/// </summary>
	UFUNCTION()
		void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
