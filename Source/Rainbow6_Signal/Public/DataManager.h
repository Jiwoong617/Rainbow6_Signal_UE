// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"

struct FSignalSendData;

class RAINBOW6_SIGNAL_API UDataManager
{
private:
	static FString URL;

	static void OnRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
public:
	static void SendScenarioStart(const FSignalSendData& Data);
};
