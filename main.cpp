#include <Windows.h>
#include "Graphics.h"

#include "Level1.h"
#include "GameController.h"

Graphics* graphics;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }


	switch (uMsg)
	{
	case WM_KEYDOWN:
		GameController::Keyboard[wParam] = true;
		return 0;

	case WM_KEYUP:
		GameController::Keyboard[wParam] = false;
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX windowsclass;
	ZeroMemory(&windowsclass, sizeof(WNDCLASSEX));
	windowsclass.cbSize = sizeof(WNDCLASSEX);
	windowsclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowsclass.hInstance = hInstance;
	windowsclass.lpfnWndProc = WindowProc;
	windowsclass.lpszClassName = "MainWindow";
	windowsclass.style = CS_HREDRAW | CS_VREDRAW;
	//windowsclass.hIcon
	//windowsclass.hIconSm

	RegisterClassEx(&windowsclass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "DirectX Mario!", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowhandle) return -1;

	graphics = new Graphics();

	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics);

	ShowWindow(windowhandle, nCmdShow);

	GameController::LoadInitialLevel(new Level1());

	// Timer
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	MSG message = { 0 };
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			// Elapsed time in micro seconds.
			QueryPerformanceCounter(&EndingTime);
			ElapsedMicroseconds.QuadPart = (((EndingTime.QuadPart - StartingTime.QuadPart) * 1000000) / Frequency.QuadPart);
			StartingTime = EndingTime; // keep last time, till next cycle


			GameController::Update((float)((double)ElapsedMicroseconds.QuadPart/(double)1000000));

			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();
		}
	}

	delete graphics;

	return 0;
}
