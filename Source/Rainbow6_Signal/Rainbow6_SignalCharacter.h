// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
UCLASS(abstract)
class ARainbow6_SignalCharacter : public ACharacter
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

};

