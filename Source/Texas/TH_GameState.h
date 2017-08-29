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

UCLASS(BlueprintType)
class TEXAS_API ATH_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void PassTurn();

	UFUNCTION(BlueprintCallable)
	UDeck* GetDeck();


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



	void GameInit();

protected:
	virtual void BeginPlay() override;

	static const int MAXPLAYER = 10;
	
	
	UDeck* deck;
	UCard* flopCard[3];
	UCard* turnCard;
	UCard* riverCard;
	Action action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int turn;
	
	int sb;
	int bb;
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