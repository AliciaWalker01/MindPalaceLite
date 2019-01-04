// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Core/Public/Math/Quat.h"
#include "ScaleLibrary.generated.h"

/**
 *
 */


UCLASS()
class MINDPALACELITE_API UScaleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Physics")
		static void RecreateComponentPhysicsState(class UActorComponent* pActorComponent);

	UFUNCTION(BlueprintCallable, Category = "Maths")
		static float FlattenFloat(float input, int precision);

	UFUNCTION(BlueprintPure, Category = "Maths")
		static FVector VectorDeadzoneTruncate(FVector input, float dead);

	UFUNCTION(BlueprintPure, Category = "Maths")
		static float FloatDeadzoneTruncate(float input, float dead);

	UFUNCTION(BlueprintPure, Category = "Maths")
		static void RotateCoordinates2D(const float a, const float b, const float theta, float &a_out, float &b_out);

	UFUNCTION(BlueprintPure, Category = "Maths")
		static void RotateCoordinates3D(const float x, const float y, const float z, const float yaw, const float pitch, const float roll, float &x_out, float &y_out, float &z_out);




};
