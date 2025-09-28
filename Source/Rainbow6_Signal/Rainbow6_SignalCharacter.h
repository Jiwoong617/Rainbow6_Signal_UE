// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "R6Character.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Rainbow6_SignalCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS()
class ARainbow6_SignalCharacter : public AR6Character
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	UCameraComponent* FirstPersonCameraComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Movement")
	class AActor* SplineToFollow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Movement")
	float MovementSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Movement", meta = (ClampMin = "0.0"))
	float LocationSharpness = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Movement", meta = (ClampMin = "0.0"))
	float RotationSharpness = 10.0f;

	float DistanceAlongSpline = 0.0f;

	UPROPERTY()
	class USplineComponent* TargetSplineComponent;


public:
	ARainbow6_SignalCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

public:
	UFUNCTION(BlueprintCallable)
	// 지정된 시간 동안 캐릭터의 움직임을 멈춥니다.
	void StopMovementForDuration(float Duration);

private:
	UFUNCTION()
	// 캐릭터의 움직임을 재개합니다.
	void ResumeMovement();

	// 움직임 멈춤 타이머를 위한 핸들
	FTimerHandle MovementStopTimerHandle;

	// 원래 이동 속도를 저장하기 위한 변수
	float OriginalMovementSpeed;
};

