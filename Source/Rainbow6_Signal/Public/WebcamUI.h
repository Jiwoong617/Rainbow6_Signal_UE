// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WebcamUI.generated.h"

class UImage;
class UMaterial;

UCLASS()
class RAINBOW6_SIGNAL_API UWebcamUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UWebcamUI(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere)
	UMaterial* WebCamMat;

	UPROPERTY(EditAnywhere)
	UTexture* SourceTexture;

	UPROPERTY(EditAnywhere)
	UTextureRenderTarget2D* RenderTarget;
	
	UPROPERTY(meta=(BindWidget))
	UImage* IMG_Webcam;

public:
	UFUNCTION(BlueprintCallable)
	UTextureRenderTarget2D* ShotWebCam();
};
