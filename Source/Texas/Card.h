// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class Pattern : uint8
{
	CLUBS UMETA(DisplayName="CLUBS"),
	SPADES UMETA(DisplayName = "SPADES"),
	DIAMONDS UMETA(DisplayName = "DIAMONDS"),
	HEARTS UMETA(DisplayName = "HEARTS")
};

UCLASS(BlueprintType)
class TEXAS_API UCard : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	int GetNum();

	UFUNCTION(BlueprintCallable)
	Pattern GetPattern();

//protected:
	Pattern pattern;
	int number;
};
