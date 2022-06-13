#include "stdafx.h"
#include "Utils.h"
#include "Game.h"
#include "UserUI.h"
#include "EnemyAI.h"


void StartGame()
{
	int x = 10, y = 10, x_t = 0, y_t = 0, ch, score = 0, enemyScore = 0, temp;                                  // макс. координаты, координаты кораблей, id клавищи, 
	int **ptrMainUserBattlefield = CreateMatrix(y, x, 0, 0);                                                    // матрица поля игрока, сразу заполнена нулями
	int **ptrTempUserBattlefield = CreateMatrix(y, x, 0, 0);                                                    // временная матрица поля игрока, сразу заполнена нулями
	int **ptrEnemyBattlefield = CreateMatrix(y, x, 0, 0);                                                       // матрица поля ИИ, сразу заполнена нулями
	bool hit = false, playerChek = true, ItRotated = false, health = false;                                     // Попадание, чей ход, ориентация корабля, уничтожение

 	RandomShipArrangement(ptrEnemyBattlefield, x, y);                                                           // на поле ИИ расставляются корабли
	ShipArrangement(ptrTempUserBattlefield, x, y, ptrMainUserBattlefield, ch);                                  // расстановка кораблей игрока
	//if (ch == 27) return;
	ch = 0;
	DestroyMatrix(ptrTempUserBattlefield, y);                                                                   // удаление временной матрицы
	ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);  // вывод поля боя

	while (true)
	{
		
		playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ход игрока
		
		
		if(score == 10)                  // если все вражеские корабли уничтоженны то это победа!
		{
			cout << "\n\n\t\t\t\t\t\t\t\t Вы победили!";
			break;
		}
		
		if (ch == 27) break;             // если нажат esc то выход

		if (ch == 13)                    // если нажат enter то ход передается ИИ
		{

			while (true)
			{
				temp = enemyScore;       // во временную переменную записывается счёт ИИ
				x_t = Random(0, x - 1);  // Случайные координаты
				y_t = Random(0, y - 1);
				hit = false;             // Проверка на попадание
				if (ptrMainUserBattlefield[y_t][x_t] == 1 || ptrMainUserBattlefield[y_t][x_t] >= 30 && ptrMainUserBattlefield[y_t][x_t] <= 40) continue; // если по етим координатам стреляли то генерируй новые
				ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // вывод поля
				Sleep(500);
				Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);  // Выстрел
				if (temp < enemyScore) continue;
				if (hit)                                                                    
				{
					hit = false;
					while (true)
					{
						int n = Random(1, 4);                                                // генерация случайного направления
						switch (n)
						{
						case 1:
							if (y_t - 1 < 0 || ptrMainUserBattlefield[y_t - 1][x_t] == 1 || ptrMainUserBattlefield[y_t - 1][x_t] >= 31 && ptrMainUserBattlefield[y_t - 1][x_t] <= 34) // если в эти координаты уже стреляли, или в них нельзя выстрелить - генерируй новое направление
							{
								continue;
							}// if
							y_t--;                                                                                                                   
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);               // вывод поля
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                      // Выстрел!
							if (hit)                                                                                                                 // Если попал то стреляй вверх пока не промахнешься или не уничтожишь
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t - i, playerChek, enemyScore);   // вывод поля
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t - i, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                        // Если уничтожил стреляй по случайным координатам
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // Если промахнулся то дай выстрел игроку
								y_t++;
								for (int i = 1;; i++)                                                                                                // И стреляй в противоположную сторону пока не уничтожишь
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t + i, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t + i, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health);   // Если промахнулся то дай выстрел игроку, и стреляй в другую сторону
							y_t++;
							continue;
						case 2:
							if (y_t + 1 > y - 1 || ptrMainUserBattlefield[y_t + 1][x_t] == 1 || ptrMainUserBattlefield[y_t + 1][x_t] >= 31 && ptrMainUserBattlefield[y_t + 1][x_t] <= 32) // если в эти координаты уже стреляли, или в них нельзя выстрелить - генерируй новое направление
							{
								continue;
							}// if
							y_t++;                                                                                                                   
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);               // вывод поля
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                      // Выстрел!
							if (hit)                                                                                                                 // Если попал то стреляй вниз пока не промахнешься или не уничтожишь
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t + i, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t + i, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                     // Если уничтожил стреляй по случайным координатам
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // Если промахнулся то дай выстрел игроку
								y_t--;
								for (int i = 1;; i++)                                                                                                // И стреляй в противоположную сторону пока не уничтожишь
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t - i, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t - i, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health);  // Если промахнулся то дай выстрел игроку, и стреляй в другую сторону
							y_t--;
							continue;
						case 3:
							if (x_t + 1 > x - 1 || ptrMainUserBattlefield[y_t][x_t + 1] == 1 || ptrMainUserBattlefield[y_t][x_t + 1] >= 31 && ptrMainUserBattlefield[y_t][x_t + 1] <= 34)// если в эти координаты уже стреляли, или в них нельзя выстрелить - генерируй новое направление
							{
								continue;
							}// if
							x_t++;                                                                                                                   
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);               // вывод поля
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                      // Выстрел!
							if (hit)                                                                                                                 // Если попал то стреляй вправо пока не промахнешься или не уничтожишь
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t + i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t + i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                     // Если уничтожил стреляй по случайным координатам
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // Если промахнулся то дай выстрел игроку
								x_t--;
								for (int i = 1;; i++)                                                                                                // И стреляй в противоположную сторону пока не уничтожишь
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t - i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t - i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // Если промахнулся то дай выстрел игроку, и стреляй в другую сторону
							x_t--;
							continue;

						case 4:
							if (x_t - 1 < 0 || ptrMainUserBattlefield[y_t][x_t - 1] == 1 || ptrMainUserBattlefield[y_t][x_t - 1] >= 31 || ptrMainUserBattlefield[y_t][x_t - 1] <= 34) // если в эти координаты уже стреляли, или в них нельзя выстрелить - генерируй новое направление
							{
								continue;
							}
							x_t--;                                                                                                                     
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);              // вывод поля
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                     // Выстрел!
							if (hit)                                                                                                                // Если попал то стреляй влево пока не промахнешься
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t - i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t - i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                                      // Если уничтожил стреляй по случайным координатам
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // Если промахнулся то дай выстрел игроку
								x_t++;
								for (int i = 1;; i++)                                                                                                              // И стреляй в противоположную сторону пока не уничтожишь
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t + i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t + i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // Если промахнулся то дай выстрел игроку, и стреляй в другую сторону
							x_t++;
							continue;
						}// switch
						
						break;
					}// while
				}// if
				if (temp < enemyScore) continue; // если ИИ уничтожил корабль то стреляет ещё раз
				break;
			}// while
		
		}// if
		if (enemyScore == 10)                   // если вы потеря все корабли то это фиаско
		{
			cout << "\n\n\t\t\t\t\t\t\t\t Вы проиграли!";
			break;
		}// if
		
		ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);  // вывод поля
	}// while



	DestroyMatrix(ptrMainUserBattlefield, y);          // удаление матриц и выход из игры
	DestroyMatrix(ptrEnemyBattlefield, y);
}// StartGame



