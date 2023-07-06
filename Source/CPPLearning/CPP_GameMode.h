// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CPP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPLEARNING_API ACPP_GameMode : public AGameMode
{
	GENERATED_BODY()
	ACPP_GameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> BatteryClass;
	UPROPERTY(EditAnywhere) float SpawnLocZ;
	UPROPERTY(EditAnywhere) float SpawnLocMinY;
	UPROPERTY(EditAnywhere) float SpawnLocMinX;
	UPROPERTY(EditAnywhere) float SpawnLocMaxY;
	UPROPERTY(EditAnywhere) float SpawnLocMaxX;

	UFUNCTION(BlueprintCallable) void SpawnBattery();
	
};
