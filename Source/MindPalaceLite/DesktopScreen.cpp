// Fill out your copyright notice in the Description page of Project Settings.

#include "DesktopScreen.h"

ADesktopScreen::ADesktopScreen()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	RootComponent = DefaultSceneRoot;


	Plane->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	Plane->OverrideMaterials = TArray<UMaterialInterface*>();

	Plane->SetCollisionProfileName(FName(TEXT("NoCollision")));
	Plane->RelativeScale3D = FVector(1.920000, 1.0000000, 1.080000);
	DynamicMat = nullptr;

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Webcam/M_Webcam.M_Webcam"));
	if (FoundMaterial.Succeeded())
	{
		Material = FoundMaterial.Object;
	}

}

void ADesktopScreen::ChildBeginPlay()
{

	DynamicMat = UMaterialInstanceDynamic::Create(Material, this);
	DynamicMat->SetTextureParameterValue(FName("Tex"), VideoTexture);
	Plane->SetMaterial(0, DynamicMat);

}


