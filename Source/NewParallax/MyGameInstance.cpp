// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::SetTopLeftTransform(FTransform transform)
{
	TopLeftTransform = transform;
}

void UMyGameInstance::SetTopRightTransform(FTransform transform)
{
	TopRightTransform = transform;
}

void UMyGameInstance::SetBottomLeftTransform(FTransform transform)
{
	BottomLeftTransform = transform;
}

void UMyGameInstance::SetBottomRightTransform(FTransform transform)
{
	BottomRightTransform = transform;
}

void UMyGameInstance::SetCameraTransform(FTransform transform)
{
	CameraTransform = transform;
}
