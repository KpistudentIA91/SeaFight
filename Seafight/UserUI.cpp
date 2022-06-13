#include "stdafx.h"
#include "Utils.h"
#include "UserUI.h"
#include "EnemyAI.h"


void ShowUserBattlefield(int **MainUserBattlefield, int x, int y, int **TempUserBattlefield, register int x_t, register int y_t, int nDeck, bool ItRotated) // Отображение поля боя игрока
{
	system("cls");
	cout << "\n \t\t\b\b\bРасположите свои корабли";
	cout << "\n";
	char symbol = 65;                             // Цифровое обозначение столбцов
	int number = 1;                               // Нумерация строк
	cout << "\t\b\b\b\b";
	for (int i = 0; i < 10; i++)                  // вывод символьной нумерации
	{
		cout << "   " << symbol;
		symbol++;
	}
	cout << "\n\t\b\b\b";
	cout << "|---|---|---|---|---|---|---|---|---|---|\n";
	for (int i = 0; i < y; i++)                   // Нумерация строк
	{
		cout << setw(2) <<  number++;
		cout << "\t\b\b\b";
		for (int j = 0; j < x; j++)
		{
			
			cout << "|";
			//if (i == y_t && j == x_t) SetColor(TURQUOISE_BACKGROUND);
			//else SetColor(GREY_BACKGROUND);
			if (i == y_t && j >= x_t && j <= x_t + nDeck - 1 && !ItRotated || j == x_t && i >= y_t && i <= y_t + nDeck - 1 && ItRotated)
			{
				switch (TempUserBattlefield[i][j])
				{
				case 0: case 2:                        // Клетка пустого моря
					cout << "   ";
					break;
				case 1:                                // Пустое море в которое был произведён выстрел
					cout << " X ";
					break;
				case 31: case 32: case 33: case 34:    // Уничтоженный сегмент корабля
					cout << "[X]";
					break;
				case 41: case 42: case 43: case 44:    // Сегмент корабля
					cout << "[ ]";
					break;
				}// switch
				continue;
			}// if
			 
			switch(MainUserBattlefield[i][j])
			{
			case 0: case 2:                        // Клетка пустого моря
				cout << "   ";                    
				break;
			case 1:                                // Пустое море в которое был произведён выстрел
				cout << " X ";
				break;
			case 31: case 32: case 33: case 34:    // Уничтоженный сегмент корабля
				cout << "[X]";
				break;
			case 41: case 42: case 43: case 44:    // Сегмент корабля
				SetColor(GREEN);
				cout << "[ ]";
				SetColor(GREY);
				break;
			}// switch
			
		}// for
		cout << "|";
		if (i == 3) cout << " \"X\" - для случайной генерации";
		if (i == 5) cout << " \"R\" - для поворота корабля";
		
		cout << "\n\t\b\b\b";
		cout << "|---|---|---|---|---|---|---|---|---|---|\n";
	}
}// UserBattlefield

void CreateShip(int **TempUserBattlfield, int y_t, int x_t, int nDeck) // создание корабля
{
	for (int k = 0; k < 4; k++)
	{
		TempUserBattlfield[y_t][x_t + k] = 40 + nDeck;    // 40 + количество палуб = id палубы нПалубника         
	}// for k
}// CreateShip

