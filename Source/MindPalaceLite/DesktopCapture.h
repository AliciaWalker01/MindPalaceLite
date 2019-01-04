// An actor class that can capture the desktop via bitblt asynchronously and
// use it to update a texture, per tick/refresh. 
//
// @ToDo: Extend this to allow us to specify which window to capture. This will require us to extend our windows
// input to access this, and may be better suited once the contextual menu system is set up (How we can set up
// more advanced control setups for within game testing)


#pragma once

#include "Windows/MinWindows.h"
#include "Engine/Texture2D.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesktopCapture.generated.h"



UCLASS()
class MINDPALACELITE_API ADesktopCapture : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADesktopCapture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	struct FUpdateTextureRegion2D* VideoUpdateTextureRegion;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Webcam)
		bool Active;

	// The rate at which the color data array and video texture is updated (in frames per second)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Webcam)
		float RefreshRate;

	// The refresh timer
	UPROPERTY(BlueprintReadWrite, Category = Webcam)
		float RefreshTimer;

	UFUNCTION(BlueprintCallable, Category = "")
		void ToggleActivation();



	float Sp;

	BITMAPINFO bi;
	BYTE* ScreenData = 0;

	void UpdateFrame(); void UpdateTexture();
	virtual void ChildBeginPlay();

	// The videos width and height (width, height) 
	UPROPERTY(BlueprintReadWrite, Category = Webcam)
		FVector2D VideoSize;

	// The current video frame's corresponding texture
	UPROPERTY(BlueprintReadOnly, Category = Webcam)
		UTexture2D* VideoTexture;

	int32 x_size, y_size;
	HBITMAP hBitmap;
	HDC hdcSys;
	HDC hdcMem;
	void *ptrBitmapPixels;
	BITMAPINFOHEADER cheese;
	HDC hwindowDC, hwindowCompatibleDC;

	int32 height, width, srcheight, srcwidth;
	HBITMAP hbwindow;

	void RunAsyncTask(HDC hdcSys, HDC hdcMem, BITMAPINFO bi, void *ptrBitmapPixels, UTexture2D* VideoTexture, FUpdateTextureRegion2D *VideoTextureUpdateRegion);


private:


};

//=======

class DCTask : public FNonAbandonableTask
{
public:


	DCTask(HDC hdcSys, HDC hdcMem, BITMAPINFO bi, void *ptrBitmapPixels, UTexture2D* VideoTexture, FUpdateTextureRegion2D *VideoTextureUpdateRegion);

	~DCTask();

	//Required by UE4
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(DCTask, STATGROUP_ThreadPoolAsyncTasks)
	}
	bool On, Insane;
	HDC hSys, hMem;
	BITMAPINFO b;
	void *pix;
	UTexture2D *Vid;
	FUpdateTextureRegion2D *UR;

	void DoWork();
	void DoWorkMain();

};

