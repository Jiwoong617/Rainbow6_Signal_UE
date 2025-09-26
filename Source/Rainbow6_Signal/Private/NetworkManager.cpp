// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"

#include "Rainbow6_Signal.h"
#include "SignalData.h"
#include "WebSocketsModule.h"

void UNetworkManager::Connect(const FString& Url)
{
	if (WebSocket.IsValid() && WebSocket->IsConnected())
		return;
	
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
		FModuleManager::Get().LoadModuleChecked("WebSockets");
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(Url);

	WebSocket->OnConnected().AddUObject(this, &UNetworkManager::OnConnected_Native); //연결되었을 때
	WebSocket->OnMessage().AddUObject(this, &UNetworkManager::OnMessageReceived_Native); //메시지 받았을 때
	WebSocket->OnConnectionError().AddUObject(this, &UNetworkManager::OnConnectionError_Native); // 커넥션 오류떴을 때
	WebSocket->OnClosed().AddUObject(this, &UNetworkManager::OnClosed_Native); // 웹소켓 종료되었을 때
	
	WebSocket->Connect();
}

void UNetworkManager::SendScenarioStart(const FSignalStartData& Data)
{
	if (!WebSocket.IsValid() || !WebSocket->IsConnected())
	{
		UE_LOG(LogTemp, Error, TEXT("WebSocket not connected"));
		return;
	}

	// JSON 변환
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField(TEXT("type"), Data.Type);
	JsonObject->SetStringField(TEXT("sessionId"), SessionId);
	JsonObject->SetStringField(TEXT("scenario"), Data.Scenario);
	JsonObject->SetNumberField(TEXT("fps"), Data.Fps);

	//프레임 묶음으로 보내는거에서 한장씩 보내는 거로 변경
	// TArray<TSharedPtr<FJsonValue>> FrameArray;
	// for (const FString& FrameBase64 : Data.Frames)
	// {
	// 	FrameArray.Add(MakeShareable(new FJsonValueString(FrameBase64)));
	// }
	//JsonObject->SetArrayField(TEXT("Frames"), FrameArray);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	WebSocket->Send(OutputString);
}

void UNetworkManager::SendFrame(const FSignalFrameData& Data)
{
	if (!WebSocket.IsValid() || !WebSocket->IsConnected())
	{
		UE_LOG(LogTemp, Error, TEXT("WebSocket not connected"));
		return;
	}

	// JSON 변환
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField(TEXT("type"), Data.Type);
	JsonObject->SetStringField(TEXT("sessionId"), SessionId);
	JsonObject->SetNumberField(TEXT("frameId"), Data.FrameId);
	JsonObject->SetStringField(TEXT("frame"), Data.Frame);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	WebSocket->Send(OutputString);
}

void UNetworkManager::SendScenarioEnd(const FSignalEndData& Data)
{
	if (!WebSocket.IsValid() || !WebSocket->IsConnected())
	{
		UE_LOG(LogTemp, Error, TEXT("WebSocket not connected"));
		return;
	}

	// JSON 변환
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField(TEXT("type"), Data.Type);
	JsonObject->SetStringField(TEXT("sessionId"), SessionId);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	WebSocket->Send(OutputString);
}

void UNetworkManager::Close()
{
	if (WebSocket.IsValid())
	{
		WebSocket->Close();
		WebSocket = nullptr;
	}
}


////////////////////////여기부터는 웹소켓 통신관련 바인딩되는 함수들///////////////////////////
void UNetworkManager::OnConnected_Native()
{
	//잘 연결 되었는지 로그로 확인
	PRINTLOG(TEXT("WebSocket Connected!"));
	
	FGuid Guid = FGuid::NewGuid();
	SessionId = Guid.ToString(EGuidFormats::DigitsWithHyphens);

	OnConnected.Broadcast();
}

void UNetworkManager::OnMessageReceived_Native(const FString& Message)
{
	PRINTLOG(TEXT("WebSocket Message: %s"), *Message);

	// JSON 응답 파싱
	FSignalJudgeData Data;
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		if (JsonObject->HasField(TEXT("scenario")))
			Data.Scenario = JsonObject->GetStringField(TEXT("scenario"));
		if (JsonObject->HasField(TEXT("isAnswer")))
			Data.IsAnswer = JsonObject->GetBoolField(TEXT("isAnswer"));
		if (JsonObject->HasField(TEXT("score")))
			Data.Score = JsonObject->GetNumberField(TEXT("score"));
	}
	
	OnMessageReceived.Broadcast(Data);
}

void UNetworkManager::OnConnectionError_Native(const FString& Error)
{
	PRINTLOG(TEXT("WebSocket ERROR: %s"), *Error);

	OnConnectionError.Broadcast(Error);
}

void UNetworkManager::OnClosed_Native(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	PRINTLOG(TEXT("WebSocket CLOSED: %s"), *Reason);

	OnClosed.Broadcast(StatusCode, Reason, bWasClean);
}
