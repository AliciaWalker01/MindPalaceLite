// Fill out your copyright notice in the Description page of Project Settings.

// An child class of DesktopCapture which has a mesh that can be set (e.g. a plane) whereby it asigns a dynamic texture
// to it as a dynamic material instance and uses its parent functions to update it.
//
// @ToDo: Allow the screen to have it's scale change depending on how wide/tall the capture is. e.g. when other windows
// are implementable


#pragma once

#include "CoreMinimal.h"
#include "DesktopCapture.h"
#include "DesktopScreen.generated.h"

/**
 *
 */
UCLASS()
class MINDPALACELITE_API ADesktopScreen : public ADesktopCapture
{
	GENERATED_BODY()

		// Default Constructor
public:
	ADesktopScreen();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Plane;
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultSceneRoot;

protected:
	// when game starts or when spawned
	virtual void ChildBeginPlay() override;

private:

	UMaterialInstanceDynamic* DynamicMat;
	UMaterialInterface* Material;

};

