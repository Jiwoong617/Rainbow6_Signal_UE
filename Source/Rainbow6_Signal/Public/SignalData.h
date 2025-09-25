#pragma once

#include "CoreMinimal.h"
#include "SignalData.generated.h"

//언리얼측에서 서버로 보낼 정보
USTRUCT()
struct FSignalSendData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Scenario; // 현재 시나리오(손동작) 이름
	
	UPROPERTY(EditAnywhere)
	int32 ScenarioNum; // 현재 시나리오 번호 (혹시 모르니)
};

//서버측에서 언리얼로 보낼 정보
USTRUCT()
struct FSignalJudgeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Scenario; // 현재 시나리오(손동작) 이름
	
	UPROPERTY(EditAnywhere)
	bool IsAnswer; // 정답인지
	
	UPROPERTY(EditAnywhere)
	float Score; // 동작 수행률(얼마나 정답과 가까운지)
};
