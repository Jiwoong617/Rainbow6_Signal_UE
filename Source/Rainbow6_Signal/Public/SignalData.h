#pragma once

#include "CoreMinimal.h"
#include "SignalData.generated.h"

namespace NetworkConfig
{
	const FString BaseUrl = TEXT("http://172.16.20.103");
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

//언리얼측에서 서버로 보낼 정보
USTRUCT(BlueprintType)
struct FSignalSendData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Scenario; // 현재 시나리오(손동작) 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Fps; // fps 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Frames; // Base64 이미지 정보
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
