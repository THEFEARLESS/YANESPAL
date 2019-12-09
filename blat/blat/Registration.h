#pragma once
struct HEAD {
	int x0, y0, x1, y1, BackGroundColor, LineColor, IDCell, TextHeight, Width;
	char ModLoad[100], Text[100], LoadMOD[100];
	struct HEAD *next, *prev, *EndElement;
};
struct HEAD *ElementDatas = NULL;
struct HEAD *RegistrationObject(int x0, int y0, int x1, int y1, int BackGroundColor, int LineColor,const char ModLoad[100], const char Text[100], const char LoadMOD[100], int IDCell, int TextHeight, int Width) {
	if (ElementDatas == NULL) {
		ElementDatas = (struct HEAD*)malloc(sizeof(struct HEAD));
		strcpy_s(ElementDatas->ModLoad, ModLoad);
		strcpy_s(ElementDatas->Text, Text);
		strcpy_s(ElementDatas->LoadMOD, LoadMOD);
		ElementDatas->x0 = x0;
		ElementDatas->x1 = x1;
		ElementDatas->y0 = y0;
		ElementDatas->y1 = y1;
		ElementDatas->TextHeight = TextHeight;
		ElementDatas->Width = Width;
		ElementDatas->IDCell = IDCell;
		ElementDatas->BackGroundColor = BackGroundColor;
		ElementDatas->LineColor = LineColor;
		ElementDatas->next = NULL;
		ElementDatas->prev = NULL;
		ElementDatas->EndElement = ElementDatas;
		return ElementDatas;
	}
	struct HEAD *StructFollow = ElementDatas, *FreeAdress;
	for (;;) {
		if (StructFollow->next == NULL) {
			FreeAdress = (struct HEAD*)malloc(sizeof(struct HEAD));
			strcpy_s(FreeAdress->ModLoad, ModLoad);
			strcpy_s(FreeAdress->Text, Text);
			strcpy_s(FreeAdress->LoadMOD, LoadMOD);
			FreeAdress->x0 = x0;
			FreeAdress->x1 = x1;
			FreeAdress->y0 = y0;
			FreeAdress->y1 = y1;
			FreeAdress->TextHeight = TextHeight;
			FreeAdress->Width = Width;
			FreeAdress->IDCell = IDCell;
			FreeAdress->BackGroundColor = BackGroundColor;
			FreeAdress->LineColor = LineColor;
			StructFollow->next = FreeAdress;
			FreeAdress->next = NULL;
			FreeAdress->prev = StructFollow;
			ElementDatas->EndElement = FreeAdress;
			return FreeAdress;
		}
		StructFollow = StructFollow->next;
	}
}
