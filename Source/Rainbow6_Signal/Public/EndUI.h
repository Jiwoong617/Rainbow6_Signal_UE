// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class RAINBOW6_SIGNAL_API UEndUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_Answer;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_Score;

	UFUNCTION(blueprintCallable)
	void SetResultText(int32 ans, int32 score);
};
