// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLocalPlayer.h"

#include "MyGameInstance.h"

FSceneView* UMyLocalPlayer::CalcSceneView(FSceneViewFamily* ViewFamily, FVector& OutViewLocation,
                                          FRotator& OutViewRotation, FViewport* Viewport, FViewElementDrawer* ViewDrawer, int32 StereoViewIndex)
{
	FSceneView* SceneView = Super::CalcSceneView(ViewFamily, OutViewLocation, OutViewRotation, Viewport, ViewDrawer, StereoViewIndex);
	UGameInstance* gameInstance = GetGameInstance();
	UMyGameInstance* myGameInstance = dynamic_cast<UMyGameInstance*>(gameInstance);
	if(myGameInstance == nullptr)
	{
		return SceneView;
	}

	FVector topLeftLocation = myGameInstance->TopLeftTransform.GetLocation();
	FVector topRightLocation = myGameInstance->TopRightTransform.GetLocation();
	FVector bottomLeftLocation = myGameInstance->BottomLeftTransform.GetLocation();
	FVector bottomRightLocation = myGameInstance->BottomRightTransform.GetLocation();
	FVector cameraLocation = SceneView->ViewMatrices.GetViewOrigin();

	float width = (topRightLocation - topLeftLocation).Length();
	float height = (topLeftLocation - bottomLeftLocation).Length();
	FVector midPoint = (topLeftLocation + topRightLocation + bottomLeftLocation + bottomRightLocation)/4;

	FVector xAxis = (topRightLocation-topLeftLocation).GetSafeNormal();
	FVector yAxis = (topLeftLocation-bottomLeftLocation).GetSafeNormal();
	FVector zAxis = xAxis.Cross(yAxis);

	FVector cameraVector = cameraLocation-midPoint;

	float cameraDist  = -cameraVector.Dot(zAxis);

	float scale = 2*cameraDist/width;

	float horizontalComponent = 2*cameraVector.Dot(xAxis)/width;
	float verticalComponent = 2*cameraVector.Dot(yAxis)/height;

	FMatrix projectionMatrix = SceneView->ProjectionMatrixUnadjustedForRHI;
	projectionMatrix.M[2][0] = horizontalComponent;
	projectionMatrix.M[2][1] = verticalComponent;
	projectionMatrix.M[0][0] *= scale;
	projectionMatrix.M[1][1] *= scale;

	projectionMatrix.M[2][2] = 0.0f;
	projectionMatrix.M[3][0] = 0.0f;
	projectionMatrix.M[3][1] = 0.0f;
	projectionMatrix.M[2][3] = 1;

	projectionMatrix *= 1.0f / projectionMatrix.M[0][0];
	projectionMatrix.M[3][2] = GNearClippingPlane;

	SceneView->UpdateProjectionMatrix(projectionMatrix);

	FVector TopLeft = FVector(80,-80.f,45.f);
	FVector TopRight = FVector(80,80.f,45.f);
	FVector BottomLeft = FVector(80,-80.f,-45.f);
	FVector BottomRight = FVector(80,80.f,-45.f);

	FVector4 TopLeftProjected = SceneView->Project(TopLeft);
	FVector4 TopRightProjected = SceneView->Project(TopRight);
	FVector4 BottomLeftProjected = SceneView->Project(BottomLeft);
	FVector4 BottomRightProjected = SceneView->Project(BottomRight);

	// if(GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Yellow,TEXT("Top Left: " + TopLeftProjected.ToString()));
	// 	GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Yellow,TEXT("Top Right: " + TopRightProjected.ToString()));
	// 	GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Yellow,TEXT("Bottom Left: " + BottomLeftProjected.ToString()));
	// 	GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Yellow,TEXT("Bottom Right: " + BottomRightProjected.ToString()));
	// }

	return SceneView;
}
