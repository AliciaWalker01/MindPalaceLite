// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//#include "Windows.h"
//#include "Windows/WindowsSystemIncludes.h"

#include "Windows/MinWindows.h"
#include "WindowsInput.generated.h"




/**
 *
 */



UCLASS()
class MINDPALACELITE_API UWindowsInput : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void Test(int32 key);

	UFUNCTION(BlueprintPure, Category = "WindowsInput")
		static int32 VirtualKey(FString key);

	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void MoveMouse(int32 x, int32 y);

	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void LMouseClickDown();
	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void LMouseClickUp();

	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void RMouseClickDown();
	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void RMouseClickUp();

	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void MMouseClickDown();
	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void MMouseClickUp();

	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void GameFocus();
	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void InitWindow();
	UFUNCTION(BlueprintCallable, Category = "WindowsInput")
		static void DesktopFocus();


};
