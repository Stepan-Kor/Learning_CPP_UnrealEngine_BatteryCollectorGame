// Fill out your copyright notice in the Description page of Project Settings.



#include "MyCPPCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Gameframework/Actor.h"
#include "Kismet/GameplayStatics.h" //для рестарта игры
//#include "Components/PrimitiveComponent.h"

// Sets default values
AMyCPPCharacter::AMyCPPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	bDead = false;
}




// Called when the game starts or when spawned
void AMyCPPCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCPPCharacter::OnBeginOverlap);
	if (Player_HUD_Class != nullptr) {
		Player_HUD_Widget = CreateWidget(GetWorld(), Player_HUD_Class);
		Player_HUD_Widget->AddToViewport();
	}
	
	
}

// Called every frame
void AMyCPPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Life_Time_Left -= DeltaTime / Life_Time_Starting;
	if (Life_Time_Left <= 0 && !bDead) {
		bDead = true;
		
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		if (AMyCPPCharacter::IsPlayerControlled()) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player controlled - Gona restart"));
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyCPPCharacter::RestartLevel,3.0f, false);
		}
		else { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Not player controlled")); }
	}

}

// Called to bind functionality to input
void AMyCPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCPPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCPPCharacter::MoveRight);
}

void AMyCPPCharacter::MoveForward(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void AMyCPPCharacter::MoveRight(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}


void AMyCPPCharacter::OnBeginOverlap(UPrimitiveComponent* HitComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	//printf(OtherActor::GetFName);
	if (OtherActor->ActorHasTag("Recharge")) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with"));
		OtherActor->Destroy();
		Life_Time_Left += 0.2;
	}
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Battery collected"));
}

void AMyCPPCharacter::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
