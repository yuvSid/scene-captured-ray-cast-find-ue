// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneCaptureCalcPos.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/GameplayStatics.h"

FVector ASceneCaptureCalcPos::CalculateDepthFromClippedPos(const FVector2D& normalizedPos)
{
	FVector2D checkedNormalizedPos(FMath::Clamp(normalizedPos.X, 0., 1.),
								   FMath::Clamp(normalizedPos.Y, 0., 1.));

	// Get inverse view projection Matrix
	FMinimalViewInfo viewInfo;
	CalcCamera(0.f, viewInfo);
	FMatrix invVewProjMatrix, viewMatrix, projMatrix;
	UGameplayStatics::GetViewProjectionMatrix(viewInfo, viewMatrix, projMatrix, invVewProjMatrix);
	invVewProjMatrix = invVewProjMatrix.Inverse();
	
	// Get the pixel coordinates into -1..1 projection space
	const float ScreenSpaceX = (checkedNormalizedPos.X - 0.5f) * 2.0f;
	const float ScreenSpaceY = ((1.0f - checkedNormalizedPos.Y) - 0.5f) * 2.0f;

	FVector3d spawnPoint(ScreenSpaceX, ScreenSpaceY, 0.f);
	spawnPoint = invVewProjMatrix.TransformPosition(spawnPoint);
		
	// read depth from depth map by UV coordinate
	UTextureRenderTarget2D* pTexture = GetCaptureComponent2D()->TextureTarget.Get();
	if (!pTexture || GetCaptureComponent2D()->CaptureSource != ESceneCaptureSource::SCS_SceneColorSceneDepth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to acces not initialized of wrong capttured texture: %s"), __FUNCTION__);
		return FVector(0.);
	}
	double depth = UKismetRenderingLibrary::ReadRenderTargetRawUV(GetWorld(),
																  pTexture, 
																  checkedNormalizedPos.X,
																  checkedNormalizedPos.Y,
																  false).A;

	// find intersectio point of ray and depth plane
	spawnPoint.Normalize();
	//		rotate default normal camera vector to current camera rotation
	FVector3d cameraNormal = viewInfo.Rotation.RotateVector(FVector(1., 0., 0.));
	cameraNormal.Normalize();
	FPlane depthPlane(cameraNormal, depth);
	spawnPoint = FMath::RayPlaneIntersection(FVector3d(0.), spawnPoint, depthPlane);

	// convert to world coordinates
	spawnPoint += viewInfo.Location;
	return spawnPoint;
}