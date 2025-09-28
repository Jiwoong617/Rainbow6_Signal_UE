// Fill out your copyright notice in the Description page of Project Settings.


#include "R6Character.h"

#include "DataManager.h"
#include "NetworkManager.h"
#include "Rainbow6_Signal.h"
#include "SignalData.h"
#include "TrainingResultUI.h"
#include "WebcamUI.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AR6Character::AR6Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UWebcamUI> wbpWebcam(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/WBP/WBP_WebCamUI.WBP_WebCamUI_C'"));
	if (wbpWebcam.Succeeded())
		WBP_WebcamUI = wbpWebcam.Class;

	ConstructorHelpers::FClassFinder<UTrainingResultUI> wbpResult(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_TrainingResultUI.WBP_TrainingResultUI_C'"));
	if (wbpResult.Succeeded())
		WBP_ResultUI = wbpResult.Class;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AR6Character::BeginPlay()
{
	Super::BeginPlay();

	WebcamUI = CreateWidget<UWebcamUI>(GetWorld(), WBP_WebcamUI);
	WebcamUI->AddToViewport();

	ResultUI = CreateWidget<UTrainingResultUI>(GetWorld(), WBP_ResultUI);

	NetManager = GetWorld()->GetSubsystem<UNetworkManager>();
	if (NetManager)
	{
		NetManager->OnMessageReceived.AddDynamic(this, &AR6Character::OnResponseReceived);
		NetManager->OnFrameResponseDelegate.AddDynamic(this, &AR6Character::OnFrameResponseReceived);
		NetManager->Connect(NetworkConfig::GetURL());
	}
}

// Called every frame
void AR6Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AR6Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AR6Character::OnResponseReceived(const FSignalJudgeData& Message)
{
	PRINTLOG(TEXT("Scenario: %s, Score: %f, IsAnswer: %S"), *Message.Scenario, Message.Score
		, (Message.IsAnswer ? "Answer" : "Not An answer"));

	SignalJudgeData.Add(Message);
	OnResponseDelegate.Broadcast();
}

void AR6Character::OnFrameResponseReceived(int32 FrameNum)
{
	if (FrameNum == Fps)
	{
		PRINTLOG(TEXT("%d"), FrameNum);
		EndScenario();
	}
}

void AR6Character::SendFrame(int32 FrameId, FString Frame)
{
	FSignalFrameData FrameData;
	FrameData.Type = TEXT("frame");
	FrameData.FrameId = FrameId;
	FrameData.jpegBase64 = Frame;
		
	NetManager->SendFrame(FrameData);
}

void AR6Character::EndScenario()
{
	NetManager->SendScenarioEnd(FSignalEndData(TEXT("end_scenario")));
}

void AR6Character::StartScenario(FString Signal, int32 AllFrame)
{
	FrameCounter = 0;
	
	FSignalStartData StartData;
	StartData.Type = TEXT("start_scenario");
	StartData.Scenario = Signal;
	StartData.Fps = AllFrame;
	NetManager->SendScenarioStart(StartData);

	//PRINTLOG(TEXT("%s \n %d \n %s"), *StartData.Scenario, StartData.Fps, *StartData.Type);
	
	Fps = AllFrame;
	
	float cnt = 2.f / static_cast<float>(Fps);
	GetWorldTimerManager().SetTimer(FrameTimer, [this]()
	{
		if (FrameCounter == Fps)
		{
			GetWorldTimerManager().ClearTimer(FrameTimer);
			return;
		}

		UTextureRenderTarget2D* Target = WebcamUI->ShotWebCam();
		FString Frame = UDataManager::EncodeFrameToBase64(Target);
		SendFrame(FrameCounter, Frame);
		FrameCounter++;
	}, cnt, true);

	//GetWorldTimerManager().SetTimer(EndTimer, this, &AR6Character::EndScenario, 4.f, false);
}

void AR6Character::OnGameEnd()
{
	WebcamUI->RemoveFromParent();
	ResultUI->AddToViewport();
	//EndUI->SetResultText()
}