void ShipArrangement(int **TempUserBattlfield, int x, int y, int **MainUserBattlefield, int &ch)  // расстановка кораблей
{
	register int x_t = 0, y_t = 0, nDeck = 4;              // стартовые координаты
	int test = 0;                                          // количество установленых кораблей
	bool ItRotated = false;                                // ориентация корабля, горизонтальная (false), вертикальная (true)
	CreateShip(TempUserBattlfield, y_t, x_t, nDeck);       // Создание корабля
	ShowUserBattlefield(MainUserBattlefield, x, y, TempUserBattlfield, x_t, y_t, nDeck, ItRotated); // вывод поля
	while (true)
	{

		ch = _getch();                                       // считывание клавиши
		if (ch == 224) continue;
		
		switch (ch)
		{
		case 77:                                              // Движение корабля вправо
			if (x_t + nDeck - 1 == x - 1 && !ItRotated) break;
			if (x_t == x - 1 && ItRotated) break;
			if(ItRotated) 
			{
				for (int i = 0; i < nDeck; i++)
				{
					TempUserBattlfield[y_t + i][x_t] = 0;
				}// for i
				x_t++;                                              // []
				for (int i = 0; i < nDeck; i++)                     // [] -->
				{                                                   // []
					TempUserBattlfield[y_t + i][x_t] = 40 + nDeck;  // []
				}// for i
				break;
			}// if
			x_t++;
			TempUserBattlfield[y_t][x_t - 1] = 0;
			TempUserBattlfield[y_t][x_t + nDeck - 1] = 40 + nDeck;// [][][][] -->
			break;
		case 75:                                              // Движение корабля влево
			if (x_t == 0) break;
			if (ItRotated)
			{
				for (int i = 0; i < nDeck; i++)
				{
					TempUserBattlfield[y_t + i][x_t] = 0;
				}// for i
				x_t--;                                              //    []
				for (int i = 0; i < nDeck; i++)                     //<-- [] 
				{                                                   //    []
					TempUserBattlfield[y_t + i][x_t] = 40 + nDeck;  //    []
				}// for i
				break;
			}// if
			TempUserBattlfield[y_t][x_t + nDeck - 1] = 0;
			TempUserBattlfield[y_t][x_t - 1] = 40 + nDeck;        // [][][][] <--
			x_t--;
			break;
		case 80:                                              // Движение корабля вниз
			if (y_t == y - 1 && !ItRotated) break;
			if (y_t + nDeck - 1 == y - 1 && ItRotated) break;
			if(ItRotated)                                             // []
			{                                                         // []
				y_t++;                                                // []  
				TempUserBattlfield[y_t - 1][x_t] = 0;                 // []
				TempUserBattlfield[y_t + nDeck - 1][x_t] = 40 + nDeck;// |
				break;                                                // V
			}
			for (int i = 0; i < nDeck; i++)
			{
				TempUserBattlfield[y_t][x_t + i] = 0;
			}// for i
			y_t++;                                          
			for (int i = 0; i < nDeck; i++)                      // [][][][]
			{                                                    //    |
				TempUserBattlfield[y_t][x_t + i] = 40 + nDeck;   //    V
			}// for i
			break;
		case 72:                                           // Движение корабля ввверх
			if (y_t == 0) break;
			if (ItRotated)                                        
			{                                                     // ^
				                                                  // | 
				TempUserBattlfield[y_t + nDeck - 1][x_t] = 0;     // []
				TempUserBattlfield[y_t - 1][x_t] = 40 + nDeck;    // []
				y_t--;                                            // []
				break;                                            // []
			}
			for (int i = 0; i < nDeck; i++)
			{
				TempUserBattlfield[y_t][x_t + i] = 0;          //    ^
			}// for i                                          //    |
			y_t--;                                             // [][][][]
			for (int i = 0; i < nDeck; i++)
			{
				TempUserBattlfield[y_t][x_t + i] = 40 + nDeck;
			}// for i
			break;
		case 114:                                              // Поворот корабля    
			if (y_t - nDeck < 0 && !ItRotated)                 // Из горизонтального в вертикальное
			{
				for (int i = 0; i < nDeck; i++)                // Если корабль прижат к верхней границе
				{                                              
					TempUserBattlfield[y_t][x_t + i] = 0;          
				}                                                      // [][][][]
				for (int i = 0; i < nDeck; i++)                        // []<- | |
				{                                                      // []<--- |
					TempUserBattlfield[y_t + i][x_t] = 40 + nDeck;	   // []<-----
				}                                              
				ItRotated = true;
				break;
			}
			else if(!ItRotated)
			{
				for (int i = 0; i < nDeck; i++)                    // Если корабль прижат к нижней границе
				{                                                  // []<-----
					TempUserBattlfield[y_t][x_t + i] = 0;          // []<--- |
				}                                                  // []<- | |  
				for (int i = 0; i < nDeck; i++)                    // [][][][]
				{
					TempUserBattlfield[y_t - i][x_t] = 40 + nDeck;
				}
				y_t -= nDeck - 1;
				ItRotated = true;
				break;
			}// if

			if (x_t + nDeck > x - 1 && ItRotated)              // Из Вертикального в горизонтальное
			{
				for (int i = 0; i < nDeck; i++)                // Если корабль прижат к правой границе
				{
					TempUserBattlfield[y_t + i][x_t] = 0;
				}                                                  // [][][][]
				for (int i = 0; i < nDeck; i++)                    // ^ ^ ^-[]
				{                                                  // | |---[]
					TempUserBattlfield[y_t][x_t - i] = 40 + nDeck; // ------[]
				}
				x_t -= nDeck - 1;
				ItRotated = false;
				break;
			}
			else if (ItRotated)
			{
				for (int i = 0; i < nDeck; i++)
				{                                                  // [][][][]
					TempUserBattlfield[y_t + i][x_t] = 0;          // []-^ ^ ^
				}                                                  // []---| | 
				for (int i = 0; i < nDeck; i++)                    // []-----|
				{
					TempUserBattlfield[y_t][x_t + i] = 40 + nDeck;
				}                                             
				ItRotated = false;
				break;
			}// if
		case 120:                                                // Случайная генерация
			 RandomShipArrangement(MainUserBattlefield, x, y);
			 return;
		case 27:                                                 // при нажатии esc уходим
			return;
		case 13:                                                 // При нажатии enter происходит запись в основную матрицу, и создание "поля" вокруг корабля
			int k;
			bool flag = true;                                    // проверка годности координат
			if(!ItRotated)                                                        // Если корабль расположен горизонтально
			{
				for (k = 0; k < nDeck; k++)
				{
					if (MainUserBattlefield[y_t][x_t + k] != 0)  // Не годны! Следующий!
					{
						cout << "\n\n\tВы не можете поставить тут корабль";
						Sleep(500);
						flag = false;
						break;
					}
				}// for
				if (!flag) break;                                
				if (x_t - 1 >= 0)                                                    // создание "поля" за кораблём
				{
					if (y_t - 1 >= 0) MainUserBattlefield[y_t - 1][x_t - 1] = 2;
					if (y_t + 1 <= y - 1) MainUserBattlefield[y_t + 1][x_t - 1] = 2;
					MainUserBattlefield[y_t][x_t - 1] = 2;
				}
				for (int i = 0; i < nDeck; i++)                                      // создание палуб и "поля" по сторонам палуб
				{
					MainUserBattlefield[y_t][x_t + i] = 40 + nDeck;
					if(y_t + 1 <= y - 1)MainUserBattlefield[y_t + 1][x_t + i] = 2;
					if(y_t - 1 >= 0)MainUserBattlefield[y_t - 1][x_t + i] = 2;
				}// for i
				if (x_t + 1 <= x - 1)                                                // создание "поля" перед кораблём
				{
					if(y_t - 1 >= 0)MainUserBattlefield[y_t - 1][x_t + nDeck] = 2;
					if(y_t + 1 <= y - 1)MainUserBattlefield[y_t + 1][x_t + nDeck] = 2;
					MainUserBattlefield[y_t][x_t + nDeck] = 2;
				}
				if(test == 0 || test == 2 || test == 5 || test == 9)nDeck--; // если созданы все 4\3\2\1 - палубники уменьш количество палуб
				x_t = 0;                                                     // обнуление координат
				y_t = 0;                                                     // обнуление координат
				test++;
				CreateShip(TempUserBattlfield, y_t, x_t, nDeck);             // создание след. корабля
			}// if
			if (ItRotated)                                                          // Если корабль расположен вертикально
			{
				for (k = 0; k < nDeck; k++)
				{
					if (MainUserBattlefield[y_t + k][x_t] != 0) // Не годны! Следующий!
					{
						cout << "\n\n\tВы не можете поставить тут корабль";
						Sleep(500);
						flag = false;
						break;
					}// if
				}// for
				if (!flag) break;
				if (y_t - 1 >= 0)                                                    // создание "поля" за кораблём
				{
					if(x_t - 1 >= 0)MainUserBattlefield[y_t - 1][x_t - 1] = 2;
					if(x_t + 1 <= x - 1)MainUserBattlefield[y_t - 1][x_t + 1] = 2;
					MainUserBattlefield[y_t - 1][x_t] = 2;
				}// if
				for (int i = 0; i < nDeck; i++)                                      // создание палуб и "поля" по сторонам палуб
				{
					MainUserBattlefield[y_t + i][x_t] = 40 + nDeck;
					if(x_t + 1 <= x - 1)MainUserBattlefield[y_t + i][x_t + 1] = 2;
					if(x_t - 1 >= 0)MainUserBattlefield[y_t + i][x_t - 1] = 2;
				}// for i
				if (y_t + nDeck <= y - 1)                                            // создание "поля" перед кораблём
				{
					if(x_t - 1 >= 0 )MainUserBattlefield[y_t + nDeck][x_t - 1] = 2;
					if(x_t + 1 <= x - 1 )MainUserBattlefield[y_t + nDeck][x_t + 1] = 2;
					MainUserBattlefield[y_t + nDeck][x_t] = 2;
				}// if
				if (test == 0 || test == 2 || test == 5 || test == 9)nDeck--; // если созданы все 4\3\2\1 - палубники уменьш количество палуб
				x_t = 0;                                                      // обнуление координат
				y_t = 0;                                                      // обнуление координат
				test++;
				ItRotated = false;
				CreateShip(TempUserBattlfield, y_t, x_t, nDeck);              // создание след. корабля
			}// if
		
		}// switch
		ShowUserBattlefield(MainUserBattlefield, x, y, TempUserBattlfield, x_t, y_t, nDeck, ItRotated); // вывод поля
		if (test == 10) break;  // если корабли расставлены то уходим
	}// while
}// ShipArrangement

