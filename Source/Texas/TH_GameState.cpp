// Fill out your copyright notice in the Description page of Project Settings.

#include "TH_GameState.h"
#include <algorithm>
void ATH_GameState::BeginPlay()
{
	Super::BeginPlay();
	GameInit();
}

void ATH_GameState::PassTurn()
{
	if (numActivePlayer == numTotalPlayer)turn = (turn+1) % numTotalPlayer;
	else turn = (dealer + 1) % numActivePlayer;
}

int ATH_GameState::GetTurn()
{
	return turn;
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
	isHoleCardSpread = false;
	deck = UDeck::CreateDeck();
	deck->Init();
	deck->Shuffle();
	turnState = TurnState::PREFLOP;
	dealer = 0;
	sb = dealer + 1;
	bb = sb + 1;
	numTotalPlayer = 2;//
	numActivePlayer = 2;// 
	numPlayerActed = 0;
	dealer = (dealer++) % numTotalPlayer;
	sb = (sb+1) % numTotalPlayer;
	bb = (bb+1) % numTotalPlayer;
	turn = (bb+1) % numTotalPlayer;
	bigBet = 2;
	smallBet = bigBet / 2;
	pot = bigBet + smallBet;
	biggestBet = bigBet;
	for (int i = 0; i < numTotalPlayer; ++i) {
		isNewPlayer[i] = false; // 플레이어 추가될 때 true로 set
		isPlaying[i] = true;
		playerBet[i] = 0;
		playerBankroll[i] = 100;
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
			turnState = TurnState::TURN;
			break;
		case TurnState::TURN :
			riverCard = deck->Draw();
			numPlayerActed = 0;
			for (int i = 0;i < numTotalPlayer;++i) {
				playerHands[i][6] = riverCard;
			}
			turnState = TurnState::RIVER;
			break;
		case TurnState::RIVER:
			winner = DetermineWinner(); // suppose winner is unique
			ApplyGameResult(winner);
			SetNewGame();
			break;
		}
	}
}

void ATH_GameState::SetNewGame()
{
	isHoleCardSpread = false;
	deck = UDeck::CreateDeck();
	deck->Init();
	deck->Shuffle();
	turnState = TurnState::PREFLOP;
	numActivePlayer = 2;// 
	numPlayerActed = 0;
	dealer = (dealer++) % numTotalPlayer;
	sb = (sb + 1) % numTotalPlayer;
	bb = (bb + 1) % numTotalPlayer;
	turn = (bb + 1) % numTotalPlayer;
	pot = bigBet + smallBet;
	biggestBet = bigBet;
	for (int i = 0; i < numTotalPlayer; ++i) {
		playerBet[i] = 0;
		if (isNewPlayer[i]) {
			playerBankroll[i] = 100;// new player에게만 필요.
			isNewPlayer[i] = false;
		}
	}
	playerBet[bb] = bigBet;
	playerBet[sb] = smallBet;
	PreFlop();
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

int ATH_GameState::GetNumActivePlayer()
{
	return numActivePlayer;
}

void ATH_GameState::SetNumActivePlayer(int num)
{
	numActivePlayer = num;
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

int ATH_GameState::GetPlayerBankroll(int player)
{
	return playerBankroll[player];
}

void ATH_GameState::SetPlayerBankroll(int player, int money)
{
	playerBankroll[player] = money;
}

int ATH_GameState::GetBiggestBet()
{
	return biggestBet;
}

void ATH_GameState::SetBiggestBet(int money)
{
	biggestBet = money;
}

bool ATH_GameState::GetisPlaying(int id)
{
	return isPlaying[id];
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

void ATH_GameState::ApplyGameResult(int winner)
{
	for (int i = 0;i < numTotalPlayer;++i) {
		if (i == winner) {
			playerBankroll[i] += (pot - playerBet[i]);
		} else {
			playerBankroll[i] -= playerBet[i];
		}
	}
}