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

	void PreFlop();
	void GameInit();

protected:
	virtual void BeginPlay() override;
	UDeck* deck;
	UCard* flopCard[3];
	UCard* turnCard;
	UCard* riverCard;
	int8 turn;
	int8 sb;
	int8 bb;
	int8 dealer;
	int8 numTotalPlayer;
	int8 numActivePlayer;
	int8 numPlayerActed;
	int bigBet;
	int smallBet;
	int pot;


	
};
