#pragma once

enum COLOR {
	GREEN = 0xA,
	GREEN_BACKGROUND = 0xBA,
	RED_BACKGROUND = 0xBC,
	TURQUOISE = 0xB,
	TURQUOISE_BACKGROUND = 0xB0,
	RED = 0xC,
	GREY = 0x7,
	BLUE = 0x1,
	ORANGE = 0x6,
	YELLOW = 0xE,
	PURPLE = 0x5,
	PINK = 0xD,
	GREY_BACKGROUND = 0x07,
	GREY_BACKGROUND_GREEN_LAT = 0x0A,
	GREY_BACKGROUND_RED_LAT = 0x0C
};

void Init();                        // инициализация проекта
void SetColor(COLOR text);          // переключение цвета


int ** CreateMatrix(int m, int n, int from, int to); // создания матрицы
int Random(int From, int To);                        // генерация псевдо случайных чисел
void DestroyMatrix(int **arr, int m);                // удаление матрицы
