// Fill out your copyright notice in the Description page of Project Settings.

#include "TH_GameState.h"
#include <algorithm>
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

void ATH_GameState::PreFlop()
{
	for (int i = 0;i < numTotalPlayer; ++i) {
		for (int j = 0;j < 2;++j) {
			playerHands[i][j] = deck->Draw();
		}
	}
}

UCard* ATH_GameState::GetPlayerHands(int player, int seq)
{
	return playerHands[player][seq];
}

void ATH_GameState::GameInit()
{
	deck = UDeck::CreateDeck();
	deck->Init();// game의 상위 단계에서 한 번 하면 됨.
	deck->Shuffle();
	turnState = TurnState::PREFLOP;
	dealer = 0; // game의 상위 단계에서 한 번 하면 됨.
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
	
	PreFlop();
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
			for (int i = 0;i < numTotalPlayer; ++i) {
				playerHands[i][2] = flopCard1;
				playerHands[i][3] = flopCard2;
				playerHands[i][4] = flopCard3;
			}
			turnState = TurnState::FLOP;
			break;
		case TurnState::FLOP :
			turnCard = deck->Draw();
			numPlayerActed = 0;
			for (int i = 0;i < numTotalPlayer;++i) {
				playerHands[i][5] = turnCard;
			}
			turnState = TurnState::RIVER;
			break;
		case TurnState::RIVER :
			riverCard = deck->Draw();
			for (int i = 0;i < numTotalPlayer;++i) {
				playerHands[i][6] = riverCard;
			}
			winner = DetermineWinner();
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

bool sortByRank(const UCard* c1, const UCard* c2)
{
	if (c1->number == 1) return false;
	return c1->number < c2->number;
}

void ATH_GameState::SortPlayerHands()
{
	for (int i = 0;i < numTotalPlayer;++i) {
		std::sort(&playerHands[i][0], &playerHands[i][0] + 6,sortByRank);
	}
}

void ATH_GameState::ScoringHands()
{
	int numSamePattern;
}

void ATH_GameState::AnalyzeHands()
{
	SortPlayerHands();
	ScoringHands();
}

int ATH_GameState::DetermineWinner()
{
	AnalyzeHands();
	return 0;
}