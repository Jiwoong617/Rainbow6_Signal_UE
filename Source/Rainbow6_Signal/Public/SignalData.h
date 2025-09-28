#pragma once

#include "CoreMinimal.h"
#include "SignalData.generated.h"

namespace NetworkConfig
{
	const FString BaseUrl = TEXT("wss://3e22125ffb05.ngrok-free.app/ws/scenario");
	const int32 Port = 8000;

	static FString GetURL()
	{
		return BaseUrl;
	}
	
	static FString GetFullUrl(const FString& Endpoint)
	{
		return FString::Printf(TEXT("%s:%d%s"), *BaseUrl, Port, *Endpoint);
	}
}

//언리얼측에서 서버로 보낼 정보 - Start
USTRUCT(BlueprintType)
struct FSignalStartData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type = TEXT("start_scenario"); // start_scenario
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Scenario; // 현재 시나리오(손동작) 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Fps; // 총 fps 수
};

//언리얼측에서 서버로 보낼 정보 - Frame
USTRUCT(BlueprintType)
struct FSignalFrameData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type = TEXT("frame"); // frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FrameId; // 현재 프레임 번호
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString jpegBase64; // Base64 이미지 정보
};

//언리얼측에서 서버로 보낼 정보 - End
USTRUCT(BlueprintType)
struct FSignalEndData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type = TEXT("end_scenario"); // end_scenario
};


//서버측에서 언리얼로 보낼 정보
USTRUCT(BlueprintType)
struct FSignalJudgeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Scenario; // 현재 시나리오(손동작) 이름
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAnswer; // 정답인지
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Score; // 동작 수행률(얼마나 정답과 가까운지)
};