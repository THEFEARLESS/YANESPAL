#pragma once
#include<fstream>
#include<cstdio>
using namespace std;
void LoadButtons(char *ModLoad, HWND hwnd) {
	ElementDatas = NULL;

	if (strcmp(ModLoad, "LOGIN") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\fon.bmp", 1, 0, 0);
		RegistrationObject(960, 10, 1190, 100, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Exit.bmp", 2, 0, 0);
		RegistrationObject(465, 512, 705, 562, 255, 255, "EDITE", "Введите ваше имя           ", "ROUNDRECT", 3, 30, 12);
		RegistrationObject(380, 560, 810, 670, 6579455, 16777215, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Prodolzhit(N).bmp", 4, 0, 0);
	}
	if (strcmp(ModLoad, "MAINMENU") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\menu.bmp", 1, 0, 0);
		RegistrationObject(920, 20, 1200, 85, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\exit.bmp", 2, 0, 0);
		RegistrationObject(335, 355, 890, 435, 0, 0, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Zagruzit_igru(N).bmp", 3, 0, 0);
		RegistrationObject(345, 255, 870, 335, 0, 0, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Novaya_igra(N).bmp", 4, 0, 0);
		RegistrationObject(385, 460, 820, 535, 0, 0, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Rekordy(N).bmp", 5, 0, 0);
		RegistrationObject(385, 565, 820, 640, 0, 0, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Ob_igre(N).bmp", 6, 0, 0);
		RegistrationObject(630, 20, 930, 70, 0, 0, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Smena_polzovatelya(N).bmp", 7, 0, 0);
	}
	if (strcmp(ModLoad, "ABOUTGAME") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\AboutGame.bmp", 7, 0, 0);
		RegistrationObject(250, 260, 890, 380, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Introduction(N).bmp", 2, 20, 9);
		RegistrationObject(40, 455, 540, 525, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Help(N).bmp", 3, 20, 9);
		RegistrationObject(600, 455, 1150, 525, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\author(N).bmp", 4, 20, 9);
		RegistrationObject(850, 10, 1180, 110, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\back.bmp", 5, 0, 0);
	}
	if (strcmp(ModLoad, "ABOUTAUTHOR") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\Author.bmp", 1, 0, 0);
		RegistrationObject(1030, 20, 1155, 50, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\back.bmp", 5, 0, 0);
	}
	if (strcmp(ModLoad, "HELP") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\Help.bmp", 1, 0, 0);
		RegistrationObject(980, 20, 1155, 50, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\back.bmp", 5, 0, 0);
	}
	if (strcmp(ModLoad, "INTRODUCTION") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\Introduction.bmp", 1, 0, 0);
		RegistrationObject(950, 640, 1180, 690, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\back.bmp", 5, 0, 0);
	}
	if (strcmp(ModLoad, "NEWGAME") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\fon1.bmp", 1, 0, 0);
		RegistrationObject(920, 15, 1165, 90, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\back.bmp", 5, 0, 0);
		RegistrationObject(410, 280, 730, 350, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\easy.bmp", 2, 20, 9);
		RegistrationObject(370, 360, 820, 440, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\normal.bmp", 3, 20, 9);
		RegistrationObject(370, 450, 820, 530, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\hard.bmp", 4, 20, 9);
	}
	if (strcmp(ModLoad, "PROCESSGAME") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\gamefon.bmp", 1, 0, 0);
		RegistrationObject(860, 20, 1160, 120, 16777216, 0, "DRAWING", "Пауза/Пуск ", "ROUNDRECT", 2, 20, 9);
		RegistrationObject(930, 130, 1160, 210, 16777216, 0, "DRAWING", "Выйти ", "ROUNDRECT", 5, 20, 9);
		RegistrationObject(930, 500, 1160, 660, 16777216, 0, "DRAWING", "Сохранить и выйти   ", "ROUNDRECT", 3, 20, 9);
		Score = RegistrationObject(100, 350, 150, 430, 255, 16777215, "TEXT_BACKGROUND_OFF", "0", "ROUNDRECT", 6, 40, 18);
		int IDRecord = 100, X = 425, Y = 0;
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 10; x++) {
				RegistrationObject(X, Y, X + 35, Y + 35, 16777215, 0, "DRAWING", "", "RECTANGLE", IDRecord, 0, 0);
				X = X + 35;
				IDRecord++;
			}
			X = 425;
			Y = Y + 35;
		}
	}
	if (strcmp(ModLoad, "ENDGAME") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\Endgamefon.bmp", 1, 0, 0);
		RegistrationObject(1000, 100, 1155, 160, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\Exit.bmp", 5, 20, 9);
		Score = RegistrationObject(20, 350, 100, 415, 255, 16777215, "TEXT_BACKGROUND_OFF", Score->Text, "ROUNDRECT", 6, 40, 18);
		RegistrationObject(160, 360, 400, 415, 65520, 16777215, "TEXT_BACKGROUND_OFF", GlobalIntegerName, "ROUNDRECT", 6, 40, 18);
	}
	if (strcmp(ModLoad, "RECORDS") == 0) {
		int IDRecord = 6, x = 450, y = 195;
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\Records.bmp", 8, 0, 0);
		RegistrationObject(980, 10, 1190, 80, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\back.bmp", 5, 0, 0);
		ifstream LoadResultFromFile;
		LoadResultFromFile.open("data\\text file\\Score.txt");
		for (;;) {
			char TextInLoadFile[100] = { 0 }, NamePlayer[100] = { 0 }, PlayerScore[100] = { 0 };
			int ValueCell = 0;
			LoadResultFromFile.getline(TextInLoadFile, 200);
			if (LoadResultFromFile.eof()) break;
			if (strlen(TextInLoadFile) < 2) continue;
			for (int n = 0;; n++) {
				if (TextInLoadFile[n] == '.') {
					for (int N = n + 1;; N++) {
						if (N >= strlen(TextInLoadFile)) break;
						PlayerScore[ValueCell] = TextInLoadFile[N];
						ValueCell++;
					}
					break;
				}
				NamePlayer[n] = TextInLoadFile[n];
			}
			RegistrationObject(x, y, x + 170, y + 30, 6579455, 16777215, "TEXT_BACKGROUND_OFF", NamePlayer, "ROUNDRECT", IDRecord, 20, 9);
			IDRecord++;
			x = x + 180;
			RegistrationObject(x, y, x + 170, y + 30, 65520, 16777215, "TEXT_BACKGROUND_OFF", PlayerScore, "ROUNDRECT", IDRecord, 20, 9);
			IDRecord++;
			x = 450;
			y = y + 35;
			if (LoadResultFromFile.eof()) break;
		}
		LoadResultFromFile.close();
	}
	if (strcmp(ModLoad, "SESSIONS") == 0) {
		RegistrationObject(0, 0, 1200, 700, 6579455, 16777215, "PICTERES", "", "data\\capture\\fon2.bmp", 1, 20, 9);
		RegistrationObject(980, 10, 1190, 80, 1, 1, "PICTERES_BACKGROUND_OFF", "", "data\\capture\\back.bmp", 5, 0, 0);
		ifstream LoadResultFromFile;
		LoadResultFromFile.open("data\\text file\\SavedGame.txt");
		int X = 300, Y = 230, ID = 301;
		for (;;) {
			char TextInLoadFile[100] = { 0 }, BufferAccaunt[100] = { 0 };
			LoadResultFromFile.getline(TextInLoadFile, 200);
			if (strncmp(TextInLoadFile, "START,", 6) == 0) {
				int N = 0;
				for (int n = 6;; n++) {
					if (TextInLoadFile[n] == ',') break;
					BufferAccaunt[N] = TextInLoadFile[n];
					N++;
				}
				RegistrationObject(X, Y, X + 600, Y + 80, 16777215, 16777215, "TEXT_BACKGROUND_OFF", BufferAccaunt, "ROUNDRECT", ID, 40, 18);
				Y = Y + 40;
				ID++;
			}
			if (LoadResultFromFile.eof()) break;
		}
	}
	UpdateWindowRect(hwnd);
}
