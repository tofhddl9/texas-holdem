// Fill out your copyright notice in the Description page of Project Settings.

#include "TH_GameState.h"

void ATH_GameState::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-10, 5.f, FColor::Yellow, FString::Printf(TEXT("turn: %d"), turn));
	GameInit();
	//PreFlop();
}

void ATH_GameState::PassTurn()
{
	turn = (turn+1) % numTotalPlayer;
	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("turn: %d"), turn));
}

UDeck* ATH_GameState::GetDeck()
{
	return deck;
}

void ATH_GameState::GameInit()
{
	deck = UDeck::CreateDeck();
	deck->Init();// game의 상위 단계에서 한 번 하면 됨.
	deck->Shuffle();
	dealer = 0; // game의 상위 단계에서 한 번 하면 됨.
	sb = dealer + 1;//
	bb = sb + 1;//
	numActivePlayer = 2;//
	numTotalPlayer = 2;//
	dealer = (dealer++) % numTotalPlayer;
	sb = (sb+1) % numTotalPlayer;
	bb = (bb+1) % numTotalPlayer;
	turn = bb;
	bigBet = 2;//
	smallBet = bigBet / 2;
	pot = bigBet + smallBet;//
}


/*void ATH_GameState::PreFlop()
{
	while (numActivePlayer != numPlayerActed) {
		turn = (turn + 1) % numTotalPlayer;
		//EnableAction(turn);
		//action = GetAction();
		//DisableAction(turn);
		switch(action)
		{
			case Action::FOLD:numActivePlayer--;break;
			case Action::CALL:numPlayerActed++;break;
			case Action::RAISE:break;
			case Action::CHECK:break;
		}
	}
}*/