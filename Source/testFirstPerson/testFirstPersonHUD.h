// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "testFirstPersonHUD.generated.h"

UCLASS()
class AtestFirstPersonHUD : public AHUD
{
	GENERATED_BODY()

public:
	AtestFirstPersonHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

