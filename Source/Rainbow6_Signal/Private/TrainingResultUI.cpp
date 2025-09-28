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
	FString Grade;
	FString Comment;
	
	if (TotalScore >= 90)
	{
		Grade = TEXT("특급");
		Comment = TEXT("참 잘했어요!");
	}
	else if (TotalScore >= 80)
	{
		Grade = "1급";
		Comment = TEXT("최고를 목표로 나아갈 것.");
	}
	else if (TotalScore >= 70)
	{
		Grade = "2급";
		Comment = TEXT("더욱 정진할 수 있을 것.");
	}
	else if (TotalScore >= 60)
	{
		Grade = "3급";
		Comment = TEXT("포기하지 말 것.");
	}
	else
	{
		Grade = "실격";
		Comment = TEXT("");
	}
	
	TEXT_TotalGrade->SetText(FText::FromString(Grade));
	TEXT_CommentFromCommander->SetText(FText::FromString(Comment));
}