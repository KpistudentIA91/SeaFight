#include "stdafx.h"
#include "Utils.h"
#include "Game.h"
#include "UserUI.h"
#include "EnemyAI.h"


void StartGame()
{
	int x = 10, y = 10, x_t = 0, y_t = 0, ch, score = 0, enemyScore = 0, temp;                                  // ����. ����������, ���������� ��������, id �������, 
	int **ptrMainUserBattlefield = CreateMatrix(y, x, 0, 0);                                                    // ������� ���� ������, ����� ��������� ������
	int **ptrTempUserBattlefield = CreateMatrix(y, x, 0, 0);                                                    // ��������� ������� ���� ������, ����� ��������� ������
	int **ptrEnemyBattlefield = CreateMatrix(y, x, 0, 0);                                                       // ������� ���� ��, ����� ��������� ������
	bool hit = false, playerChek = true, ItRotated = false, health = false;                                     // ���������, ��� ���, ���������� �������, �����������

 	RandomShipArrangement(ptrEnemyBattlefield, x, y);                                                           // �� ���� �� ������������� �������
	ShipArrangement(ptrTempUserBattlefield, x, y, ptrMainUserBattlefield, ch);                                  // ����������� �������� ������
	//if (ch == 27) return;
	ch = 0;
	DestroyMatrix(ptrTempUserBattlefield, y);                                                                   // �������� ��������� �������
	ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);  // ����� ���� ���

	while (true)
	{
		
		playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ��� ������
		
		
		if(score == 10)                  // ���� ��� ��������� ������� ����������� �� ��� ������!
		{
			cout << "\n\n\t\t\t\t\t\t\t\t �� ��������!";
			break;
		}
		
		if (ch == 27) break;             // ���� ����� esc �� �����

		if (ch == 13)                    // ���� ����� enter �� ��� ���������� ��
		{

			while (true)
			{
				temp = enemyScore;       // �� ��������� ���������� ������������ ���� ��
				x_t = Random(0, x - 1);  // ��������� ����������
				y_t = Random(0, y - 1);
				hit = false;             // �������� �� ���������
				if (ptrMainUserBattlefield[y_t][x_t] == 1 || ptrMainUserBattlefield[y_t][x_t] >= 30 && ptrMainUserBattlefield[y_t][x_t] <= 40) continue; // ���� �� ���� ����������� �������� �� ��������� �����
				ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // ����� ����
				Sleep(500);
				Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);  // �������
				if (temp < enemyScore) continue;
				if (hit)                                                                    
				{
					hit = false;
					while (true)
					{
						int n = Random(1, 4);                                                // ��������� ���������� �����������
						switch (n)
						{
						case 1:
							if (y_t - 1 < 0 || ptrMainUserBattlefield[y_t - 1][x_t] == 1 || ptrMainUserBattlefield[y_t - 1][x_t] >= 31 && ptrMainUserBattlefield[y_t - 1][x_t] <= 34) // ���� � ��� ���������� ��� ��������, ��� � ��� ������ ���������� - ��������� ����� �����������
							{
								continue;
							}// if
							y_t--;                                                                                                                   
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);               // ����� ����
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                      // �������!
							if (hit)                                                                                                                 // ���� ����� �� ������� ����� ���� �� ������������ ��� �� ����������
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t - i, playerChek, enemyScore);   // ����� ����
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t - i, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                        // ���� ��������� ������� �� ��������� �����������
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ���� ����������� �� ��� ������� ������
								y_t++;
								for (int i = 1;; i++)                                                                                                // � ������� � ��������������� ������� ���� �� ����������
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t + i, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t + i, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health);   // ���� ����������� �� ��� ������� ������, � ������� � ������ �������
							y_t++;
							continue;
						case 2:
							if (y_t + 1 > y - 1 || ptrMainUserBattlefield[y_t + 1][x_t] == 1 || ptrMainUserBattlefield[y_t + 1][x_t] >= 31 && ptrMainUserBattlefield[y_t + 1][x_t] <= 32) // ���� � ��� ���������� ��� ��������, ��� � ��� ������ ���������� - ��������� ����� �����������
							{
								continue;
							}// if
							y_t++;                                                                                                                   
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);               // ����� ����
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                      // �������!
							if (hit)                                                                                                                 // ���� ����� �� ������� ���� ���� �� ������������ ��� �� ����������
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t + i, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t + i, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                     // ���� ��������� ������� �� ��������� �����������
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ���� ����������� �� ��� ������� ������
								y_t--;
								for (int i = 1;; i++)                                                                                                // � ������� � ��������������� ������� ���� �� ����������
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t - i, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t, y_t - i, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health);  // ���� ����������� �� ��� ������� ������, � ������� � ������ �������
							y_t--;
							continue;
						case 3:
							if (x_t + 1 > x - 1 || ptrMainUserBattlefield[y_t][x_t + 1] == 1 || ptrMainUserBattlefield[y_t][x_t + 1] >= 31 && ptrMainUserBattlefield[y_t][x_t + 1] <= 34)// ���� � ��� ���������� ��� ��������, ��� � ��� ������ ���������� - ��������� ����� �����������
							{
								continue;
							}// if
							x_t++;                                                                                                                   
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);               // ����� ����
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                      // �������!
							if (hit)                                                                                                                 // ���� ����� �� ������� ������ ���� �� ������������ ��� �� ����������
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t + i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t + i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                     // ���� ��������� ������� �� ��������� �����������
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ���� ����������� �� ��� ������� ������
								x_t--;
								for (int i = 1;; i++)                                                                                                // � ������� � ��������������� ������� ���� �� ����������
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t - i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t - i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ���� ����������� �� ��� ������� ������, � ������� � ������ �������
							x_t--;
							continue;

						case 4:
							if (x_t - 1 < 0 || ptrMainUserBattlefield[y_t][x_t - 1] == 1 || ptrMainUserBattlefield[y_t][x_t - 1] >= 31 || ptrMainUserBattlefield[y_t][x_t - 1] <= 34) // ���� � ��� ���������� ��� ��������, ��� � ��� ������ ���������� - ��������� ����� �����������
							{
								continue;
							}
							x_t--;                                                                                                                     
							ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);              // ����� ����
							Sleep(500);
							Fire(ptrMainUserBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);                                     // �������!
							if (hit)                                                                                                                // ���� ����� �� ������� ����� ���� �� ������������
							{
								for (int i = 1;; i++)
								{
									if (temp < enemyScore) break;
									if (!hit) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t - i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t - i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								if (temp < enemyScore) break;                                                                                                      // ���� ��������� ������� �� ��������� �����������
								if (!hit) playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ���� ����������� �� ��� ������� ������
								x_t++;
								for (int i = 1;; i++)                                                                                                              // � ������� � ��������������� ������� ���� �� ����������
								{
									if (temp < enemyScore) break;
									ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t + i, y_t, playerChek, enemyScore);
									Sleep(500);
									Fire(ptrMainUserBattlefield, x_t + i, y_t, hit, score, playerChek, enemyScore, health);
								}// for i
								break;
							}// if
							else playerFire(ptrEnemyBattlefield, ptrMainUserBattlefield, x, y, x_t, y_t, score, hit, playerChek, enemyScore, ch, health); // ���� ����������� �� ��� ������� ������, � ������� � ������ �������
							x_t++;
							continue;
						}// switch
						
						break;
					}// while
				}// if
				if (temp < enemyScore) continue; // ���� �� ��������� ������� �� �������� ��� ���
				break;
			}// while
		
		}// if
		if (enemyScore == 10)                   // ���� �� ������ ��� ������� �� ��� ������
		{
			cout << "\n\n\t\t\t\t\t\t\t\t �� ���������!";
			break;
		}// if
		
		ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore);  // ����� ����
	}// while



	DestroyMatrix(ptrMainUserBattlefield, y);          // �������� ������ � ����� �� ����
	DestroyMatrix(ptrEnemyBattlefield, y);
}// StartGame



