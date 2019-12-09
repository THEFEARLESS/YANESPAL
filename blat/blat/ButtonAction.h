#pragma once
struct HEAD *GetID(int x, int y) {
	struct HEAD *StructFollow = ElementDatas->EndElement;
	for (;;) {
		if (StructFollow == NULL) return 0;
		if (StructFollow->x0 <= x && StructFollow->x1 >= x && StructFollow->y0 <= y && StructFollow->y1 >= y) return StructFollow;
		StructFollow = StructFollow->prev;
	}
}
struct HEAD *GetStruct(int IDCell) {
	struct HEAD *StructFollow = ElementDatas->EndElement;
	for (;;) {
		if (StructFollow == NULL) return 0;
		if (StructFollow->IDCell == IDCell) return StructFollow;
		StructFollow = StructFollow->prev;
	}
}
int ControlButton(char *ModLoads, struct HEAD *AdressRect, HWND hwnd) {
	if (strcmp(ModLoad, "LOGIN") == 0) {
		if (strcmp(AdressRect->ModLoad, "EDITE") == 0 && AdressRect->IDCell == 3) {
			AdressUsesEdite = AdressRect;
			memset(AdressUsesEdite->Text, 0, 100);
			UpdateWindowRect(hwnd);
		}
		if (AdressRect->IDCell == 2) if (AdressRect->IDCell == 2) PostQuitMessage(0);
		if (AdressRect->IDCell == 4) {
			if (AdressUsesEdite == NULL) AdressUsesEdite = GetStruct(3);
			strcpy_s(GlobalIntegerName, AdressUsesEdite->Text);
			strcpy_s(ModLoad, "MAINMENU");
			LoadButtons(ModLoad, hwnd);
			return 0;
		}
	}
	if (strcmp(ModLoad, "MAINMENU") == 0) {
		if (AdressRect->IDCell == 2) PostQuitMessage(0);
		if (AdressRect->IDCell == 3) {
			strcpy_s(ModLoad, "SESSIONS");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 6) {
			strcpy_s(ModLoad, "ABOUTGAME");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 5) {
			strcpy_s(ModLoad, "RECORDS");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 4) {
			strcpy_s(ModLoad, "NEWGAME");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 7) {
			strcpy_s(ModLoad, "LOGIN");
			LoadButtons(ModLoad, hwnd);
		}
		return 0;
	}
	if (strcmp(ModLoad, "ABOUTGAME") == 0 || strcmp(ModLoad, "ABOUTAUTHOR") == 0 || strcmp(ModLoad, "HELP") == 0 || strcmp(ModLoad, "INTRODUCTION") == 0) {
		if (AdressRect->IDCell == 5) {
			if (strcmp(ModLoad, "ABOUTGAME") == 0) strcpy_s(ModLoad, "MAINMENU"); else strcpy_s(ModLoad, "ABOUTGAME");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 3) {
			strcpy_s(ModLoad, "HELP");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 2) {
			strcpy_s(ModLoad, "INTRODUCTION");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 4) {
			strcpy_s(ModLoad, "ABOUTAUTHOR");
			LoadButtons(ModLoad, hwnd);
		}
		return 0;
	}
	if (strcmp(ModLoad, "RECORDS") == 0 || strcmp(ModLoad, "NEWGAME") == 0) {
		if (AdressRect->IDCell == 5) {
			strcpy_s(ModLoad, "MAINMENU");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 2 || AdressRect->IDCell == 3 || AdressRect->IDCell == 4) {
			strcpy_s(ModLoad, "PROCESSGAME");
			if (AdressRect->IDCell == 2) {
				CoefficientOfSpeed = 1000;
				strcpy_s(LvlHard, "EASY");
			}
			if (AdressRect->IDCell == 3) {
				CoefficientOfSpeed = 500;
				strcpy_s(LvlHard, "NORMAL");
			}
			if (AdressRect->IDCell == 4) {
				CoefficientOfSpeed = 250;
				strcpy_s(LvlHard, "HARD");
			}
			LoadButtons(ModLoad, hwnd);
			UsesFigure[0] = 1000;
			char buffer[20] = { "USES" };
			CreateFigure(buffer, UsesFigure, hwnd);
			NextFigure[0] = -1;
			char buffer_1[20] = { "NEXT" };
			CreateFigure(buffer_1, NextFigure, hwnd);
			UpdateWindowRect(hwnd);
			SetTimer(hwnd, 1, CoefficientOfSpeed, NULL);
		}
		return 0;
	}
	if (strcmp(ModLoad, "PROCESSGAME") == 0 || strcmp(ModLoad, "ENDGAME") == 0) {
		if (AdressRect->IDCell == 3) {
			SaveGame();
			strcpy_s(ModLoad, "MAINMENU");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 5) {
			strcpy_s(ModLoad, "MAINMENU");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell == 2) {
			if (FlagPause == 0) {
				FlagPause = 1;
				KillTimer(hwnd, 1);
				return 0;
			}
			if (FlagPause == 1) {
				FlagPause = 0;
				SetTimer(hwnd, 1, CoefficientOfSpeed, NULL);
				return 0;
			}
		}
	}
	if (strcmp(ModLoad, "SESSIONS") == 0) {
		if (AdressRect->IDCell == 5) {
			strcpy_s(ModLoad, "MAINMENU");
			LoadButtons(ModLoad, hwnd);
		}
		if (AdressRect->IDCell >= 301) {
			strcpy_s(ModLoad, "PROCESSGAME");
			LoadButtons(ModLoad, hwnd);
			LoadGame(AdressRect->IDCell, hwnd);
		}
	}
}
