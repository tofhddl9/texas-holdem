// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Classes/Camera/CameraComponent.h"
#include "TH_Pawn.generated.h"

UCLASS()
class TEXAS_API ATH_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATH_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UCameraComponent *PlayerCamera;
	USceneComponent *VisibleComponent;

	FVector2D CameraInput;
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
