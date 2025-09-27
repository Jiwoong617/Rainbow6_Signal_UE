
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StopTriggerBox.generated.h"

class UBoxComponent;

UCLASS()
class RAINBOW6_SIGNAL_API AStopTriggerBox : public AActor
{
    GENERATED_BODY()

public:

    AStopTriggerBox();

protected:
 
    virtual void BeginPlay() override;

public:

    virtual void Tick(float DeltaTime) override;

   
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* TriggerBox;

    // 캐릭터가 멈춰있을 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay")
    float StopDuration = 3.0f;

    
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
