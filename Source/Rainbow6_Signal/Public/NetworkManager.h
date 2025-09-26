// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWebSocket.h"
#include "NetworkManager.generated.h"

struct FSignalSendData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebSocketConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketMessageReceived, const FSignalJudgeData&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketConnectionError, const FString&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebSocketClosed, int32, StatusCode, const FString&, Reason, bool, bWasClean);

UCLASS()
class RAINBOW6_SIGNAL_API UNetworkManager : public UObject
{
	GENERATED_BODY()
private:
	TSharedPtr<IWebSocket> WebSocket;

	void OnConnected_Native();
	void OnMessageReceived_Native(const FString& Message);
	void OnConnectionError_Native(const FString& Error);
	void OnClosed_Native(int32 StatusCode, const FString& Reason, bool bWasClean);
	
public:
	UFUNCTION(BlueprintCallable, Category="Signal|WebSocket")
	void Connect(const FString& Url);

	UFUNCTION(BlueprintCallable, Category="Signal|WebSocket")
	void SendScenarioStart(const FSignalSendData& Data);

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