void Fire(int **EnemyBattlefield, int x_t, int y_t, bool &hit, int &score, bool playerChek, int &enemyScore, bool health) // ������� �������� ��
{
	int nDeck = 0;                    // ���������� ����� ������� � ������� ������
	int distanceToLeft = 0;           // ���������� ������ �� ����� �����/������� ������
	bool ItRotated = false;           // ���������� ������� (�� ������� false ���� �� ������� ��� ��������� � ������������)

	if (y_t + 1 <= 9) if (EnemyBattlefield[y_t + 1][x_t] > 30) ItRotated = true; // ���� ������ ������ ����� ��� ���� �� ��� ������������ �������
	if (y_t - 1 >= 0) if (EnemyBattlefield[y_t - 1][x_t] > 30) ItRotated = true;
	if (EnemyBattlefield[y_t][x_t - 1] > 30) ItRotated = false;                  // ���� ������ ������ ����� ��� ������ �� ��� �������������� �������
	if (EnemyBattlefield[y_t][x_t + 1] > 30) ItRotated = false;

	if (EnemyBattlefield[y_t][x_t] > 40)                                         // ���� � ������ ��� ������ ��...
	{
		EnemyBattlefield[y_t][x_t] -= 10;                                        // ������ �� id ������ 10 ��� �������� id ������������ ������
		
		// ���������� ���������� �����
		if (!ItRotated) // ���� ������� ���������� �������������...
		{
			for (int j = 0; j < 4; j++)                     // �������� ������
			{
				if (EnemyBattlefield[y_t][x_t + j] == 0 || EnemyBattlefield[y_t][x_t + j] == 1 || EnemyBattlefield[y_t][x_t + j] == 2) break; // ���� ������ ������ ��� �� ����� �� �����
				if (EnemyBattlefield[y_t][x_t + j] > 30) nDeck++;                                                                             // ���� ������ ������ �������� �                                            
			}// for j                                                                                                                               
				 
			for (int j = 1; j < 4; j++)                     // �������� �����
			{
				if (x_t - j < 0) break;
				if (EnemyBattlefield[y_t][x_t - j] == 0 || EnemyBattlefield[y_t][x_t - j] == 1 || EnemyBattlefield[y_t][x_t - j] == 2) break;  // ���� ������ ������ ��� �� ����� �� �����
				if (EnemyBattlefield[y_t][x_t - j] > 30) nDeck++;                                                                              // ���� ������ ������ �������� �
				distanceToLeft++;
			}// for j
			x_t -= distanceToLeft;            // ������� �� ����� �����/������� ������
			for (int i = 0; i < nDeck; i++)   // �������� "���� �� ��� ����� ��������?"
			{
				if (EnemyBattlefield[y_t][x_t + i] > 40) health = true;
			}// if
		} // if
		else            // ���� ������� ���������� �����������...
		{
			for (int j = 0; j < 4; j++)                      // �������� ���� 
			{
				if (EnemyBattlefield[y_t + j][x_t] == 0 || EnemyBattlefield[y_t + j][x_t] == 1 || EnemyBattlefield[y_t + j][x_t] == 2) break; // ���� ������ ������ ��� �� ����� �� �����
				if (EnemyBattlefield[y_t + j][x_t] > 30) nDeck++;                                                                             // ���� ������ ������ �������� �
			}// for j        
			for (int j = 1; j < 4; j++)                      // �������� ����� 
			{
				if (y_t - j < 0) break;                                                                                                       // ���� ����� �� ������� ���� �� ����� �� �����
				if (EnemyBattlefield[y_t - j][x_t] == 0 || EnemyBattlefield[y_t - j][x_t] == 1 || EnemyBattlefield[y_t - j][x_t] == 2) break; // ���� ������ ������ ��� �� ����� �� �����
				if (EnemyBattlefield[y_t - j][x_t] > 30) nDeck++;                                                                             // ���� ������ ������ �������� �
				distanceToLeft++;
			}// for j
			y_t -= distanceToLeft;            // ������� �� ����� �����/������� ������
			for (int i = 0; i < nDeck; i++)   // �������� "���� �� ��� ����� ��������?"
			{
				if (EnemyBattlefield[y_t + i][x_t] > 40) health = true;
			}// if
		}// if
		
		if (!health)   // ����� �������� �� ����������, ���������� �������
		{
			if (!ItRotated)   // ���� ������� ������������
			{
				
				if (x_t - 1 >= 0)                                                   //������ ������ �������� �������� ������
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
			else              // ���� ������� ����������
			{
				//y_t -= distanceToLeft;
				if (y_t - 1 >= 0)                                                   //������ ������ �������� �������� ������
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
				if (playerChek)	score++;     // �������� ������� ���� ��� �����                                     
				else enemyScore++;
			}// if
		}// if
		hit = true; // ���� ���� ��������� �� ������ ����� ������������ ��� ���
	}// if
	else if (EnemyBattlefield[y_t][x_t] == 0 || EnemyBattlefield[y_t][x_t] == 2 || EnemyBattlefield[y_t][x_t] == 1) // ���� ����������� ��...
	{
		EnemyBattlefield[y_t][x_t] = 1;         // ������ ������ ������
		hit = false;                            // ������ � �������
	}
}// Fire


void playerFire(int **ptrEnemyBattlefield, int **ptrMainUserBattlefield, int x, int y,int x_t, int y_t, int &score, bool hit, bool &playerChek, int &enemyScore, int &ch, bool health) // ��� ������
{
	playerChek = true;                               
	x_t = 0;                                 
	y_t = 0;                                 
	ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // ����� ����
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
		case 13:                             // ���� enter...
			if (ptrEnemyBattlefield[y_t][x_t] == 1 || ptrEnemyBattlefield[y_t][x_t] >= 30 && ptrEnemyBattlefield[y_t][x_t] <= 40) // �� ��� ������ ���������� ������ � ���� �����
			{
				cout << "\n\n\t\t\t\t\t\t\t\t �� ��� �������� ����";
				continue;
			}
			Fire(ptrEnemyBattlefield, x_t, y_t, hit, score, playerChek, enemyScore, health);               // ����!!
			if (!hit || score == 10) break;                                                                // ���� ������������, ��� ���������� ��������� ������� �� ������
			ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // ����� ����
			if (hit) continue;                                                                             // ���� ����� �� ������� ��� ���
		case 27:                                                                                           // ���� esc �� �����
			return;
	    }// switch
		ShowEnemyBattlefield(ptrEnemyBattlefield, x, y, ptrMainUserBattlefield, x_t, y_t, playerChek, enemyScore); // ����� ����
		if (ch == 13) if (!hit || score == 10) break;       // ���� ��� ����� enter � ������ ��� ��� ������ ������ �� ������
	}// while
	playerChek = false;   // ������� ��� ��
}// playerFire