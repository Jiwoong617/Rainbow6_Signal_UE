#include "WebcamUI.h"
#include "ImageUtils.h"
#include "Rainbow6_Signal.h"
#include "Components/Image.h"
#include "Kismet/KismetRenderingLibrary.h"


UWebcamUI::UWebcamUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/Media/M_Webcam.M_Webcam'"));
	if (tempMat.Succeeded())
		WebCamMat = tempMat.Object;
}

void UWebcamUI::NativeConstruct()
{
	Super::NativeConstruct();

	SourceTexture = Cast<UTexture>(IMG_Webcam->Brush.GetResourceObject());
	if (!SourceTexture)
	{
		UE_LOG(LogTemp, Error, TEXT("IMG_Webcam has no texture!"));
		return;
	}

	RenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(),
		SourceTexture->GetSurfaceWidth(),
		SourceTexture->GetSurfaceHeight()
);
}

UTextureRenderTarget2D* UWebcamUI::ShotWebCam()
{
	if (RenderTarget == nullptr)
	{
		PRINTLOG(TEXT("No RenderTarget Error"));
		return nullptr;
	}
	
	// 머티리얼 인스턴스 생성 + 웹캠 텍스처 세팅
	UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(WebCamMat, this);
	MID->SetTextureParameterValue(TEXT("WebcamTEX"), SourceTexture);
	// RenderTarget에 머티리얼 그리기
	UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), RenderTarget, MID);
	
	return RenderTarget;
}
