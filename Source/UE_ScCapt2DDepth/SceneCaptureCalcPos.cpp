// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneCaptureCalcPos.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"

FVector ASceneCaptureCalcPos::CalculateDepthFromClippedPos(const FVector2D clippedPos)
{
	FMinimalViewInfo viewInfo;

	CalcCamera(0.f, viewInfo);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString("Capture info:") + viewInfo.Location.ToString() + viewInfo.Rotation.ToString() 
																	+ FString(" clippedPos:") + clippedPos.ToString());

	FMatrix projectionMatrix = viewInfo.CalculateProjectionMatrix().Inverse();
	FVector spawnPoint(clippedPos, 1.);
	projectionMatrix.TransformPosition(spawnPoint);
	spawnPoint.Normalize();
	
	
	// read depth from depth map by UV coordinate
	UTextureRenderTarget2D *pTexture = GetCaptureComponent2D()->TextureTarget.Get();
	FLinearColor pixelColor = UKismetRenderingLibrary::ReadRenderTargetRawUV(GetWorld(), pTexture,
													clippedPos.X / static_cast< float >(pTexture->SizeX),
													clippedPos.Y / static_cast< float >(pTexture->SizeY),
													false);
	//TODO clippedPos need to be recalculated to UV coordinates [0,1]

	spawnPoint *= pixelColor.A;

	return spawnPoint;
}
