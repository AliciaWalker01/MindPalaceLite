// Fill out your copyright notice in the Description page of Project Settings.

#include "DesktopCapture.h"



// Sets default values
ADesktopCapture::ADesktopCapture()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Active = true;

	RefreshRate = 20; VideoSize = FVector2D(0, 0);
	RefreshTimer = 0.0f;


}

// Called when the game starts or when spawned
void ADesktopCapture::BeginPlay()
{
	Super::BeginPlay();


	x_size = 1920;
	y_size = 1080;

	hdcSys = GetDC(GetDesktopWindow());

	hdcMem = CreateCompatibleDC(hdcSys);
	SetStretchBltMode(hdcMem, COLORONCOLOR);

	//BITMAPINFO bi;
	HDC hdc;
	ZeroMemory(&bi, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = x_size;
	bi.bmiHeader.biHeight = -y_size;  //negative so (0,0) is at top left
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;

	hdc = GetDC(NULL);
	hBitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &ptrBitmapPixels, NULL, 0);
	// ^^ The output: hBitmap & ptrBitmapPixels


	// Set hBitmap in the hdcMem 
	SelectObject(hdcMem, hBitmap);


	UpdateFrame();
	VideoSize = FVector2D(x_size, y_size);


	VideoTexture = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y);
	Sp = 0;

	VideoTexture->CompressionSettings = TextureCompressionSettings::TC_MAX;
#define UpdateResource UpdateResource
	VideoTexture->UpdateResource();
	VideoUpdateTextureRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, VideoSize.X, VideoSize.Y);

	UpdateTexture();

	ChildBeginPlay();
	RunAsyncTask(hdcSys, hdcMem, bi, ptrBitmapPixels, VideoTexture, VideoUpdateTextureRegion);

}

// Called every frame
void ADesktopCapture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RefreshTimer += DeltaTime;

	if (Active)
	{
		if (RefreshTimer >= 1.0f / RefreshRate)
		{
			RunAsyncTask(hdcSys, hdcMem, bi, ptrBitmapPixels, VideoTexture, VideoUpdateTextureRegion);
			RefreshTimer -= 1.0f / RefreshRate;
		}

	}

}


void ADesktopCapture::ToggleActivation()
{
	if (Active == true)
	{
		Active = false;
	}
	else if (Active == false)
	{
		Active = true;
	}
}


void ADesktopCapture::UpdateFrame()
{
	BitBlt(hdcMem, 0, 0, x_size, y_size, hdcSys, 0, 0, SRCCOPY);

}


void ADesktopCapture::UpdateTexture() {

	VideoTexture->UpdateTextureRegions((int32)0, (uint32)1, VideoUpdateTextureRegion, (uint32)(4 * VideoSize.X), (uint32)4, (uint8*)/*&ptrData);*/ptrBitmapPixels);//Data.GetData());

}

void ADesktopCapture::ChildBeginPlay()
{
}





void ADesktopCapture::RunAsyncTask(HDC hdcSys, HDC hdcMem, BITMAPINFO bi, void * ptrBitmapPixels, UTexture2D * VideoTexture, FUpdateTextureRegion2D * VideoTextureUpdateRegion)
{
	(new FAutoDeleteAsyncTask<DCTask>(hdcSys, hdcMem, bi, ptrBitmapPixels, VideoTexture, VideoTextureUpdateRegion))->StartBackgroundTask();
}


DCTask::DCTask(HDC hdcSys, HDC hdcMem, BITMAPINFO bi, void * ptrBitmapPixels, UTexture2D * VideoTexture, FUpdateTextureRegion2D *VideoTextureUpdateRegion)
{
	On = true;
	hSys = hdcSys;
	hMem = hdcMem;
	b = bi;
	pix = ptrBitmapPixels;
	Vid = VideoTexture;
	UR = VideoTextureUpdateRegion;

}

DCTask::~DCTask()
{
}

void DCTask::DoWork()
{

	BitBlt(hMem, 0, 0, 1920, 1080, hSys, 0, 0, SRCCOPY);
	Vid->UpdateTextureRegions((int32)0, (uint32)1, UR, (uint32)(4 * 1920), (uint32)4, (uint8*)pix);

}

void DCTask::DoWorkMain()
{
	DoWork();
}
