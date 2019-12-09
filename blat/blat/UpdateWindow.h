#pragma once
HDC DrawingPicOrDraw(int ModDraw, struct HEAD *StructFollow, HDC MemDC, HWND hwnd, HBITMAP MemBMP) {
	HPEN hPen;
	RECT rect;
	GetWindowRect(hwnd, &rect);
	rect.bottom = StructFollow->y1;
	rect.right = StructFollow->x1 - StructFollow->x0 + StructFollow->x0;
	rect.top = (StructFollow->y1 - StructFollow->y0) / 2 - 8 + StructFollow->y0;
	rect.left = (StructFollow->x1 - StructFollow->x0) / 2 - strlen(StructFollow->Text) * 4 + StructFollow->x0;
	HFONT Font = CreateFontA(StructFollow->TextHeight, StructFollow->Width, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");
	SelectObject(MemDC, Font);
	if (ModDraw == 4) {
		SetTextColor(MemDC, StructFollow->LineColor);
		SetBkMode(MemDC, TRANSPARENT);
		DrawTextA(MemDC, StructFollow->Text, -1, &rect, DT_SINGLELINE);
	}
	if (ModDraw == 0) {
		HBRUSH hbrush;
		hbrush = CreateSolidBrush(StructFollow->BackGroundColor);
		SetBkColor(MemDC, StructFollow->BackGroundColor);
		SelectObject(MemDC, hbrush);
		hPen = CreatePen(0, 2, StructFollow->LineColor);
		SelectObject(MemDC, hPen);
		if (StructFollow->BackGroundColor != 16777216) {
			if (strcmp(StructFollow->LoadMOD, "RECTANGLE") == 0) Rectangle(MemDC, StructFollow->x0, StructFollow->y0, StructFollow->x1, StructFollow->y1);
			if (strcmp(StructFollow->LoadMOD, "ROUNDRECT") == 0) RoundRect(MemDC, StructFollow->x0, StructFollow->y0, StructFollow->x1, StructFollow->y1, 40, 40);
			if (strcmp(StructFollow->LoadMOD, "ELLIPSE") == 0) Ellipse(MemDC, StructFollow->x0, StructFollow->y0, StructFollow->x1, StructFollow->y1);
			DrawTextA(MemDC, StructFollow->Text, -1, &rect, DT_SINGLELINE);
		}
		DeleteObject(hPen);
		DeleteObject(hbrush);
	}
	if (ModDraw == 1) {
		HDC MemPicHDC, hDcEndImage;
		BITMAP bitmap;
		HBITMAP hbm;
		HANDLE hAndle = LoadImageA(NULL, StructFollow->LoadMOD, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		MemPicHDC = CreateCompatibleDC(MemDC);
		SelectObject(MemPicHDC, hAndle);
		GetObject(hAndle, sizeof(BITMAP), &bitmap);
		hDcEndImage = CreateCompatibleDC(MemDC);
		hbm = CreateCompatibleBitmap(MemDC, StructFollow->x1 - StructFollow->x0, StructFollow->y1 - StructFollow->y0);
		SelectObject(hDcEndImage, hbm);
		SetStretchBltMode(hDcEndImage, STRETCH_HALFTONE);
		StretchBlt(hDcEndImage, 0, 0, StructFollow->x1 - StructFollow->x0, StructFollow->y1 - StructFollow->y0, MemPicHDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		BitBlt(MemDC, StructFollow->x0, StructFollow->y0, StructFollow->x1, StructFollow->y1, hDcEndImage, 0, 0, SRCCOPY);
		DrawTextA(MemDC, StructFollow->Text, -1, &rect, DT_SINGLELINE);
		DeleteObject(MemPicHDC);
		DeleteObject(hDcEndImage);
		DeleteObject(hAndle);
		DeleteObject(hbm);
	}
	if (ModDraw == 3) {
		if (strcmp(StructFollow->ModLoad, "EDITE") == 0) {
			SetTextColor(MemDC, StructFollow->LineColor);
			SetBkMode(MemDC, TRANSPARENT);
			DrawTextA(MemDC, StructFollow->Text, -1, &rect, DT_SINGLELINE);
		}
		else {
			HDC MemPicHDC, hDcEndImage;
			BITMAP bitmap;
			HBITMAP hbm;
			HANDLE hAndle = LoadImageA(NULL, StructFollow->LoadMOD, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			MemPicHDC = CreateCompatibleDC(MemDC);
			SelectObject(MemPicHDC, hAndle);
			GetObject(hAndle, sizeof(BITMAP), &bitmap);
			hDcEndImage = CreateCompatibleDC(MemDC);
			int x = fabs(StructFollow->x1 - StructFollow->x0), y = fabs(StructFollow->y1 - StructFollow->y0);
			hbm = CreateCompatibleBitmap(MemDC, x, y);
			SelectObject(hDcEndImage, hbm);
			SetStretchBltMode(hDcEndImage, STRETCH_HALFTONE);
			StretchBlt(hDcEndImage, 0, 0, x, y, MemPicHDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			RGBQUAD *buffer = new RGBQUAD[y*x];
			ZeroMemory(&bif, sizeof(BITMAPINFO));
			bif.bmiHeader.biSize = sizeof(bif);
			bif.bmiHeader.biHeight = -SRC_RESOLUTION_Y;
			bif.bmiHeader.biWidth = SRC_RESOLUTION_X;
			bif.bmiHeader.biPlanes = 1;
			bif.bmiHeader.biBitCount = sizeof(RGBQUAD) * 8;
			ZeroMemory(&bifs, sizeof(BITMAPINFO));
			bifs.biSize = sizeof(bifs);
			bifs.biHeight = -y;
			bifs.biWidth = x;
			bifs.biPlanes = 1;
			bifs.biBitCount = sizeof(RGBQUAD) * 8;
			bifs.biCompression = BI_RGB;
			GetDIBits(hDcEndImage, hbm, 0, y, buffer, (LPBITMAPINFO)&bifs, DIB_RGB_COLORS);
			GetDIBits(MemDC, MemBMP, 0, SRC_RESOLUTION_Y, im, (LPBITMAPINFO)&bif, DIB_RGB_COLORS);
			if (StructFollow->BackGroundColor != 0 && StructFollow->LineColor != 0) {
				for (int y_c = 0; y_c < y; y_c++) {
					for (int x_c = 0; x_c < x; x_c++) {
						if (buffer[y_c*x + x_c].rgbBlue > 4 && buffer[y_c*x + x_c].rgbGreen > 4 && buffer[y_c*x + x_c].rgbRed > 4)
							im[(y_c + StructFollow->y0)*SRC_RESOLUTION_X + (x_c + StructFollow->x0)] = buffer[y_c*x + x_c];
					}
				}
			}
			SetDIBitsToDevice(MemDC, 0, 0, SRC_RESOLUTION_X, SRC_RESOLUTION_Y, 0, 0, 0, SRC_RESOLUTION_Y, im, &bif, DIB_RGB_COLORS);
			DeleteObject(MemPicHDC);
			DeleteObject(hDcEndImage);
			DeleteObject(hAndle);
			DeleteObject(hbm);
			delete[] buffer;
		}
	}
	DeleteObject(Font);
	return MemDC;
}
void UpdateWindowRect(HWND hwnd) {
	InvalidateRect(hwnd, NULL, FALSE);
	HDC MainHDC, MemDC;
	RECT rect;
	HBITMAP MemBMP;
	PAINTSTRUCT paintStr;
	GetWindowRect(hwnd, &rect);
	MainHDC = BeginPaint(hwnd, &paintStr);
	MemDC = CreateCompatibleDC(MainHDC);
	MemBMP = CreateCompatibleBitmap(MainHDC, rect.right, rect.bottom);
	SelectObject(MemDC, MemBMP);
	struct HEAD *StructFollow = ElementDatas;
	for (;;) {
		if (StructFollow == NULL) break;
		if (strcmp(StructFollow->ModLoad, "PICTERES") == 0) MemDC = DrawingPicOrDraw(1, StructFollow, MemDC, hwnd, MemBMP);
		if (strcmp(StructFollow->ModLoad, "DRAWING") == 0) MemDC = DrawingPicOrDraw(0, StructFollow, MemDC, hwnd, MemBMP);
		if (strcmp(StructFollow->ModLoad, "PICTERES_BACKGROUND_OFF") == 0 || strcmp(StructFollow->ModLoad, "EDITE") == 0) MemDC = DrawingPicOrDraw(3, StructFollow, MemDC, hwnd, MemBMP);
		if (strcmp(StructFollow->ModLoad, "TEXT_BACKGROUND_OFF") == 0 ) MemDC = DrawingPicOrDraw(4, StructFollow, MemDC, hwnd, MemBMP);
		StructFollow = StructFollow->next;
	}
	char FPS_str[100] = { 0 };
	if (strcmp(ModLoad, "PROCESSGAME") == 0) {
		sprintf_s(FPS_str, "%d", FRAP_DOUBLE_BUFFER);
		DrawTextA(MemDC, FPS_str, -1, &rect, DT_SINGLELINE);
	}
	BitBlt(MainHDC, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);
	DeleteObject(MainHDC);
	DeleteObject(MemDC);
	DeleteObject(MemBMP);
	EndPaint(hwnd, &paintStr);
}
