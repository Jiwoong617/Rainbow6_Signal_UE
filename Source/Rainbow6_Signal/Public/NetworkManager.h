// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWebSocket.h"
#include "NetworkManager.generated.h"

class IWebSocket;
struct FSignalFrameData;
struct FSignalStartData;
struct FSignalEndData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebSocketConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketMessageReceived, const FSignalJudgeData&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketConnectionError, const FString&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebSocketClosed, int32, StatusCode, const FString&, Reason, bool, bWasClean);

UCLASS()
class RAINBOW6_SIGNAL_API UNetworkManager : public UWorldSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY()
	FString SessionId;
	
	TSharedPtr<IWebSocket> WebSocket;

	void OnConnected_Native();
	void OnMessageReceived_Native(const FString& Message);
	void OnConnectionError_Native(const FString& Error);
	void OnClosed_Native(int32 StatusCode, const FString& Reason, bool bWasClean);
	
public:
	UFUNCTION(BlueprintCallable, Category="Signal|WebSocket")
	void Connect(const FString& Url);

	//시나리오 시작 시 넘기기
	UFUNCTION(BlueprintCallable, Category="Signal|WebSocket")
	void SendScenarioStart(const FSignalStartData& Data);

	//시나리오 시작, 프레임(사진 정보) 넘기기
	UFUNCTION(BlueprintCallable, Category="Signal|WebSocket")
	void SendFrame(const FSignalFrameData& Data);

	//녹화가 끝났다면 넘기기
	UFUNCTION(BlueprintCallable, Category="Signal|WebSocket")
	void SendScenarioEnd(const FSignalEndData& Data);

	UFUNCTION(BlueprintCallable, Category="Signal|WebSocket")
	void Close();
		
	UPROPERTY(BlueprintAssignable, Category = "WebSocket")
	FOnWebSocketConnected OnConnected;
	UPROPERTY(BlueprintAssignable, Category = "WebSocket")
	FOnWebSocketMessageReceived OnMessageReceived;

	UPROPERTY(BlueprintAssignable, Category = "WebSocket")
	FOnWebSocketConnectionError OnConnectionError;
	UPROPERTY(BlueprintAssignable, Category = "WebSocket")
	FOnWebSocketClosed OnClosed;
};
