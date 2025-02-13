// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_Project2GameMode.h"
#include "CPP_Project2Character.h"
#include "UObject/ConstructorHelpers.h"

ACPP_Project2GameMode::ACPP_Project2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
