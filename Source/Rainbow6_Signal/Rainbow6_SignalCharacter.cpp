// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rainbow6_SignalCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SplineComponent.h"
#include "Rainbow6_Signal.h"
#include "VectorTypes.h"

ARainbow6_SignalCharacter::ARainbow6_SignalCharacter()
{
// Set size for collision capsule
GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);


FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

FirstPersonMesh->SetupAttachment(GetMesh());
FirstPersonMesh->SetOnlyOwnerSee(true);
FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));


FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
FirstPersonCameraComponent->SetupAttachment(GetMesh(), FName("head"));
FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
FirstPersonCameraComponent->bUsePawnControlRotation = true;
FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
FirstPersonCameraComponent->bEnableFirstPersonScale = true;
FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
FirstPersonCameraComponent->FirstPersonScale = 0.6f;


GetMesh()->SetOwnerNoSee(true);
GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);


GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);}

// BeginPlay 함수 추가
void ARainbow6_SignalCharacter::BeginPlay()
{
	Super::BeginPlay();

	// SplineToFollow가 유효한지 확인하고 SplineComponent를 미리 찾아둠
		if (SplineToFollow)
		{
			TargetSplineComponent = SplineToFollow->FindComponentByClass<USplineComponent>();

			// 아래 디버그 로그 추가
			if (TargetSplineComponent)
			{
				// 성공 로그 (초록색)
				UE_LOG(LogTemp, Warning, TEXT("Success: Spline Component was found on the assigned Actor."));
			}
			else
			{
				// 실패 로그 (빨간색)
				UE_LOG(LogTemp, Error, TEXT("ERROR: Spline Component was NOT found on the assigned Actor! Check the BP_Spline Blueprint."));
			}
		}
		else
		{
			// SplineToFollow 자체가 할당 안된 경우 (빨간색)
			UE_LOG(LogTemp, Error, TEXT("ERROR: The 'SplineToFollow' variable is not assigned in the editor."));
		}
}

void ARainbow6_SignalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetSplineComponent)
	{
		DistanceAlongSpline += MovementSpeed * DeltaTime;

		
		FVector SplineLocation = TargetSplineComponent->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		FVector SplineTangent = TargetSplineComponent->GetDirectionAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);

		
		FVector TargetLocation = SplineLocation;
		FRotator TargetRotation;

		
		FHitResult HitResult;
		FVector TraceStart = SplineLocation + FVector(0, 0, 200.0f); 
		FVector TraceEnd = SplineLocation - FVector(0, 0, 2000.0f); 
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		FVector GroundNormal = FVector::UpVector;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, CollisionParams)) 
		{
			if (HitResult.bBlockingHit)
			{
				
				TargetLocation.Z = HitResult.ImpactPoint.Z + GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
				GroundNormal = HitResult.ImpactNormal;
			}
		}


		TargetRotation = FRotationMatrix::MakeFromXZ(SplineTangent, GroundNormal).Rotator();


		const FVector SmoothedLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, LocationSharpness);
		const FRotator SmoothedRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSharpness);

		SetActorLocationAndRotation(SmoothedLocation, SmoothedRotation);
	}
}