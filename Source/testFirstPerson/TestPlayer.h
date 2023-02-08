// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestPlayer.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class ABulletActor;
class UTraceComponent;

UCLASS()
class TESTFIRSTPERSON_API ATestPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = " Mesh ")
	USkeletalMeshComponent* MeshA;
	/// <summary>
	/// Camera
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = " Camera ")
	UCameraComponent* CameraComponent;
public:
	// Sets default values for this character's properties
	ATestPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/// <summary>
	/// Fires the bullet that is a projectle
	/// </summary>
	void OnFire();
	/// <summary>
	/// Fires the ray 
	/// </summary>
	void OnFireRay();
	/// <summary>
	/// Move on the X
	/// </summary>
	/// <param name="value">is the input</param>
	void MoveX(float value);
	/// <summary>
	/// Move on the Y
	/// </summary>
	/// <param name="value">is the input</param>
	void MoveY(float value);
	/// <summary>
	///  Called to bind functionality to input
	/// </summary>
	/// <param name="PlayerInputComponent">input</param>
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		float BaseTurnRate;
	UPROPERTY(EditAnywhere)
		FVector OffSet;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		ABulletActor* ProjectileClass;
	UPROPERTY(EditAnywhere)
		UTraceComponent* TraceComp;
	UPROPERTY(VisibleAnywhere)
		float BaseLookUpRate;
	UPROPERTY(VisibleAnywhere, Category = "Camera location")
		FVector CamLocation;

};
