// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainingResultUI.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UTrainingResultUI::Hide()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UTrainingResultUI::Show()
{
	this->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::PlaySound2D(GetWorld(), MR);
}

void UTrainingResultUI::SetBombScore(const float Score)
{
	TotalScore += (Score / 4.f);
	TEXT_BombScore->SetText(FText::FromString(FString::SanitizeFloat(Score)));
	UpdateTotalScoreAndGrade();
}

void UTrainingResultUI::SetHeliScore(const float Score)
{
	TotalScore += (Score / 4.f);
	TEXT_HeliScore->SetText(FText::FromString(FString::SanitizeFloat(Score)));
	UpdateTotalScoreAndGrade();
}

void UTrainingResultUI::SetTankScore(const float Score)
{
	TotalScore += (Score / 4.f);
	TEXT_TankScore->SetText(FText::FromString(FString::SanitizeFloat(Score)));
	UpdateTotalScoreAndGrade();
}

void UTrainingResultUI::SetGasScore(const float Score)
{
	TotalScore += (Score / 4.f);
	TEXT_GasScore->SetText(FText::FromString(FString::SanitizeFloat(Score)));
	UpdateTotalScoreAndGrade();
}

void UTrainingResultUI::UpdateTotalScoreAndGrade()
{
	TEXT_TotalScore->SetText(FText::FromString(FString::SanitizeFloat(TotalScore)));
	FText Grade;
	FText Comment;
	
	if (TotalScore >= 90)
	{
		Grade = FText::FromString(TEXT("특급"));
		Comment = FText::FromString(TEXT("참 잘했어요!"));
	}
	else if (TotalScore >= 80)
	{
		Grade = FText::FromString(TEXT("1급"));
		Comment = FText::FromString(TEXT("최고를 목표로 나아갈 것."));
	}
	else if (TotalScore >= 70)
	{
		Grade = FText::FromString(TEXT("2급"));
		Comment = FText::FromString(TEXT("더욱 정진할 수 있을 것."));
	}
	else if (TotalScore >= 60)
	{
		Grade = FText::FromString(TEXT("3급"));
		Comment = FText::FromString(TEXT("포기하지 말 것."));
	}
	else
	{
		Grade = FText::FromString(TEXT("실격"));
		Comment = FText::FromString(TEXT("..."));
	}
	
	TEXT_TotalGrade->SetText(Grade);
	TEXT_CommentFromCommander->SetText(Comment);
}