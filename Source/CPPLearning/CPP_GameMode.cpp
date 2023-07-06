// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameMode.h"
#include "GameFramework/Actor.h"

ACPP_GameMode::ACPP_GameMode() {
	PrimaryActorTick.bCanEverTick = true;
}


void ACPP_GameMode::BeginPlay() {
	Super::BeginPlay();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACPP_GameMode::SpawnBattery,
		3.0f, true);
}

void ACPP_GameMode::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}


void ACPP_GameMode::SpawnBattery()
{/*
	FVector SpawnLocation = FVector(0,0,0);
	FVector SpawnLocation = FVector(FMath::RandRange(SpawnLocMinX, SpawnLocMaxX),
		FMath::RandRange(SpawnLocMinY, SpawnLocMaxY),
		SpawnLocZ);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	//TSubclassOf<AActor> awd;
	GetWorld()->SpawnActor<AActor> (BatteryClass, FVector(0, 0, 1000), FRotator(0.0f, 0.0f, 0.0f));*/
	GetWorld()->SpawnActor<AActor>(BatteryClass,
		FVector(FMath::RandRange(SpawnLocMinX, SpawnLocMaxX),
			FMath::RandRange(SpawnLocMinY, SpawnLocMaxY),
			SpawnLocZ),
		FRotator(0.0f, 0.0f, 0.0f)
	);
}
