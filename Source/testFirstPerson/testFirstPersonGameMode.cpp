// Copyright Epic Games, Inc. All Rights Reserved.

#include "testFirstPersonGameMode.h"
#include "testFirstPersonHUD.h"
#include "testFirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AtestFirstPersonGameMode::AtestFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AtestFirstPersonHUD::StaticClass();
}