void Fire(int **EnemyBattlefield, int x_t, int y_t, bool &hit, int &score, bool playerChek, int &enemyScore, bool health) // функция выстрела ИИ
{
	int nDeck = 0;                    // количество палуб корабля в который попали
	int distanceToLeft = 0;           // количество клеток до самой левой/верхней палубы
	bool ItRotated = false;           // ориентация корабля (по дефолту false чтоб не крашило при попадании в однопалубник)

	if (y_t + 1 <= 9) if (EnemyBattlefield[y_t + 1][x_t] > 30) ItRotated = true; // если палубы уходят вверх или вниз то это вертикальный корабль
	if (y_t - 1 >= 0) if (EnemyBattlefield[y_t - 1][x_t] > 30) ItRotated = true;
	if (EnemyBattlefield[y_t][x_t - 1] > 30) ItRotated = false;                  // если палубы уходят влево или вправо то это горизонтальный корабль
	if (EnemyBattlefield[y_t][x_t + 1] > 30) ItRotated = false;

	if (EnemyBattlefield[y_t][x_t] > 40)                                         // если в клетке был кораль то...
	{
		EnemyBattlefield[y_t][x_t] -= 10;                                        // отними от id палубы 10 что получить id уничтоженной палубы
		
		// Вычисление количества палуб
		if (!ItRotated) // Если корабль расположен горизонтально...
		{
			for (int j = 0; j < 4; j++)                     // двигайся вправо
			{
				if (EnemyBattlefield[y_t][x_t + j] == 0 || EnemyBattlefield[y_t][x_t + j] == 1 || EnemyBattlefield[y_t][x_t + j] == 2) break; // если дальше ничего нет то выйди из цикла
				if (EnemyBattlefield[y_t][x_t + j] > 30) nDeck++;                                                                             // если дальше палуба засчитай её                                            
			}// for j                                                                                                                               
				 
			for (int j = 1; j < 4; j++)                     // двигайся влево
			{
				if (x_t - j < 0) break;
				if (EnemyBattlefield[y_t][x_t - j] == 0 || EnemyBattlefield[y_t][x_t - j] == 1 || EnemyBattlefield[y_t][x_t - j] == 2) break;  // если дальше ничего нет то выйди из цикла
				if (EnemyBattlefield[y_t][x_t - j] > 30) nDeck++;                                                                              // если дальше палуба засчитай её
				distanceToLeft++;
			}// for j
			x_t -= distanceToLeft;            // Перенос на самую левую/верхнею палубу
			for (int i = 0; i < nDeck; i++)   // Проверка "Есть ли ещё целые сегменты?"
			{
				if (EnemyBattlefield[y_t][x_t + i] > 40) health = true;
			}// if
		} // if
		else            // Если корабль расположен вертикально...
		{
			for (int j = 0; j < 4; j++)                      // двигайся вниз 
			{
				if (EnemyBattlefield[y_t + j][x_t] == 0 || EnemyBattlefield[y_t + j][x_t] == 1 || EnemyBattlefield[y_t + j][x_t] == 2) break; // если дальше ничего нет то выйди из цикла
				if (EnemyBattlefield[y_t + j][x_t] > 30) nDeck++;                                                                             // если дальше палуба засчитай её
			}// for j        
			for (int j = 1; j < 4; j++)                      // двигайся вверх 
			{
				if (y_t - j < 0) break;                                                                                                       // если вышли за пределы поля то выйди из цикла
				if (EnemyBattlefield[y_t - j][x_t] == 0 || EnemyBattlefield[y_t - j][x_t] == 1 || EnemyBattlefield[y_t - j][x_t] == 2) break; // если дальше ничего нет то выйди из цикла
				if (EnemyBattlefield[y_t - j][x_t] > 30) nDeck++;                                                                             // если дальше палуба засчитай её
				distanceToLeft++;
			}// for j
			y_t -= distanceToLeft;            // Перенос на самую левую/верхнею палубу
			for (int i = 0; i < nDeck; i++)   // Проверка "Есть ли ещё целые сегменты?"
			{
				if (EnemyBattlefield[y_t + i][x_t] > 40) health = true;
			}// if
		}// if
		
		if (!health)   // Целые сегменты не обнаружены, затопление корабля
		{
			if (!ItRotated)   // если корабль горизонтален
			{
				
				if (x_t - 1 >= 0)                                                   //клетки вокруг получают значения пустых
				{
					if (y_t - 1 >= 0) EnemyBattlefield[y_t - 1][x_t - 1] = 1;
					if (y_t + 1 <= 10 - 1) EnemyBattlefield[y_t + 1][x_t - 1] = 1;
					EnemyBattlefield[y_t][x_t - 1] = 1;
				}// if
				for (int i = 0; i < nDeck; i++)
				{
					if (y_t + 1 <= 10 - 1)EnemyBattlefield[y_t + 1][x_t + i] = 1;
					if (y_t - 1 >= 0)EnemyBattlefield[y_t - 1][x_t + i] = 1;
				}// for i
				if (x_t + 1 <= 10 - 1)
				{
					if (y_t - 1 >= 0)EnemyBattlefield[y_t - 1][x_t + nDeck] = 1;
					if (y_t + 1 <= 10 - 1)EnemyBattlefield[y_t + 1][x_t + nDeck] = 1;
					EnemyBattlefield[y_t][x_t + nDeck] = 1;
				}// if
				if (playerChek)	score++;
				else enemyScore++;
			}
			else              // если корабль вертикален
			{
				//y_t -= distanceToLeft;
				if (y_t - 1 >= 0)                                                   //клетки вокруг получают значения пустых
				{
					if (x_t - 1 >= 0)EnemyBattlefield[y_t - 1][x_t - 1] = 1;
					if (x_t + 1 <= 9)EnemyBattlefield[y_t - 1][x_t + 1] = 1;
					EnemyBattlefield[y_t - 1][x_t] = 1;
				}// if
				for (int i = 0; i < nDeck; i++)
				{
					if (x_t + 1 <= 9)EnemyBattlefield[y_t + i][x_t + 1] = 1;
					if (x_t - 1 >= 0)EnemyBattlefield[y_t + i][x_t - 1] = 1;
				}// for i
				if (y_t + nDeck <= 9)
				{
					if (x_t - 1 >= 0)EnemyBattlefield[y_t + nDeck][x_t - 1] = 1;
					if (x_t + 1 <= 9)EnemyBattlefield[y_t + nDeck][x_t + 1] = 1;
					EnemyBattlefield[y_t + nDeck][x_t] = 1;
				}// if
				if (playerChek)	score++;     // засчитай корабль тому кто ходил                                     
				else enemyScore++;
			}// if
		}// if
		hit = true; // Если было попадание то игроку будет предоставлен ещё ход
	}// if
	else if (EnemyBattlefield[y_t][x_t] == 0 || EnemyBattlefield[y_t][x_t] == 2 || EnemyBattlefield[y_t][x_t] == 1) // если промохнулся то...
	{
		EnemyBattlefield[y_t][x_t] = 1;         // пометь клетку пустой
		hit = false;                            // сообщи о промахе
	}
}// Fire


