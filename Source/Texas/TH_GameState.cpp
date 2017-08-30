// Fill out your copyright notice in the Description page of Project Settings.

#include "TH_GameState.h"

void ATH_GameState::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-10, 5.f, FColor::Yellow, FString::Printf(TEXT("turn: %d"), turn));
	GameInit();
	
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
	deck->Init();// game�� ���� �ܰ迡�� �� �� �ϸ� ��.
	deck->Shuffle();
	turnState = TurnState::PREFLOP;
	dealer = 0; // game�� ���� �ܰ迡�� �� �� �ϸ� ��.
	sb = dealer + 1;//
	bb = sb + 1;//
	numActivePlayer = 2;//
	numTotalPlayer = 2;//
	numPlayerActed = 0;
	dealer = (dealer++) % numTotalPlayer;
	sb = (sb+1) % numTotalPlayer;
	bb = (bb+1) % numTotalPlayer;
	turn = (bb+1) % numTotalPlayer;
	bigBet = 2;//
	smallBet = bigBet / 2;
	pot = bigBet + smallBet;//
	biggestBet = bigBet;
	for (int i = 0; i < numTotalPlayer; ++i) {
		playerBet[i] = 0;
	}
	playerBet[bb] = bigBet;
	playerBet[sb] = smallBet;
}

void ATH_GameState::CheckGame()
{
	if (numPlayerActed == numActivePlayer) {
		switch (turnState)
		{
		case TurnState::PREFLOP :
			flopCard1 = deck->Draw();
			flopCard2 = deck->Draw();
			flopCard3 = deck->Draw();
			numPlayerActed = 0;
			turnState = TurnState::FLOP;
			break;
		case TurnState::FLOP :
			turnCard = deck->Draw();
			numPlayerActed = 0;
			turnState = TurnState::RIVER;
			break;
		case TurnState::RIVER :
			riverCard = deck->Draw();
			break;
		}
	}
}

int ATH_GameState::GetNumTotalPlayer()
{
	return numTotalPlayer;
}

void ATH_GameState::SetNumTotalPlayer(int num)
{
	numTotalPlayer = num;
}

int ATH_GameState::GetNumPlayerActed()
{
	return numPlayerActed;
}

void ATH_GameState::SetNumPlayerActed(int num)
{
	numPlayerActed = num;
}

int ATH_GameState::GetPot()
{
	return pot;
}
void ATH_GameState::SetPot(int chips)
{
	pot = chips;
}

int ATH_GameState::GetPlayerBet(int turn)
{
	return playerBet[turn];
}

void ATH_GameState::SetPlayerBet(int turn, int money)
{
	playerBet[turn] = money;
}

int ATH_GameState::GetBiggestBet()
{
	return biggestBet;
}
void ATH_GameState::SetBiggestBet(int chips)
{
	biggestBet = chips;
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