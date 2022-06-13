#include "stdafx.h"
#include "Utils.h"
#include "EnemyAI.h"

void ShowEnemyBattlefield(int **MainEnemyBattlefield, int x, int y, int **MainUserBattlefield, int x_t, int y_t, bool playerChek, int enemyScore) // Отображение поля боя врага
{
	system("cls");
	cout << "\n\n";
	char symbol = 65;                             // Цифровое обозначение столбцов
	int number = 0;                               // Нумерация строк
	cout << "\t\b\b\b\b";
	for (int i = 0; i < 10; i++)                  // вывод символьной нумерации
	{
		cout << "   " << symbol;
		symbol++;
	}
	symbol = 65;
	cout << "\t\t\t\t\t\t\t\b\b\b\b\b";
	for (int i = 0; i < 10; i++)                   // вывод символьной нумерации
	{
		cout << "   " << symbol;
		symbol++;
	}
	cout << "\n\t\b\b\b";
	cout << "|---|---|---|---|---|---|---|---|---|---|";
	cout << "\t\t\t\t\t\t\t\b\b\b\b";
	cout << "|---|---|---|---|---|---|---|---|---|---|\n";
	for (int i = 0; i < y; i++)
	{
		cout << setw(2) << ++number;                // Нумерация строк
		cout << "\t\b\b\b";
		for (int j = 0; j < x; j++)
		{
			cout << "|";
			if(!playerChek)
			{
				if (i == y_t && j == x_t) SetColor(TURQUOISE_BACKGROUND);      // Если стреляет враг, отобрази куда
				else SetColor(GREY_BACKGROUND);
			}// if
			switch (MainUserBattlefield[i][j])
			{
			case 0: case 2:                        // Клетка пустого моря
				cout << "   ";
				break;
			case 1:                                // Пустое море в которое был произведён выстрел
				cout << " * ";
				break;
			case 31: case 32: case 33: case 34:    // Уничтоженный сегмент корабля
				SetColor(RED);
				if(!playerChek)
				{
					if (i == y_t && j == x_t) SetColor(RED_BACKGROUND);
					else SetColor(GREY_BACKGROUND_RED_LAT);
				}// if
				cout << "[X]";
				SetColor(GREY);
				break;
			case 41: case 42: case 43: case 44:    // Сегмент корабля
				SetColor(GREEN);
				if(!playerChek)
				{
					if (i == y_t && j == x_t) SetColor(GREEN_BACKGROUND);
					else SetColor(GREY_BACKGROUND_GREEN_LAT);
				}// if
				cout << "[ ]";
				SetColor(GREY);
				break;
			}// switch
			SetColor(GREY);
		}// for j
		cout << "|";
		
		cout << "\t\t\t\t\t\t\t\b\b\b\b\b\b\b";
		cout << setw(2) << number;
		cout << " ";
		for (int j = 0; j < x; j++)
		{

			cout << "|";
			if(playerChek)
			{
				if (i == y_t && j == x_t) SetColor(TURQUOISE_BACKGROUND); // Если стреляет игрок, отобрази куда
				else SetColor(GREY_BACKGROUND);
			}// if
			switch (MainEnemyBattlefield[i][j])
			{
			case 0: case 2:                        // Клетка пустого моря
				cout << "   ";
				break;
			case 1:                                // Пустое море в которое был произведён выстрел
				cout << " * ";
				break;
			case 31: case 32: case 33: case 34:    // Уничтоженный сегмент корабля
				SetColor(RED);
				if(playerChek)
				{
					if (i == y_t && j == x_t) SetColor(RED_BACKGROUND);
					else SetColor(GREY_BACKGROUND_RED_LAT);
				}// if
				cout << "[X]";
				SetColor(GREY);
				break;
			case 41: case 42: case 43: case 44:    // Сегмент корабля
				
				if (enemyScore < 10 /*false*/)     // Раскомментировать false чтобы видеть вражеские корабли
				{
					cout << "   ";
				}
				else
				{
					SetColor(GREEN);
					if (!playerChek)
					{
						if (i == y_t && j == x_t) SetColor(GREEN_BACKGROUND);
						else SetColor(GREY_BACKGROUND_GREEN_LAT);
					}// if
					cout << "[ ]";
					SetColor(GREY);
				}
				break;
			}// switch
			SetColor(GREY);
		}// for
		cout << "|";
		cout << "\n\t\b\b\b";
		cout << "|---|---|---|---|---|---|---|---|---|---|";
		cout << "\t\t\t\t\t\t\t\b\b\b\b";
		cout << "|---|---|---|---|---|---|---|---|---|---|\n";
	}
}// UserBattlefield

