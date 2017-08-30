// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Deck.h"
#include "TH_GameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class Action : uint8
{
	CALL UMETA(DisplayName = "CALL"),
	FOLD UMETA(DisplayName = "FOLD"),
	RAISE UMETA(DisplayName = "RAISE"),
	CHECK UMETA(DisplayName = "CHECK")
};

UENUM(BlueprintType)
enum class TurnState : uint8
{
	PREFLOP UMETA(DisplayName = "PREFLOP"),
	FLOP UMETA(DisplayName = "FLOP"),
	TURN UMETA(DisplayName = "TURN"),
	RIVER UMETA(DisplayName = "RIVER")
};

UCLASS(BlueprintType)
class TEXAS_API ATH_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void PassTurn();

	UFUNCTION(BlueprintCallable)
	UDeck* GetDeck();

	TurnState turnState;

	int GetNumTotalPlayer();
	void SetNumTotalPlayer(int num);

	int GetNumPlayerActed();
	void SetNumPlayerActed(int num);
	
	int GetPot();
	void SetPot(int chips);

	int GetBiggestBet();
	void SetBiggestBet(int chips);

	int GetPlayerBet(int turn);
	void SetPlayerBet(int turn, int money);

	void CheckGame();

	void GameInit();

protected:
	virtual void BeginPlay() override;

	static const int MAXPLAYER = 10;
	
	
	UDeck* deck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCard* flopCard1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCard* flopCard2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCard* flopCard3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCard* turnCard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCard* riverCard;
	Action action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int turn;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int sb;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int bb;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int dealer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int numTotalPlayer;
	int numActivePlayer;
	int numPlayerActed;

	int playerBet[MAXPLAYER];

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int bigBet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int smallBet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int pot;

	int biggestBet;
};