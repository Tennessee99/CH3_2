// Fill out your copyright notice in the Description page of Project Settings.


#include "CH3_2/Game/MPGameModeBase.h"
#include "CH3_2/Controller/MPController.h"
#include "CH3_2/Pawn/MyPawn.h"


AMPGameModeBase::AMPGameModeBase()
{
	PlayerControllerClass = AMPController::StaticClass();
	DefaultPawnClass = AMyPawn::StaticClass();

}