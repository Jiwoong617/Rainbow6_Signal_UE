// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrainingResultUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class RAINBOW6_SIGNAL_API UTrainingResultUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_BombScore;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_HeliScore;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_TankScore;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_GasScore;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_TotalScore;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_TotalGrade;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_CommentFromCommander;

	UPROPERTY(EditAnywhere)
	USoundBase* MR;

	UPROPERTY()
	float TotalScore;

	UFUNCTION()
	void Hide();

	UFUNCTION(BlueprintCallable)
	void Show();

	UFUNCTION(blueprintCallable)
	void SetBombScore(float Score);

	UFUNCTION(blueprintCallable)
	void SetHeliScore(float Score);

	UFUNCTION(blueprintCallable)
	void SetTankScore(float Score);

	UFUNCTION(blueprintCallable)
	void SetGasScore(float Score);

	UFUNCTION(blueprintCallable)
	void UpdateTotalScoreAndGrade();
};
