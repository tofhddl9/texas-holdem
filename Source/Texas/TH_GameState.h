// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Deck.h"
#include "TH_GameState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TEXAS_API ATH_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UDeck* GetDeck();

protected:
	virtual void BeginPlay() override;
	UDeck* deck;
	
};
