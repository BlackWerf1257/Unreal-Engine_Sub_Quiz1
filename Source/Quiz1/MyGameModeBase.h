// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPawn.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class QUIZ1_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:	
	virtual void BeginPlay() override;

public:
	AMyGameModeBase();
	virtual void Tick(float v) override;
};