void HowToPlay()   // вывод правил
{
	system("cls");
	cout << "\n    «Морской бой» — игра для двух участников, в которой игроки по очереди называют координаты на неизвестной им карте соперника.\n   Если у соперника по этим координатам имеется корабль (координаты заняты), то корабль или его часть «топится», а попавший получает право сделать ещё один ход.\n   Цель игрока — первым потопить все корабли противника. ";
	cout << R"(
    Игровое поле — обычно квадрат 10x10 у каждого игрока, на котором размещается флот кораблей. Горизонтали обычно нумеруются сверху вниз,
    а вертикали помечаются буквами слева направо. При этом используются буквы русского алфавита от «а» до «к» (буквы «ё» и «й» обычно пропускаются)
    либо от «а» до «и» (с использованием буквы «ё»), либо буквы латинского алфавита от «a» до «j».

    Размещаются:

    1 корабль — ряд из 4 клеток («четырёхпалубный»; линкор)
    2 корабля — ряд из 3 клеток («трёхпалубные»; крейсера)
    3 корабля — ряд из 2 клеток («двухпалубные»; эсминцы)
    4 корабля — 1 клетка («однопалубные»; торпедные катера)
    
    При размещении корабли не могут касаться друг друга сторонами и углами.
    
    Игрок, выполняющий ход, совершает выстрел — называет координаты клетки, в которой, по его мнению, находится корабль противника, например, «В1».
         1. Если выстрел пришёлся в клетку, не занятую ни одним кораблём противника, стрелявший игрок ставит на чужом квадрате в этом месте точку.
         Право хода переходит к сопернику.
         2. Если выстрел пришёлся в клетку, где находится многопалубный корабль (размером больше чем 1 клетка). Стрелявший игрок ставит на чужом поле
         в эту клетку крестик, а его противник ставит крестик на своём поле также в эту клетку. Стрелявший игрок получает право на ещё один выстрел.
         3. Если выстрел пришёлся в клетку, где находится однопалубный корабль, или последнюю непоражённую клетку многопалубного корабля.
         Оба игрока отмечают потопленный корабль. Стрелявший игрок получает право на ещё один выстрел.

    Победителем считается тот, кто первым потопит все 10 кораблей противника. Проигравший имеет право попросить изучить после окончания игры
    у соперника игровое поле. )";

}// HowToPlay


