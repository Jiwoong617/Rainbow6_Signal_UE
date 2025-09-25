// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//로그 카테고리
DECLARE_LOG_CATEGORY_EXTERN(Rainbow6_Signal, Log, All);

//호출된 함수와 줄번호 매크로
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define PRINTINFO() UE_LOG(LogTemp, Warning, TEXT("%s"), *CALLINFO)

//포맷과 가변인자
//사용할 때 PRINTLOG(TEXT("%s"), TEXT("HelloWorld"));
#define PRINTLOG(fmt, ...) \
UE_LOG(Rainbow6_Signal, Warning, TEXT("%s : %s"), *CALLINFO, *FString::Printf(fmt, ##__VA_ARGS__))