// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/DataManager.h"
#include "HttpModule.h"
#include "ImageUtils.h"
#include "Rainbow6_Signal.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Interfaces/IHttpResponse.h"
#include "Public/SignalData.h"

//FString UDataManager::URL = TEXT("");
//FOnResponse UDataManager::OnResponseDelegate;

// void UDataManager::OnRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
// {
// 	if (!Successful || !Response.IsValid())
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("REST API 요청 실패"));
// 		return;
// 	}
//
// 	int32 Code = Response->GetResponseCode();
// 	FString ResponseString = Response->GetContentAsString();
// 	
// 	if (Code != 200)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("서버 오류 코드: %d | 응답: %s"), Code, *ResponseString);
// 		return;
// 	}
// 	
// 	// JSON 파싱
// 	TSharedPtr<FJsonObject> JsonObject;
// 	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
// 	FSignalJudgeData Data = FSignalJudgeData();
// 	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
// 	{
// 		Data.Scenario = JsonObject->GetStringField(TEXT("Scenario"));
// 		Data.IsAnswer = JsonObject->GetBoolField(TEXT("IsAnswer"));
// 		Data.Score = JsonObject->GetNumberField(TEXT("Score"));
// 		
// 		PRINTLOG(TEXT("Scenario: %s | IsAnswer: %s | Throw: %f"),
// 			*Data.Scenario, (Data.IsAnswer ? TEXT("True") : TEXT("False")), Data.Score);
// 	}
//
// 	//Response 처리
// 	OnResponseDelegate.ExecuteIfBound(Data);
// }

// void UDataManager::SendScenarioStart(const FSignalSendData& Data)
// {
// 	// Json 변환
// 	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
// 	JsonObject->SetStringField(TEXT("Scenario"), Data.Scenario);
// 	JsonObject->SetNumberField(TEXT("Fps"), Data.Fps);
// 	TArray<TSharedPtr<FJsonValue>> FrameArray;
// 	for (const FString& FrameBase64 : Data.Frames)
// 	{
// 		FrameArray.Add(MakeShareable(new FJsonValueString(FrameBase64)));
// 		
// 	}
// 	JsonObject->SetArrayField(TEXT("Frames"), FrameArray);
//
// 	FString OutputString;
// 	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
// 	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
//
// 	// HTTP 요청
// 	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
// 	Request->SetURL(URL);
// 	Request->SetVerb("POST");  // POST: push new entry, PUT: overwrite
// 	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
// 	Request->SetContentAsString(OutputString);
// 	Request->OnProcessRequestComplete().BindStatic(&UDataManager::OnRequestComplete);
// 	Request->ProcessRequest();
// }

FString UDataManager::EncodeFrameToBase64(UTextureRenderTarget2D* RenderTarget)
{
	TArray<FColor> Pixels;
	FRenderTarget* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
	RenderTargetResource->ReadPixels(Pixels);

	TArray<uint8> CompressedBytes;
	FImageUtils::CompressImageArray(RenderTarget->SizeX, RenderTarget->SizeY, Pixels, CompressedBytes);

	return FBase64::Encode(CompressedBytes);
}
