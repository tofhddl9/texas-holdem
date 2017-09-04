// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Card.h"
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

	int GetTurn();

	UFUNCTION(BlueprintCallable)
	UDeck* GetDeck();

	UFUNCTION(BlueprintCallable)
	UCard* GetPlayerHands(int player, int seq);

	int GetNumTotalPlayer();
	void SetNumTotalPlayer(int num);
	
	int GetNumPlayerActed();
	void SetNumPlayerActed(int num);

	int GetNumActivePlayer();
	void SetNumActivePlayer(int num);
	
	int GetPot();
	void SetPot(int chips);

	int GetBiggestBet();
	void SetBiggestBet(int chips);

	UFUNCTION(BlueprintCallable)
	int GetPlayerBet(int turn);
	void SetPlayerBet(int turn, int money);

	UFUNCTION(BlueprintCallable)
	int GetPlayerBankroll(int player);
	void SetPlayerBankroll(int player,int money);

	bool GetisPlaying(int id);

	void CheckGame();

	void GameInit();
	void PreFlop();
	void SortPlayerHands();
	void ScoringHands();
	void AnalyzeHands();
	int DetermineWinner();
	void ApplyGameResult(int winner);
	void SetNewGame();

protected:
	virtual void BeginPlay() override;

	static const int MAXPLAYER = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isHoleCardSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TurnState turnState;
	UDeck* deck;
	UCard* playerHands[MAXPLAYER][7];
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
	//Action action;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int pot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int bigBet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int smallBet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int biggestBet;
	int playerBankroll[MAXPLAYER];
	int playerBet[MAXPLAYER];
	int rankScore[MAXPLAYER];
	bool isNewPlayer[MAXPLAYER];
	bool isPlaying[MAXPLAYER];
	int winner;
};