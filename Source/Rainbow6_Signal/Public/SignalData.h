#pragma once

#include "CoreMinimal.h"
#include "SignalData.generated.h"

//언리얼측에서 서버로 보낼 정보
USTRUCT(BlueprintType)
struct FSignalSendData
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Scenario; // 현재 시나리오(손동작) 이름
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ScenarioNum; // 현재 시나리오 번호 (혹시 모르니)
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
