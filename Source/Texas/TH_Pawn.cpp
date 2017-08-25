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
	acted = false;
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
	PlayerInputComponent->BindAction("ActionCall", IE_Pressed, this, &ATH_Pawn::Call);
	PlayerInputComponent->BindAction("ActionFold", IE_Pressed, this, &ATH_Pawn::Fold);
	PlayerInputComponent->BindAction("ActionRaise", IE_Pressed, this, &ATH_Pawn::Raise);
	PlayerInputComponent->BindAction("ActionCheck", IE_Pressed, this, &ATH_Pawn::Check);
}

void ATH_Pawn::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ATH_Pawn::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ATH_Pawn::Call()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Call");
	acted = true;
}

void ATH_Pawn::Fold()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Fold");
	acted = true;
}

void ATH_Pawn::Raise()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Raise");
	acted = true;
}

void ATH_Pawn::Check()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Check");
	acted = true;
}

bool ATH_Pawn::GetActed()
{
	return acted;
}

void ATH_Pawn::SetActed(bool act)
{
	acted = act;
}