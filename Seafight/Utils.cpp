#include "stdafx.h"
#include "Utils.h"
HANDLE h;

void Init()
{
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(GetTickCount());
	SetConsoleOutputCP(RUS_LOCALE);
	cout << setprecision(3);
	SetColor(GREY);

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(h, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(h, &structCursorInfo);
	ShowCursor(FALSE);

	CONSOLE_FONT_INFOEX cfi;

	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 26;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL/*FW_BOLD*/;

	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(h, TRUE, &cfi);


	SetConsoleTitle(L"Морской бой");


	
	COORD crd = { 1980, 1024 };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(h, true, &src);
	SetConsoleScreenBufferSize(h, crd);

    HWND window_header = GetConsoleWindow();
	SetWindowPos(window_header, HWND_TOP, -4, -4, 1980, 1025, NULL);
}//Init

void SetColor(COLOR text)
{
	SetConsoleTextAttribute(h, text);
} // SetColor

int ** CreateMatrix(int m, int n, int from, int to)
{
	// массив указателей на строки матрицы
	int **ptrTemp = new int*[m];

	// создание одномерных массивов, содержащих данные в матрице
	for (int i = 0; i < m; i++) {
		ptrTemp[i] = new int[n];
		for (int j = 0; j < n; j++) {
			ptrTemp[i][j] = Random(from, to);
		} // for i
	} // for i
	return ptrTemp;
} // CreateMatrix

int Random(int From, int To)
{
	return From + rand() % (To - From + 1);
} // Random

void DestroyMatrix(int **arr, int m)
{
	for (int i = 0; i < m; i++)
		delete arr[i];

	delete[] arr;
} // DestroyMatrix





