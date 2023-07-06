// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BluePrint/UserWidget.h"



#include "MyCPPCharacter.generated.h"

UCLASS()
class CPPLEARNING_API AMyCPPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCPPCharacter();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	bool bDead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Life_Time_Left = 1.0;
	UPROPERTY(EditAnywhere)		float Life_Time_Starting =6;
	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bfromSweep, const FHitResult & SweepResult);
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Player_HUD_Class;
	UUserWidget* Player_HUD_Widget;
	UFUNCTION(BlueprintCallable)	 virtual void RestartLevel();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
