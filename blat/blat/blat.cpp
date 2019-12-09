// blat.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "blat.h"

#include<windows.h>
#include<ctime>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
using namespace std;
int SRC_RESOLUTION_X, SRC_RESOLUTION_Y;
int FRAP = 0, FRAP_DOUBLE_BUFFER = 0;
RGBQUAD* im;
BITMAPINFO bif;
BITMAPINFOHEADER bifs;
int CreateFigure(char* Mod, int ParamFigure[10], HWND hwnd);
void SaveGame();
void LoadGame(int IDLoad, HWND hwnd);
float CoefficientOfSpeed;
int UsesFigure[11] = { 0 }, NextFigure[11] = { 0 }, FlagShift = 65, FlagPause = 0;
char ModLoad[100] = { "LOGIN" }, LvlHard[100] = { 0 }, GlobalIntegerName[100] = { 0 };
#include"Registration.h"
struct HEAD* Score, * AdressUsesEdite = NULL;
#include"UpdateWindow.h"
#include"LoadButton.h"
#include"ButtonAction.h"
#include"GameFunction.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));
	LPCTSTR lpzClass = TEXT("My Window Class!");
	if (!RegMyWindowClass(hInstance, lpzClass)) return 1;

	// вычисление координат центра экрана
	SRC_RESOLUTION_X = 1200;
	SRC_RESOLUTION_Y = 741;
	// создание диалогового окна
	HWND hWnd = CreateWindow(lpzClass, TEXT("Dialog Window"), WS_VISIBLE, 0, 0, 1200, 741, NULL, NULL, hInstance, NULL);
	if (!hWnd) return 2;

	// цикл сообщений приложения
	MSG msg = { 0 };    // структура сообщения
	int iGetOk = 0;   // переменная состояния
	SetTimer(hWnd, 2, 100, NULL);
	im = new RGBQUAD[SRC_RESOLUTION_X * SRC_RESOLUTION_Y];
	time_t GLOBAL_TIME = time(NULL);
	while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0) // цикл сообщений
	{
		time_t LOCAL_TIME = time(NULL);
		if (LOCAL_TIME - GLOBAL_TIME >= 1) {
			FRAP_DOUBLE_BUFFER = FRAP;
			FRAP = 0;
			GLOBAL_TIME = time(NULL);
		}
		else {
			FRAP++;
		}
		if (iGetOk == -1) return 3;  // если GetMessage вернул ошибку - выход
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;  // возвращаем код завершения программы
}

ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
	WNDCLASS wcWindowClass = { 0 };
	// адрес ф-ции обработки сообщений
	wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
	// стиль окна
	wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	// дискриптор экземпляра приложения
	wcWindowClass.hInstance = hInst;
	// название класса
	wcWindowClass.lpszClassName = lpzClassName;
	// загрузка курсора
	wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// загрузка цвета окон
	wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	return RegisterClass(&wcWindowClass); // регистрация класса
}

LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// выборка и обработка сообщений
	switch (message)
	{
	case WM_LBUTTONDOWN: {
		ControlButton(ModLoad, GetID(LOWORD(lParam), HIWORD(lParam)), hWnd);
		break;
	}
	case WM_TIMER: {
		switch (wParam) {
		case 1: {
			RemoveFigure(hWnd, "DOWN");
			if (ClashOfFigure(hWnd) == 3 || ClashOfFigure(hWnd) == 2) {
				if (ClashOfFigure(hWnd) == 3) RemoveFigure(hWnd, "UP");
				UsesFigure[0]++;
				UsesFigure[1] = NextFigure[1];
				UsesFigure[2] = NextFigure[2];
				AssignNextFigure(UsesFigure[0], NextFigure[0], hWnd);
				char Buffer[30] = { "NEXT" };
				CreateFigure(Buffer, NextFigure, hWnd);
			}
			CheckCombustion(hWnd);
			UpdateWindowRect(hWnd);
			break;
		}
		}
		break;
	}
	case WM_KEYDOWN: {
		ControlKey(wParam, hWnd, 1);
		break;
	}
	case WM_KEYUP: {
		ControlKey(wParam, hWnd, 0);
		break;
	}
	case WM_PAINT: {
		LoadButtons(ModLoad, hWnd);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);  // реакция на сообщение
		break;
	default:
		// все сообщения не обработанные Вами обработает сама Windows
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}