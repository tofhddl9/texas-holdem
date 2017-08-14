// Fill out your copyright notice in the Description page of Project Settings.

#include "Deck.h"
#include <random>

template <typename T>
inline T RandomMt19937(T min, T max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<T> dist(min, max);

	return dist(mt);
}

void UDeck::Init()
{
	top = 0;
	for (int i = 0;i < num_cards;++i){
		cards[i] = NewObject<UCard>();
		cards[i]->pattern = static_cast<Pattern>(i % 4);
		cards[i]->number = i % 13 +1;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Init()");
}

void UDeck::Shuffle()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Shuffle()");
	for (int i = 0;i < 30;++i) {
		int idx1 = RandomMt19937(0, 51);
		int idx2 = RandomMt19937(0, 51);
		std::swap(cards[idx1], cards[idx2]);
	}
}

UDeck* UDeck::CreateDeck()
{
	return NewObject<UDeck>();
}

UCard* UDeck::Draw()
{
	critical_section.Lock();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "DRAW()");
	UCard *ret = cards[top++];
	critical_section.Unlock();
	return ret;
}

