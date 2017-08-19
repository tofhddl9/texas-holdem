// Fill out your copyright notice in the Description page of Project Settings.

#include "TH_GameState.h"

void ATH_GameState::BeginPlay()
{
	Super::BeginPlay();

	deck=UDeck::CreateDeck();
	deck->Init();
	deck->Shuffle();
}

UDeck* ATH_GameState::GetDeck()
{
	return deck;
}
