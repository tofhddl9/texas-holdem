// Fill out your copyright notice in the Description page of Project Settings.

#include "TH_GameState.h"

void ATH_GameState::BeginPlay()
{
	Super::BeginPlay();

	GameInit();
	PreFlop();
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
	dealer = (dealer++) % numTotalPlayer;
	sb = (sb++) % numTotalPlayer;
	bb = (bb++) % numTotalPlayer;
	bigBet = 2;//
	smallBet = bigBet / 2;
	pot = bigBet + smallBet;//
	turn = (bb + 1) % numTotalPlayer;
	
	numActivePlayer = 2;//
	numTotalPlayer = 2;//
	//thisAction = GetPlayerAction();
	switch (thisAction)
	{
		case fold:break;
		case call:break;
		case raise:break;
	case check:break;
	}

}

void ATH_GameState::PreFlop()
{
	while (numActivePlayer != numPlayerActed) {

	}
}
