// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Classes/Camera/CameraComponent.h"
#include "TH_GameState.h"
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

	AController *Controller;
	
	FVector2D CameraInput;
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool acted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool is_tick_start;

	void Call();
	void Fold();
	void Raise();
	void Check();

	UFUNCTION(BlueprintCallable)
	static APlayerController* GetPlayerController(APlayerState* player_state);
	
	int tick;

	int turn;

	ATH_GameState* MyGameState;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
	bool GetActed();

	UFUNCTION(BlueprintCallable)		
	void SetActed(bool act);
};
