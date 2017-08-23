// Fill out your copyright notice in the Description page of Project Settings.

#include "TH_Pawn.h"

// Sets default values
ATH_Pawn::ATH_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	PlayerCamera->SetupAttachment(RootComponent);
	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATH_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATH_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, 0.0f);
		SetActorRotation(NewRotation);
	}
}

// Called to bind functionality to input
void ATH_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CameraPitch", this, &ATH_Pawn::PitchCamera);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ATH_Pawn::YawCamera);
	
}

void ATH_Pawn::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ATH_Pawn::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}