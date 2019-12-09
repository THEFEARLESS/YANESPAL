#pragma once
int CreateFigure(char *Mod, int ParamFigure[10], HWND hwnd);
int CreateLoadFugire(char TextInLoadFile[200], HWND hwnd) {
	if (strncmp(TextInLoadFile, "END,", 4) != 0) {
		int Value = 0, MassiveDataFigure[100] = { 0 }, N = 0;
		char Buffers[100] = { 0 };
		for (int n = 0; n < strlen(TextInLoadFile); n++) {
			if (TextInLoadFile[n] == ',') {
				if (Value == 9 && strncmp(TextInLoadFile, "START,", 6) == 0) strcpy_s(LvlHard, Buffers);
				MassiveDataFigure[Value] = atoi(Buffers);
				memset(Buffers, 0, 100);
				N = 0;
				Value++;
				continue;
			}
			Buffers[N] = TextInLoadFile[n];
			N++;
		}
		if (strncmp(TextInLoadFile, "START,", 6) == 0) {
			char Buffer[100] = { 0 };
			_itoa_s(MassiveDataFigure[2], Buffer, 10);
			strcpy_s(Score->Text, Buffer);
			UsesFigure[0] = MassiveDataFigure[3];
			UsesFigure[1] = MassiveDataFigure[4];
			UsesFigure[2] = MassiveDataFigure[5];
			NextFigure[0] = MassiveDataFigure[6];
			NextFigure[1] = MassiveDataFigure[7];
			NextFigure[2] = MassiveDataFigure[8];
			CoefficientOfSpeed = MassiveDataFigure[10];
			char buffer_2[20] = { "FromFile" };
			CreateFigure(buffer_2, NextFigure, hwnd);
		}
		else RegistrationObject(MassiveDataFigure[0], MassiveDataFigure[2], MassiveDataFigure[1], MassiveDataFigure[3], MassiveDataFigure[4], MassiveDataFigure[5], "DRAWING", "", "RECTANGLE", MassiveDataFigure[6], 0, 0);
	}
	if (strncmp(TextInLoadFile, "END,", 4) == 0) return 3;
}
void LoadGame(int IDLoad, HWND hwnd) {
	ifstream LoadResultFromFile;
	LoadResultFromFile.open("data\\text file\\SavedGame.txt");
	int ID = 300;
	for (;;) {
		char TextInLoadFile[200] = { 0 }, BufferAccaunt[100] = { 0 };
		LoadResultFromFile.getline(TextInLoadFile, 200);
		if (strncmp(TextInLoadFile, "START,", 6) == 0) ID++;
		if (ID == IDLoad) if (CreateLoadFugire(TextInLoadFile, hwnd) == 3) break;
		if (LoadResultFromFile.eof()) break;
	}
	UpdateWindowRect(hwnd);
	SetTimer(hwnd, 1, CoefficientOfSpeed, NULL);
}
void SaveGame() {
	ofstream LoadResultFromFile;
	LoadResultFromFile.open("data\\text file\\SavedGame.txt", ios_base::app);
	LoadResultFromFile << "START," << GlobalIntegerName << "," << Score->Text << "," << UsesFigure[0] << "," << UsesFigure[1] << "," << UsesFigure[2] << "," << NextFigure[0] << "," << NextFigure[1] << "," << NextFigure[2] << "," << LvlHard << "," << CoefficientOfSpeed << "," << "\n";
	struct HEAD *GoStruct = ElementDatas;
	for (;;) {
		if (GoStruct == NULL) break;
		if (GoStruct->IDCell > 300) {
			LoadResultFromFile << GoStruct->x0 << "," << GoStruct->x1 << "," << GoStruct->y0 << "," << GoStruct->y1 << "," << GoStruct->BackGroundColor << "," << GoStruct->LineColor << "," << GoStruct->IDCell << ",\n";
		}
		GoStruct = GoStruct->next;
	}
	LoadResultFromFile << "END,\n";
	LoadResultFromFile.close();
}
void AddScoreInFile() {
	ofstream LoadResultFromFile;
	LoadResultFromFile.open("data\\text file\\Score.txt", ios_base::app);
	LoadResultFromFile << "\n" << GlobalIntegerName << "." << Score->Text << "\n";
	LoadResultFromFile.close();
}
void DelFromCoordinat(int Y0, int Y1) {
	struct HEAD *GoStruct = ElementDatas, *next, *prev;
	for (;;) {
		if (GoStruct == NULL) break;
		if (GoStruct->y0 == Y0 && GoStruct->y1 == Y1 && GoStruct->IDCell > 300) {
			prev = GoStruct->prev;
			if (GoStruct->next == NULL) {
				prev->next = NULL;
				break;
			}
			next = GoStruct->next;
			prev->next = next;
			next->prev = prev;
		}
		GoStruct = GoStruct->next;
	}
}
void RemoveFigure_GAME(int Y0, int Y1) {
	DelFromCoordinat(Y0, Y1);
	struct HEAD *StructFollow = ElementDatas;
	for (;;) {
		if (Y0 == 0) break;
		if (StructFollow == NULL) {
			Y0 = Y0 - 35;
			Y1 = Y1 - 35;
			StructFollow = ElementDatas;
		}
		if (StructFollow->IDCell != UsesFigure[0] && StructFollow->IDCell > 300) {
			if (StructFollow->y0 == Y0 && StructFollow->y1 == Y1) {
				StructFollow->y0 = StructFollow->y0 + 35;
				StructFollow->y1 = StructFollow->y1 + 35;
			}
		}
		StructFollow = StructFollow->next;
	}
}
void CheckCombustion(HWND hwnd) {
	struct HEAD *StructFollow = ElementDatas;
	int Y1 = 700, Y0 = 665, N = 0;
	for (;;) {
		if (Y1 == 0) break;
		if (StructFollow == NULL) {
			if (N == 10) {
				int ScoreValue = atoi(Score->Text);
				ScoreValue++;
				char Buffer[100] = { 0 };
				_itoa_s(ScoreValue, Buffer, 10);
				strcpy_s(Score->Text, Buffer);
				RemoveFigure_GAME(Y0, Y1);
				if (strcmp(LvlHard, "EASY") == 0) CoefficientOfSpeed = CoefficientOfSpeed / 1.01;
				if (strcmp(LvlHard, "NORMAL") == 0) CoefficientOfSpeed = CoefficientOfSpeed / 1.01;
				if (strcmp(LvlHard, "HARD") == 0) CoefficientOfSpeed = CoefficientOfSpeed / 1.01;
				KillTimer(hwnd, 1);
				SetTimer(hwnd, 1, CoefficientOfSpeed, NULL);
				break;
			}
			Y0 = Y0 - 35;
			Y1 = Y1 - 35;
			N = 0;
			StructFollow = ElementDatas;
		}
		if (StructFollow->IDCell != UsesFigure[0] && StructFollow->IDCell > 300) {
			if (StructFollow->y0 == Y0 && StructFollow->y1 == Y1) N++;
		}
		StructFollow = StructFollow->next;
	}
}
int ClashOfFigure(HWND hwnd) {
	struct HEAD *StructFollow = ElementDatas, *StructFollowAim = ElementDatas;
	for (;;) {
		if (StructFollowAim == NULL) break;
		if (StructFollowAim->IDCell != UsesFigure[0] && StructFollowAim->IDCell > 300) {
			for (;;) {
				if (StructFollow == NULL) break;
				if (StructFollow->IDCell == UsesFigure[0]) {
					if (StructFollow->x0 == StructFollowAim->x0&&StructFollow->y0 == StructFollowAim->y0&&StructFollow->x1 == StructFollowAim->x1&&StructFollow->y1 == StructFollowAim->y1) {
						if (StructFollowAim->y0 == StructFollow->y0&&StructFollow->y0 == 35) {
							strcpy_s(ModLoad, "ENDGAME");
							LoadButtons(ModLoad, hwnd);
							AddScoreInFile();
							return 4;
						}
						return 3;
					}
				}
				StructFollow = StructFollow->next;
			}
			StructFollow = ElementDatas;
		}
		StructFollowAim = StructFollowAim->next;
	}
	StructFollowAim = ElementDatas;
	for (;;) {
		if (StructFollowAim == NULL) break;
		if (StructFollowAim->IDCell > 300 && StructFollowAim->IDCell == UsesFigure[0] && ((StructFollowAim->x0 <= 390 || StructFollowAim->x0 >= 765))) return 1;
		if (StructFollowAim->IDCell > 300 && StructFollowAim->IDCell == UsesFigure[0] && StructFollowAim->y1 >= 700) return 2;
		StructFollowAim = StructFollowAim->next;
	}
}
void AddFigureNxNy(int Rotation[11], int ControlWparam[11]) {
	int ColorRandBackGround = rand() % 16777215, ColorRandLine = rand() % 16777215;
	for (int n = 0; n < 8; n++) {
		if (ControlWparam[0] == -1) RegistrationObject(35 * Rotation[n] + 565 + 300, 35 * Rotation[n + 1] + 300, 35 * Rotation[n] + 35 + 565 + 300, 35 * Rotation[n + 1] + 35 + 300, ColorRandBackGround, ColorRandLine, "DRAWING", "", "RECTANGLE", ControlWparam[0], 0, 0);  else RegistrationObject(35 * Rotation[n] + 565, 35 * Rotation[n + 1], 35 * Rotation[n] + 35 + 565, 35 * Rotation[n + 1] + 35, ColorRandBackGround, ColorRandLine, "DRAWING", "", "RECTANGLE", ControlWparam[0], 0, 0);
		n++;
	}
}
int CreateFigure(char *Mod, int ParamFigure[10], HWND hwnd) {
	int Rotation1[7][10] = { {0,0,0,1,0,2,0,3},{0,0,1,0,0,1,1,1},{0,1,1,0,1,1,2,1},{0,0,1,0,1,1,1,2},{0,0,1,0,0,1,0,2},{0,1,1,1,1,0,2,0},{0,0,1,0,1,1,2,1} }, Rotation2[7][10] = { {0,0,1,0,2,0,3,0},{0,0,1,0,0,1,1,1},{0,0,0,1,1,1,0,2},{0,1,1,1,2,1,2,0},{0,0,1,0,2,0,2,1},{0,0,0,1,1,1,1,2},{0,1,0,2,1,0,1,1} }, Rotation3[7][10] = { {0,0,0,1,0,2,0,3},{0,0,1,0,0,1,1,1},{0,0,1,0,2,0,1,1},{0,0,0,1,0,2,1,2},{0,2,1,0,1,1,1,2},{0,1,1,1,1,0,2,0},{0,0,1,0,1,1,2,1} }, Rotation4[7][10] = { {0,0,1,0,2,0,3,0},{0,0,1,0,0,1,1,1},{0,1,1,0,1,1,1,2},{0,0,1,0,2,0,0,1},{0,0,0,1,1,1,2,1},{0,0,0,1,1,1,1,2},{0,1,0,2,1,0,1,1} };
	int RotationRand = rand() % 3 + 1, FigureRand = rand() % 7;
	if (strcmp(Mod, "USES") == 0) {
		UsesFigure[1] = RotationRand;
		UsesFigure[2] = FigureRand;
	}
	else {
		if (strcmp(Mod, "FromFile") != 0) {
			NextFigure[1] = RotationRand;
			NextFigure[2] = FigureRand;
		}
	}
	switch (RotationRand) {
	case 1: {
		AddFigureNxNy(Rotation1[FigureRand], ParamFigure);
		break;
	}
	case 2: {
		AddFigureNxNy(Rotation2[FigureRand], ParamFigure);
		break;
	}
	case 3: {
		AddFigureNxNy(Rotation3[FigureRand], ParamFigure);
		break;
	}
	case 4: {
		AddFigureNxNy(Rotation4[FigureRand], ParamFigure);
		break;
	}
	}
	if (ClashOfFigure(hwnd) == 4) return 0;
}
void AssignNextFigure(int IDUse, int IDNext, HWND hwnd) {
	struct HEAD *StructFollow = ElementDatas;
	for (;;) {
		if (StructFollow == NULL) break;
		if (StructFollow->IDCell == IDNext) {
			StructFollow->IDCell = IDUse;
			StructFollow->y0 = StructFollow->y0 - 300;
			StructFollow->y1 = StructFollow->y1 - 300;
			StructFollow->x0 = StructFollow->x0 - 300;
			StructFollow->x1 = StructFollow->x1 - 300;
		}
		StructFollow = StructFollow->next;
	}
	UpdateWindowRect(hwnd);
}
void RemoveFigure(HWND hwnd,const char ModRemove[10]) {
	struct HEAD *StructFollow = ElementDatas;
	for (;;) {
		if (StructFollow == NULL) break;
		if (StructFollow->IDCell == UsesFigure[0]) {
			if (strcmp(ModRemove, "UP") == 0) {
				StructFollow->y0 = StructFollow->y0 - 35;
				StructFollow->y1 = StructFollow->y1 - 35;
			}
			if (strcmp(ModRemove, "DOWN") == 0) {
				StructFollow->y0 = StructFollow->y0 + 35;
				StructFollow->y1 = StructFollow->y1 + 35;
			}
			if (strcmp(ModRemove, "LEFT") == 0) {
				StructFollow->x0 = StructFollow->x0 - 35;
				StructFollow->x1 = StructFollow->x1 - 35;
			}
			if (strcmp(ModRemove, "RIGHT") == 0) {
				StructFollow->x0 = StructFollow->x0 + 35;
				StructFollow->x1 = StructFollow->x1 + 35;
			}
		}
		StructFollow = StructFollow->next;
	}
}
void DeleteFigure(int IDDelite) {
	struct HEAD *GoStruct = ElementDatas, *next, *prev;
	for (;;) {
		if (GoStruct == NULL) break;
		if (GoStruct->IDCell == IDDelite) {
			prev = GoStruct->prev;
			if (GoStruct->next == NULL) {
				prev->next = NULL;
				break;
			}
			next = GoStruct->next;
			prev->next = next;
			next->prev = prev;
		}
		GoStruct = GoStruct->next;
	}
}
void AddFigureRotate(int Rotation[11], int ControlWparam[11]) {
	struct HEAD *StructFollow = ElementDatas;
	int ColorRandBackGround, ColorRandLine;
	int Xmin = -1, Ymin = -1;
	for (;;) {
		if (StructFollow == NULL) break;
		if (StructFollow->IDCell == UsesFigure[0]) {
			if (Xmin == -1) {
				Xmin = StructFollow->x0;
				Ymin = StructFollow->y0;
				ColorRandBackGround = StructFollow->BackGroundColor;
				ColorRandLine = StructFollow->LineColor;
			}
			else {
				if (Xmin > StructFollow->x0) {
					Xmin = StructFollow->x0;
					Ymin = StructFollow->y0;
					ColorRandBackGround = StructFollow->BackGroundColor;
					ColorRandLine = StructFollow->LineColor;
				}
				if (Xmin == StructFollow->x0) {
					if (Ymin > StructFollow->y0) {
						Xmin = StructFollow->x0;
						Ymin = StructFollow->y0;
						ColorRandBackGround = StructFollow->BackGroundColor;
						ColorRandLine = StructFollow->LineColor;
					}
				}
			}
		}
		StructFollow = StructFollow->next;
	}
	if (ControlWparam[2] == 2 && ((ControlWparam[1] == 2) || (ControlWparam[1] == 1))) Ymin = Ymin - 35;
	if ((ControlWparam[2] == 5 || ControlWparam[2] == 6) && ((ControlWparam[1] == 2) || (ControlWparam[1] == 4))) Ymin = Ymin - 35;
	if (ControlWparam[2] == 3 && ((ControlWparam[1] == 1))) Ymin = Ymin - 35;
	if (ControlWparam[2] == 4 && ((ControlWparam[1] == 1) || (ControlWparam[1] == 3))) Ymin = Ymin - 35;
	DeleteFigure(UsesFigure[0]);
	for (int n = 0; n < 8; n++) {
		RegistrationObject(35 * Rotation[n] + Xmin, 35 * Rotation[n + 1] + Ymin, 35 * Rotation[n] + 35 + Xmin, 35 * Rotation[n + 1] + 35 + Ymin, ColorRandBackGround, ColorRandLine, "DRAWING", "", "RECTANGLE", ControlWparam[0], 0, 0);
		n++;
	}
}
void ChangeRotation(HWND hwnd,const char ModRotation[15]) {
	int Rotation1[7][10] = { {0,0,0,1,0,2,0,3},{0,0,1,0,0,1,1,1},{0,1,1,0,1,1,2,1},{0,0,1,0,1,1,1,2},{0,0,1,0,0,1,0,2},{0,1,1,1,1,0,2,0},{0,0,1,0,1,1,2,1} }, Rotation2[7][10] = { {0,0,1,0,2,0,3,0},{0,0,1,0,0,1,1,1},{0,0,0,1,1,1,0,2},{0,1,1,1,2,1,2,0},{0,0,1,0,2,0,2,1},{0,0,0,1,1,1,1,2},{0,1,0,2,1,0,1,1} }, Rotation3[7][10] = { {0,0,0,1,0,2,0,3},{0,0,1,0,0,1,1,1},{0,0,1,0,2,0,1,1},{0,0,0,1,0,2,1,2},{0,2,1,0,1,1,1,2},{0,1,1,1,1,0,2,0},{0,0,1,0,1,1,2,1} }, Rotation4[7][10] = { {0,0,1,0,2,0,3,0},{0,0,1,0,0,1,1,1},{0,1,1,0,1,1,1,2},{0,0,1,0,2,0,0,1},{0,0,0,1,1,1,2,1},{0,0,0,1,1,1,1,2},{0,1,0,2,1,0,1,1} };
	switch (UsesFigure[1]) {
	case 1: {
		if (strcmp(ModRotation, "NEXT") == 0) {
			UsesFigure[1] = 2;
			AddFigureRotate(Rotation2[UsesFigure[2]], UsesFigure);
		}
		if (strcmp(ModRotation, "PREV") == 0) {
			UsesFigure[1] = 4;
			AddFigureRotate(Rotation4[UsesFigure[2]], UsesFigure);
		}
		break;
	}
	case 2: {
		if (strcmp(ModRotation, "NEXT") == 0) {
			UsesFigure[1] = 3;
			AddFigureRotate(Rotation3[UsesFigure[2]], UsesFigure);
		}
		if (strcmp(ModRotation, "PREV") == 0) {
			UsesFigure[1] = 1;
			AddFigureRotate(Rotation1[UsesFigure[2]], UsesFigure);
		}
		break;
	}
	case 3: {
		if (strcmp(ModRotation, "NEXT") == 0) {
			UsesFigure[1] = 4;
			AddFigureRotate(Rotation4[UsesFigure[2]], UsesFigure);
		}
		if (strcmp(ModRotation, "PREV") == 0) {
			UsesFigure[1] = 2;
			AddFigureRotate(Rotation2[UsesFigure[2]], UsesFigure);
		}
		break;
	}
	case 4: {
		if (strcmp(ModRotation, "NEXT") == 0) {
			UsesFigure[1] = 1;
			AddFigureRotate(Rotation1[UsesFigure[2]], UsesFigure);
		}
		if (strcmp(ModRotation, "PREV") == 0) {
			UsesFigure[1] = 3;
			AddFigureRotate(Rotation3[UsesFigure[2]], UsesFigure);
		}
		break;
	}
	}
}
int ControlKey(int wParam, HWND hwnd, int ModKey) {
	if (wParam == 32 && strcmp(ModLoad, "PROCESSGAME") == 0 && ModKey == 1) {
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
	if (FlagPause == 1 && strcmp(ModLoad, "PROCESSGAME") == 0) return 0;
	if (wParam == 16 && strcmp(ModLoad, "LOGIN") == 0) if (FlagShift == 0) FlagShift = 65; else FlagShift = 0;
	if (ModKey == 0) return 0;
	if (AdressUsesEdite != NULL && wParam != 16 && strcmp(ModLoad, "LOGIN") == 0) {
		if (wParam == 8) {
			if (strlen(AdressUsesEdite->Text) <= 0) return 0;
			char Byffer[100] = { 0 };
			strncpy_s(Byffer, AdressUsesEdite->Text, strlen(AdressUsesEdite->Text) - 1);
			strcpy_s(AdressUsesEdite->Text, Byffer);
		}
		else {
			if (wParam >= 48 && wParam <= 59) {
				AdressUsesEdite->Text[strlen(AdressUsesEdite->Text)] = (char)wParam;
				UpdateWindowRect(hwnd);
				return 0;
			}
			char Byffer;
			if (wParam == 32) strcat_s(AdressUsesEdite->Text, " ");
			wParam = wParam - FlagShift;
			if (FlagShift != 0) {
				char WordAlphavit[100] = { "abcdefghijklmnopqrstuvwxyz" };
				Byffer = WordAlphavit[wParam];
			}
			else Byffer = (char)wParam;
			AdressUsesEdite->Text[strlen(AdressUsesEdite->Text)] = Byffer;
		}
		UpdateWindowRect(hwnd);
		return 0;
	}
	if (wParam == 65) {
		RemoveFigure(hwnd, "LEFT");
		if (ClashOfFigure(hwnd) == 3 || ClashOfFigure(hwnd) == 1)	RemoveFigure(hwnd, "RIGHT");
	}
	if (wParam == 68) {
		RemoveFigure(hwnd, "RIGHT");
		if (ClashOfFigure(hwnd) == 3 || ClashOfFigure(hwnd) == 1)	RemoveFigure(hwnd, "LEFT");
	}
	if (wParam == 83) {
		KillTimer(hwnd, 1);
		RemoveFigure(hwnd, "DOWN");
		if (ClashOfFigure(hwnd) == 3 || ClashOfFigure(hwnd) == 2) {
			if (ClashOfFigure(hwnd) == 3) RemoveFigure(hwnd, "UP");
			UsesFigure[0]++;
			UsesFigure[1] = NextFigure[1];
			UsesFigure[2] = NextFigure[2];
			AssignNextFigure(UsesFigure[0], NextFigure[0], hwnd);
			char Buffer[30] = { "NEXT" };
			CreateFigure(Buffer, NextFigure, hwnd);
		}
		CheckCombustion(hwnd);
		SetTimer(hwnd, 1, CoefficientOfSpeed, NULL);
	}
	if (wParam == 87) {
		ChangeRotation(hwnd, "NEXT");
		int RotateNumber = ClashOfFigure(hwnd);
		if (RotateNumber == 1 || RotateNumber == 3) {
			ChangeRotation(hwnd, "PREV");
			if (UsesFigure[2] == 4 && (UsesFigure[1] == 1 || UsesFigure[1] == 3)) {
				if (UsesFigure[1] == 3) RemoveFigure(hwnd, "UP");
				if (UsesFigure[1] == 1) RemoveFigure(hwnd, "DOWN");
			}
			if (UsesFigure[2] == 2 && (UsesFigure[1] == 2 || UsesFigure[1] == 4)) {
				if (UsesFigure[1] == 4) RemoveFigure(hwnd, "UP");
				if (UsesFigure[1] == 2) RemoveFigure(hwnd, "DOWN");
			}
		}
		if (RotateNumber == 2) {
			UsesFigure[0]++;
			UsesFigure[1] = NextFigure[1];
			UsesFigure[2] = NextFigure[2];
			AssignNextFigure(UsesFigure[0], NextFigure[0], hwnd);
			char Buffer[30] = { "NEXT" };
			CreateFigure(Buffer, NextFigure, hwnd);
		}
		CheckCombustion(hwnd);
	}
	UpdateWindowRect(hwnd);
}