void playerFire(int **ptrEnemyBattlefield, int **ptrMainUserBattlefield, int x, int y,int x_t, int y_t, int &score, bool hit, bool &playerChek, int &enemyScore, int &ch, bool health) // ход игрока
{
	playerChek = true;                               
	x_t = 0;                                 
	y_t = 0;                                 
	ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // вывод поля
	while (true)
	{
		hit = false;                         
		ch = _getch();                       
		if (ch == 224) continue;             
		
		switch (ch)
		{
		case 80:                             
			if (y_t == y - 1) break;        
			y_t++;                           
			break;
		case 72:                             
			if (y_t == 0) break;             
			y_t--;                          
			break;
		case 75:                             
			if (x_t == 0) break;             
			x_t--;                           
			break;
		case 77:                             
			if (x_t == x - 1) break;         
			x_t++;                           
			break;
		case 13:                             // если enter...
			if (ptrEnemyBattlefield[y_t][x_t] == 1 || ptrEnemyBattlefield[y_t][x_t] >= 30 && ptrEnemyBattlefield[y_t][x_t] <= 40) // не даём игроку вестрелить дважды в одно место
			{
				cout << "\n\n\t\t\t\t\t\t\t\t Вы уже стреляли сюда";
				continue;
			}
			Fire(ptrEnemyBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);               // Залп!!
			if (!hit || score == 10) break;                                                                // если промахнулись, или уничтожили последний корабль то уходим
			ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // вывод поля
			if (hit) continue;                                                                             // если попал то стреляй ещё раз
		case 27:                                                                                           // если esc то уходи
			return;
	    }// switch
		ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // вывод поля
		if (ch == 13) if (!hit || score == 10) break;       // если был нажат enter и делать нам тут больше нечего то уходим
	}// while
	playerChek = false;   // передаём ход ИИ
}// playerFire