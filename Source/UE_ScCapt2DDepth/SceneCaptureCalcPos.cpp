// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneCaptureCalcPos.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

FVector ASceneCaptureCalcPos::CalculateDepthFromClippedPos(const FVector2D clippedPos)
{
	FMinimalViewInfo viewInfo;

	CalcCamera(0.f, viewInfo);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString("Capture info:") + viewInfo.Location.ToString() + viewInfo.Rotation.ToString() 
																	+ FString(" clippedPos:") + clippedPos.ToString());

	FMatrix projectionMatrix = viewInfo.CalculateProjectionMatrix().Inverse();
	FVector spawnPoint = FVector(1., 1., 0.);
	projectionMatrix.TransformPosition(spawnPoint);
	spawnPoint.Normalize();
	
	
	auto RenderTargetResource = GetCaptureComponent2D()->TextureTarget->GameThread_GetRenderTargetResource();

	if (RenderTargetResource)
	{
		TArray<FFloat16Color> buffer;
		RenderTargetResource->ReadFloat16Pixels(buffer);
		spawnPoint = buffer[0].A.GetFloat() * spawnPoint;
	}

	return spawnPoint;
}
