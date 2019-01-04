// Fill out your copyright notice in the Description page of Project Settings.



#include "ScaleLibrary.h"
#include "Runtime/Core/Public/Math/Quat.h"
#include <cmath>




void UScaleLibrary::RecreateComponentPhysicsState(class UActorComponent* pActorComponent)
{
	if (pActorComponent != nullptr && pActorComponent->IsValidLowLevel())
	{
		pActorComponent->RecreatePhysicsState();
	}
}

float UScaleLibrary::FlattenFloat(float input, int precision)
{

	return std::floor(input * pow(10, precision) + .5) / pow(10, precision);
}



FVector UScaleLibrary::VectorDeadzoneTruncate(FVector input, float dead)
{
	float r = input.Size();
	if (r > dead)
	{
		return  (1 - dead / r)*input;

	}
	else
	{
		return input.ZeroVector;
	}
}

float UScaleLibrary::FloatDeadzoneTruncate(float input, float dead)
{
	if (input > dead)
	{
		return input - dead;
	}
	else if (input < -dead)
	{
		return input + dead;
	}
	else
	{
		return 0;
	}
}

void UScaleLibrary::RotateCoordinates2D(const float a, const float b, const float theta, float &a_out, float &b_out)
{
	a_out = a * cos(theta) - b * sin(theta);
	b_out = a * sin(theta) + b * cos(theta);
}

void UScaleLibrary::RotateCoordinates3D(const float x, const float y, const float z, const float roll, const float pitch, const float yaw, float &x_out, float &y_out, float &z_out)
{
	x_out = x * cos(pitch)*cos(yaw) + y * (sin(roll)*sin(pitch)*cos(yaw) - cos(roll)*sin(yaw)) + z * ((cos(roll)*sin(pitch)*cos(yaw)) + sin(roll)*sin(yaw));
	y_out = x * cos(pitch)*sin(yaw) + y * (sin(roll)*sin(pitch)*sin(yaw) + cos(roll)*cos(yaw)) + z * (cos(roll)*sin(pitch)*sin(yaw) - sin(roll)*cos(yaw));
	z_out = -x * sin(pitch) + y * sin(roll)*cos(pitch) + z * cos(roll)*cos(pitch);
}


