// Fill out your copyright notice in the Description page of Project Settings.

#include "WindowsInput.h"


HWND GameWindow;

void UWindowsInput::Test(int32 key)
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "A" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));




}

int32 UWindowsInput::VirtualKey(FString key)
{
	int32 output;
	if (key == "0") output = 0x30;
	else if (key == "1") output = 0x31;
	else if (key == "2") output = 0x32;
	else if (key == "3") output = 0x33;
	else if (key == "4") output = 0x34;
	else if (key == "5") output = 0x35;
	else if (key == "6") output = 0x36;
	else if (key == "7") output = 0x37;
	else if (key == "8") output = 0x38;
	else if (key == "9") output = 0x39;
	else if (key == "a") output = 0x41;
	else if (key == "b") output = 0x42;
	else if (key == "c") output = 0x43;
	else if (key == "d") output = 0x44;
	else if (key == "e") output = 0x45;
	else if (key == "f") output = 0x46;
	else if (key == "g") output = 0x47;
	else if (key == "h") output = 0x48;
	else if (key == "i") output = 0x49;
	else if (key == "j") output = 0x4A;
	else if (key == "k") output = 0x4B;
	else if (key == "l") output = 0x4C;
	else if (key == "m") output = 0x4D;
	else if (key == "n") output = 0x4E;
	else if (key == "o") output = 0x4F;
	else if (key == "p") output = 0x50;
	else if (key == "q") output = 0x51;
	else if (key == "r") output = 0x52;
	else if (key == "s") output = 0x53;
	else if (key == "t") output = 0x54;
	else if (key == "u") output = 0x55;
	else if (key == "v") output = 0x56;
	else if (key == "w") output = 0x57;
	else if (key == "x") output = 0x58;
	else if (key == "y") output = 0x59;
	else if (key == "z") output = 0x5A;
	else if (key == "delete") output = 0x2E;
	else if (key == "backspace") output = 0x08;
	else if (key == "enter") output = 0x0D;
	else if (key == "space") output = 0x20;
	else if (key == "up") output = 0x26;
	else if (key == "left") output = 0x25;
	else if (key == "right") output = 0x27;
	else if (key == "down") output = 0x28;

	return output;
}

void UWindowsInput::MoveMouse(int32 x, int32 y)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
	input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &input, sizeof(input));
}

void UWindowsInput::LMouseClickDown()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	//input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
	//input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
	input.mi.dwFlags = MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(input));
}

void UWindowsInput::LMouseClickUp()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	//input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
	//input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
	input.mi.dwFlags = MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(input));
}

void UWindowsInput::RMouseClickDown()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	//input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
	//input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
	input.mi.dwFlags = MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input, sizeof(input));
}

void UWindowsInput::RMouseClickUp()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	//input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
	//input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
	input.mi.dwFlags = MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(input));
}

void UWindowsInput::MMouseClickDown()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dwFlags = MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_MIDDLEDOWN;
	SendInput(1, &input, sizeof(input));

}

void UWindowsInput::MMouseClickUp()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dwFlags = MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_MIDDLEUP;
	SendInput(1, &input, sizeof(input));
}

void UWindowsInput::GameFocus()
{

	SetForegroundWindow(GameWindow);

}

void UWindowsInput::InitWindow()
{
	GameWindow = GetForegroundWindow();
}

void UWindowsInput::DesktopFocus()
{
	SetForegroundWindow(GetDesktopWindow());
}
