// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestOwnersTableGameMode.h"
#include "TestOwnersTableHUD.h"
#include "TestOwnersTableCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestOwnersTableGameMode::ATestOwnersTableGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestOwnersTableHUD::StaticClass();
}