void RandomShipArrangement(int **Battlefield, int x, int y)           // Случайное расположение кораблей
{
	register int x_t, y_t, nDeck = 4;                                 // координаты и количество палуб
	int test = 0;                                                     // количество расставленных палуб
	bool ItRotated;                                                   // ориентация корабля, горизонтальная (false), вертикальная (true)

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)                                   // Очистка поля, если вдруг там есть корабли
		{
			if (Battlefield[i][j] != 0) Battlefield[i][j] = 0;
		}// for j
	}// for i

	while (true)
	{
		ItRotated = Random(0, 1);                                      // генерация ориентации корабля
		x_t = Random(0, x - 1);                                        // генерация координат
		y_t = Random(0, y - 1);                                        // генерация координат
		int k;
		bool flag = true;                                              // флаг для проверки годности координат

		if (!ItRotated)                                                        // Если корабль расположен горизонтально
		{
			for (k = 0; k < nDeck; k++)
			{
				if(x_t + nDeck > x - 1)                                // проверка: не выходит ли корабль за пределы поля
				{
					flag = false;
					break;
				}
				
				if (Battlefield[y_t][x_t + k] != 0)                    // проверка: не накладывается ли корабль на другой корабль
				{
					flag = false;
					break;
				}
			}// for
			if (!flag) continue;                                       // если координаты не подходят то генерируй заново
			                                             
			if (x_t - 1 >= 0)                                          // создание "поля" за кораблём
			{
				if (y_t - 1 >= 0) Battlefield[y_t - 1][x_t - 1] = 2;
				if (y_t + 1 <= y - 1) Battlefield[y_t + 1][x_t - 1] = 2;
				Battlefield[y_t][x_t - 1] = 2;
			}
			for (int i = 0; i < nDeck; i++)                            // создание палуб и "поля" по сторонам палуб
			{
				Battlefield[y_t][x_t + i] = 40 + nDeck;
				if (y_t + 1 <= y - 1)Battlefield[y_t + 1][x_t + i] = 2;
				if (y_t - 1 >= 0)Battlefield[y_t - 1][x_t + i] = 2;
			}// for i
			if (x_t + nDeck <= x - 1)                                   // создание "поля" перед кораблём
			{
				if (y_t - 1 >= 0)Battlefield[y_t - 1][x_t + nDeck] = 2;
				if (y_t + 1 <= y - 1)Battlefield[y_t + 1][x_t + nDeck] = 2;
				Battlefield[y_t][x_t + nDeck] = 2;
			}
			if (test == 0 || test == 2 || test == 5 || test == 9)nDeck--; // если созданы все 4\3\2\1 - палубники уменьш количество палуб
			x_t = 0;                                                      // обнуление координат
			y_t = 0;                                                      // обнуление координат
			test++;

		}// if
		if (ItRotated)                                                          // Если корабль расположен вертикально
		{
			for (k = 0; k < nDeck; k++)
			{
				if(y_t + nDeck > y - 1)                                  // проверка: не выходит ли корабль за пределы поля
				{
					flag = false;
					break;
				}
				if (Battlefield[y_t + k][x_t] != 0)                      // проверка: не накладывается ли корабль на другой корабль
				{
					flag = false;
					break;
				}// if
			}// for
			if (!flag) continue;                                          // если координаты не подходят то генерируй заново
			 
			if (y_t - 1 >= 0)                                             // создание "поля" за кораблём
			{
				if (x_t - 1 >= 0)Battlefield[y_t - 1][x_t - 1] = 2;
				if (x_t + 1 <= x - 1)Battlefield[y_t - 1][x_t + 1] = 2;
				Battlefield[y_t - 1][x_t] = 2;
			}// if 
			for (int i = 0; i < nDeck; i++)                               // создание палуб и "поля" по сторонам палуб
			{
				Battlefield[y_t + i][x_t] = 40 + nDeck;
				if (x_t + 1 <= x - 1)Battlefield[y_t + i][x_t + 1] = 2;
				if (x_t - 1 >= 0)Battlefield[y_t + i][x_t - 1] = 2;
			}// for i
			if (y_t + nDeck <= y - 1)                                     // создание "поля" перед кораблём
			{
				if (x_t - 1 >= 0)Battlefield[y_t + nDeck][x_t - 1] = 2;
				if (x_t + 1 <= x - 1)Battlefield[y_t + nDeck][x_t + 1] = 2;
				Battlefield[y_t + nDeck][x_t] = 2;
			}// if
			if (test == 0 || test == 2 || test == 5 || test == 9)nDeck--; // если созданы все 4\3\2\1 - палубники уменьш количество палуб
			x_t = 0;                                                      // обнуление координат
			y_t = 0;                                                      // обнуление координат
			test++;                            
			ItRotated = false;                               
		}// if
		if (test == 10) return;                                           // Если все корабли расположены то выйди из функции
	}//while
}// RandomShipArrangement 
