// Fill out your copyright notice in the Description page of Project Settings.


#include "R6GameMode.h"

#include "DataManager.h"
#include "NetworkManager.h"
#include "Rainbow6_Signal.h"
#include "SignalData.h"
#include "WebcamUI.h"
#include "Blueprint/UserWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"

AR6GameMode::AR6GameMode()
{
	ConstructorHelpers::FClassFinder<UWebcamUI> wbpWebcam(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/WBP/WBP_WebCamUI.WBP_WebCamUI'"));
	if (wbpWebcam.Succeeded())
		WBP_WebcamUI = wbpWebcam.Class;
}

void AR6GameMode::BeginPlay()
{
	Super::BeginPlay();

	//TODO : 지금 owning object null 뜸 살려주셈
	WebcamUI = CreateWidget<UWebcamUI>(GetWorld(), WBP_WebcamUI);
	WebcamUI->AddToViewport();

	NetManager = GetWorld()->GetSubsystem<UNetworkManager>();
	if (NetManager)
		NetManager->Connect(NetworkConfig::GetURL());
}

void AR6GameMode::OnResponseReceived(const FSignalJudgeData& Message)
{
	PRINTLOG(TEXT("Scenario: %s, Score: %f"), *Message.Scenario, Message.Score);
}

void AR6GameMode::SendFrame(int32 FrameId, FString Frame)
{
	FSignalFrameData FrameData;
	FrameData.Type = TEXT("frame");
	FrameData.FrameId = FrameId;
	FrameData.Frame = Frame;
		
	NetManager->SendFrame(FrameData);
}

void AR6GameMode::EndScenario()
{
	NetManager->SendScenarioEnd(FSignalEndData(TEXT("end_scenario")));
}

void AR6GameMode::StartScenario(FString Signal, int32 fps)
{
	FrameCounter = 0;
	
	FSignalStartData StartData;
	StartData.Type = TEXT("start_scenario");
	StartData.Scenario = Signal;
	StartData.Fps = fps;
	NetManager->SendScenarioStart(StartData);

	Fps = fps;
	
	float cnt = 2.f / static_cast<float>(Fps);
	GetWorldTimerManager().SetTimer(FrameTimer, [this]()
	{
		if (FrameCounter == Fps)
		{
			GetWorldTimerManager().ClearTimer(FrameTimer);
			EndScenario();
			return;
		}

		UTextureRenderTarget2D* Target = WebcamUI->ShotWebCam();
		FString Frame = UDataManager::EncodeFrameToBase64(Target);
		SendFrame(FrameCounter, Frame);
		FrameCounter++;
	}, cnt, true);
}
