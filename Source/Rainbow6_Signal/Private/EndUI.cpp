// Fill out your copyright notice in the Description page of Project Settings.


#include "EndUI.h"

#include "Components/TextBlock.h"

void UEndUI::SetResultText(int32 ans, int32 score)
{
	TEXT_Answer->SetText(FText::FromString(FString::Printf(TEXT("정답 : %d"), ans)));
	TEXT_Score->SetText(FText::FromString(FString::Printf(TEXT("점수 : %d"), score)));
}
