// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "R6GameMode.generated.h"

struct FSignalJudgeData;
class UWebcamUI;
/**
 * 
 */
UCLASS()
class RAINBOW6_SIGNAL_API AR6GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AR6GameMode();
	virtual void BeginPlay() override;

private:
	FTimerHandle FrameTimer;
	int32 FrameCounter = 0;
	int32 Fps = 0;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWebcamUI> WBP_WebcamUI;
	UPROPERTY(EditAnywhere)
	UWebcamUI* WebcamUI;

	UPROPERTY()
	UNetworkManager* NetManager;

private:
	//이게 서버에서 데이터 받았을 때 들어오는 콜백되는 함수
	UFUNCTION()
	void OnResponseReceived(const FSignalJudgeData& Message);

	UFUNCTION(BlueprintCallable)
	void SendFrame(	int32 FrameId,FString Frame);
	UFUNCTION(BlueprintCallable)
	void EndScenario();
	
public:
	UFUNCTION(BlueprintCallable)
	void StartScenario(FString Signal, int32 fps);
	
};
