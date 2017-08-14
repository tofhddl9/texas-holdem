// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.h"
#include "Deck.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TEXAS_API UDeck : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void Shuffle();	
	
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	static UDeck* CreateDeck();

	UFUNCTION(BlueprintCallable)
	UCard* Draw();


private:
	static const int num_cards = 52;
	UCard* cards[num_cards]; 
	int8 top;
	
	FCriticalSection critical_section;

};
