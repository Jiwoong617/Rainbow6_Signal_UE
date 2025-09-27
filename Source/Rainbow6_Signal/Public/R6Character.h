// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
	
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "R6Character.generated.h"

class UEndUI;
class AR6PlayerController;
struct FSignalJudgeData;
class UWebcamUI;
class UNetworkManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResponse);

UCLASS()
class RAINBOW6_SIGNAL_API AR6Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AR6Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWebcamUI> WBP_WebcamUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEndUI> WBP_EndUI;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FTimerHandle FrameTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int32 FrameCounter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int32 Fps = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWebcamUI* WebcamUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEndUI* EndUI;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UNetworkManager* NetManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TArray<FSignalJudgeData> SignalJudgeData;

	UPROPERTY(BlueprintAssignable);
	FOnResponse OnResponseDelegate;
	
protected:
	//이게 서버에서 데이터 받았을 때 들어오는 콜백되는 함수
	UFUNCTION()
	void OnResponseReceived(const FSignalJudgeData& Message);

	UFUNCTION(BlueprintCallable)
	void SendFrame(	int32 FrameId,FString Frame);
	UFUNCTION(BlueprintCallable)
	void EndScenario();
	
public:
	UFUNCTION(BlueprintCallable)
	void StartScenario(FString Signal, int32 AllFrame);

	UFUNCTION(BlueprintCallable)
	void OnGameEnd();
};
