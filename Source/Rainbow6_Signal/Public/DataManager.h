// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataManager.generated.h"

struct FSignalSendData;
struct FSignalJudgeData;

//DECLARE_DYNAMIC_DELEGATE_OneParam(FOnResponse, const FSignalJudgeData&, Data);

UCLASS()
class RAINBOW6_SIGNAL_API UDataManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
private:
	static FString URL;
	
	//static void OnRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful);
public:
	//static FOnResponse OnResponseDelegate;

	UFUNCTION(BlueprintCallable, Category="Signal|REST")
	static FString EncodeFrameToBase64(UTextureRenderTarget2D* RenderTarget);
	//UFUNCTION(BlueprintCallable, Category="Signal|REST")
	//static void SendScenarioStart(const FSignalSendData& Data);
};
