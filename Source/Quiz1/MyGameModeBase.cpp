// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MyPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultPawnClass = AMyPawn::StaticClass();
}

void AMyGameModeBase::Tick(float v)
{
	Super::Tick(v);
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
