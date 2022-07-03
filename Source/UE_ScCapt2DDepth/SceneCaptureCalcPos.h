// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "Math/Vector.h"
#include "SceneCaptureCalcPos.generated.h"

/**
 * 
 */
UCLASS()
class UE_SCCAPT2DDEPTH_API ASceneCaptureCalcPos : public ASceneCapture2D
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		virtual FVector CalculateDepthFromClippedPos(const FVector2D clippedPos);
	
};
