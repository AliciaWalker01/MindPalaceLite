// Fill out your copyright notice in the Description page of Project Settings.

// This is an implementation of http://depts.washington.edu/madlab/proj/dollar/qdollar.html
// to be usable within Unreal Engines C++ requirements. A few custom USTRUCTS are created to allow
// storage of point data, 2D integer arrays and templates.
// All functions are callable in blueprints for debugging purposes and a form of access by higher-leve
// scripts. 
// The purpose of this is to use a point-cloud gesture recognizer as a fast form of live character recognition
// for handwriting input in VR
//
//
// @ToDo: Generate an asynchronous implementation that will allow us to stream the next best answers (for auto-learning)
// and to stop us blocking the main thread (even though it is very, very fast at recognition, micro-stuttering can become a problem with
// larger amounts of templates to search through). It will allow us to search through separate templates, e.g. lowercase, uppercase, symbols,
// greek etc, without becoming too performance demanding by having them all in one template.

#pragma once

#include "CoreMinimal.h"
#include <list>
#include <limits>
#include <algorithm>
#include <cmath>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DollarQLibrary.generated.h"


/**
 *
 */

const int SAMPRES = 32;
const int LUTSIZE = 64;
const int MAXINTCO = 1024;
const int LUTSF = 16;

// A Point. TArrays are used in BP to generate complete sets of points
USTRUCT(BlueprintType)
struct FDPoint
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "DPoint")
		float X;

	UPROPERTY(BlueprintReadWrite, Category = "DPoint")
		float Y;

	UPROPERTY(BlueprintReadWrite, Category = "DPoint")
		int32 StrokeID;

	UPROPERTY(BlueprintReadWrite, Category = "DPoint")
		int32 intX;
	UPROPERTY(BlueprintReadWrite, Category = "DPoint")
		int32 intY;
};

// Our Look-Up-Tables are in integer arrays
USTRUCT(BlueprintType)
struct FIntArray
{

	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "Cheese")
		TArray<int32> A;
};

// our templates are stored in arrays of points, a look up table per point and their name
USTRUCT(BlueprintType)
struct FDPoints
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "DPoints")
		TArray<FDPoint> points;

	UPROPERTY(BlueprintReadWrite, Category = "DPoints")
		TArray<FIntArray> LUT;

	UPROPERTY(BlueprintReadWrite, Category = "Dpoints")
		FString name;

};


UCLASS()
class MINDPALACELITE_API UDollarQLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Dollar")
		static float SqrEuclideanDistance(FDPoint a, FDPoint b);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static float EuclideanDistance(FDPoint a, FDPoint b);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static float PathLength(TArray<FDPoint> points);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static TArray<FIntArray> ConstructLUT(TArray<FDPoint> points, int32 n, int32 m, int32 SF);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static TArray<FDPoint> Resample(TArray<FDPoint> points, int32 n);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static TArray<FDPoint> Scale(TArray<FDPoint> points);

	UFUNCTION(BlueprintPure, Category = "Test")
		static TArray<FDPoint> GenerateSquare();

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static FDPoint Centroid(TArray<FDPoint> points);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static TArray<FDPoint> TranslateTo(TArray<FDPoint> points, FDPoint point);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static TArray<FDPoint> TransformCoordsToIntegers(TArray<FDPoint> points, int32 Max_Int_Coordinates);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static TArray<float> ComputeLowerBound(TArray<FDPoint> points1, TArray<FDPoint> points2, TArray<FIntArray> LUT, int32 step, int32 SF);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static float CloudDistance(TArray<FDPoint> points1, TArray<FDPoint> points2, int32 startIndex, float minSoFar, bool UseEarlyAbandoning);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static float CloudMatch(TArray<FDPoint> points1, TArray<FDPoint> points2, TArray<FIntArray> LUT1, TArray<FIntArray> LUT2, float minSoFar, bool UseLowerBounding, bool UseEarlyAbandoning, int32 SF);

	UFUNCTION(BlueprintCallable, Category = "Dollar")
		static TArray<FDPoint> Normalise(TArray<FDPoint> points, int32 n, int32 m, int32 maxintcoords);

	UFUNCTION(BluePrintCallable, Category = "Dollar")
		static FString Recognizer(TArray<FDPoint> NormalisedPoints, TArray<FIntArray> InputLUT, TArray<FDPoints> NormalisedTemplates, int32 n, int32 m, int32 maxintcoords, bool UseLowerBounding, bool UseEarlyAbandoning);



};
