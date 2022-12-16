// Copyright Epic Games, Inc. All Rights Reserved.

#include "CampAdventureGameMode.h"
#include "CampAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACampAdventureGameMode::ACampAdventureGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
