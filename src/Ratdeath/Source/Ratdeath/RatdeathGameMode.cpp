// Copyright Epic Games, Inc. All Rights Reserved.

#include "RatdeathGameMode.h"
#include "RatdeathCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARatdeathGameMode::ARatdeathGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
