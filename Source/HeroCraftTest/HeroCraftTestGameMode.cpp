// Copyright Epic Games, Inc. All Rights Reserved.

#include "HeroCraftTestGameMode.h"
#include "HeroCraftTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHeroCraftTestGameMode::AHeroCraftTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
