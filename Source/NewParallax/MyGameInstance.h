// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NEWPARALLAX_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
		FTransform TopLeftTransform;
		FTransform TopRightTransform;
		FTransform BottomLeftTransform;
		FTransform BottomRightTransform;
		FTransform CameraTransform;
		UFUNCTION(BlueprintCallable)
		void SetTopLeftTransform(FTransform transform);
		UFUNCTION(BlueprintCallable)
		void SetTopRightTransform(FTransform transform);
		UFUNCTION(BlueprintCallable)
		void SetBottomLeftTransform(FTransform transform);
		UFUNCTION(BlueprintCallable)
		void SetBottomRightTransform(FTransform transform);
		UFUNCTION(BlueprintCallable)
		void SetCameraTransform(FTransform transform);
};
