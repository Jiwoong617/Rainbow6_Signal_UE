


#include "Public/StopTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Rainbow6_Signal/Rainbow6_SignalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


AStopTriggerBox::AStopTriggerBox()
{
    
    PrimaryActorTick.bCanEverTick = true;
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AStopTriggerBox::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AStopTriggerBox::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AStopTriggerBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AStopTriggerBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        ARainbow6_SignalCharacter* Character = Cast<ARainbow6_SignalCharacter>(OtherActor);
        if (Character)
        {
            Character->StopMovementForDuration(StopDuration);
        }
    }
}
