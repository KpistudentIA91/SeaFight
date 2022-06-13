#include "stdafx.h"
#include "Utils.h"
#include "EnemyAI.h"

void ShowEnemyBattlefield(int **MainEnemyBattlefield, int x, int y, int **MainUserBattlefield, int x_t, int y_t, bool playerChek, int enemyScore) // ����������� ���� ��� �����
{
	system("cls");
	cout << "\n\n";
	char symbol = 65;                             // �������� ����������� ��������
	int number = 0;                               // ��������� �����
	cout << "\t\b\b\b\b";
	for (int i = 0; i < 10; i++)                  // ����� ���������� ���������
	{
		cout << "   " << symbol;
		symbol++;
	}
	symbol = 65;
	cout << "\t\t\t\t\t\t\t\b\b\b\b\b";
	for (int i = 0; i < 10; i++)                   // ����� ���������� ���������
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
		cout << setw(2) << ++number;                // ��������� �����
		cout << "\t\b\b\b";
		for (int j = 0; j < x; j++)
		{
			cout << "|";
			if(!playerChek)
			{
				if (i == y_t && j == x_t) SetColor(TURQUOISE_BACKGROUND);      // ���� �������� ����, �������� ����
				else SetColor(GREY_BACKGROUND);
			}// if
			switch (MainUserBattlefield[i][j])
			{
			case 0: case 2:                        // ������ ������� ����
				cout << "   ";
				break;
			case 1:                                // ������ ���� � ������� ��� ��������� �������
				cout << " * ";
				break;
			case 31: case 32: case 33: case 34:    // ������������ ������� �������
				SetColor(RED);
				if(!playerChek)
				{
					if (i == y_t && j == x_t) SetColor(RED_BACKGROUND);
					else SetColor(GREY_BACKGROUND_RED_LAT);
				}// if
				cout << "[X]";
				SetColor(GREY);
				break;
			case 41: case 42: case 43: case 44:    // ������� �������
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
				if (i == y_t && j == x_t) SetColor(TURQUOISE_BACKGROUND); // ���� �������� �����, �������� ����
				else SetColor(GREY_BACKGROUND);
			}// if
			switch (MainEnemyBattlefield[i][j])
			{
			case 0: case 2:                        // ������ ������� ����
				cout << "   ";
				break;
			case 1:                                // ������ ���� � ������� ��� ��������� �������
				cout << " * ";
				break;
			case 31: case 32: case 33: case 34:    // ������������ ������� �������
				SetColor(RED);
				if(playerChek)
				{
					if (i == y_t && j == x_t) SetColor(RED_BACKGROUND);
					else SetColor(GREY_BACKGROUND_RED_LAT);
				}// if
				cout << "[X]";
				SetColor(GREY);
				break;
			case 41: case 42: case 43: case 44:    // ������� �������
				
				if (enemyScore < 10 /*false*/)     // ����������������� false ����� ������ ��������� �������
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

void RandomShipArrangement(int **Battlefield, int x, int y)           // ��������� ������������ ��������
{
	register int x_t, y_t, nDeck = 4;                                 // ���������� � ���������� �����
	int test = 0;                                                     // ���������� ������������� �����
	bool ItRotated;                                                   // ���������� �������, �������������� (false), ������������ (true)

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)                                   // ������� ����, ���� ����� ��� ���� �������
		{
			if (Battlefield[i][j] != 0) Battlefield[i][j] = 0;
		}// for j
	}// for i

	while (true)
	{
		ItRotated = Random(0, 1);                                      // ��������� ���������� �������
		x_t = Random(0, x - 1);                                        // ��������� ���������
		y_t = Random(0, y - 1);                                        // ��������� ���������
		int k;
		bool flag = true;                                              // ���� ��� �������� �������� ���������

		if (!ItRotated)                                                        // ���� ������� ���������� �������������
		{
			for (k = 0; k < nDeck; k++)
			{
				if(x_t + nDeck > x - 1)                                // ��������: �� ������� �� ������� �� ������� ����
				{
					flag = false;
					break;
				}
				
				if (Battlefield[y_t][x_t + k] != 0)                    // ��������: �� ������������� �� ������� �� ������ �������
				{
					flag = false;
					break;
				}
			}// for
			if (!flag) continue;                                       // ���� ���������� �� �������� �� ��������� ������
			                                             
			if (x_t - 1 >= 0)                                          // �������� "����" �� �������
			{
				if (y_t - 1 >= 0) Battlefield[y_t - 1][x_t - 1] = 2;
				if (y_t + 1 <= y - 1) Battlefield[y_t + 1][x_t - 1] = 2;
				Battlefield[y_t][x_t - 1] = 2;
			}
			for (int i = 0; i < nDeck; i++)                            // �������� ����� � "����" �� �������� �����
			{
				Battlefield[y_t][x_t + i] = 40 + nDeck;
				if (y_t + 1 <= y - 1)Battlefield[y_t + 1][x_t + i] = 2;
				if (y_t - 1 >= 0)Battlefield[y_t - 1][x_t + i] = 2;
			}// for i
			if (x_t + nDeck <= x - 1)                                   // �������� "����" ����� �������
			{
				if (y_t - 1 >= 0)Battlefield[y_t - 1][x_t + nDeck] = 2;
				if (y_t + 1 <= y - 1)Battlefield[y_t + 1][x_t + nDeck] = 2;
				Battlefield[y_t][x_t + nDeck] = 2;
			}
			if (test == 0 || test == 2 || test == 5 || test == 9)nDeck--; // ���� ������� ��� 4\3\2\1 - ��������� ������ ���������� �����
			x_t = 0;                                                      // ��������� ���������
			y_t = 0;                                                      // ��������� ���������
			test++;

		}// if
		if (ItRotated)                                                          // ���� ������� ���������� �����������
		{
			for (k = 0; k < nDeck; k++)
			{
				if(y_t + nDeck > y - 1)                                  // ��������: �� ������� �� ������� �� ������� ����
				{
					flag = false;
					break;
				}
				if (Battlefield[y_t + k][x_t] != 0)                      // ��������: �� ������������� �� ������� �� ������ �������
				{
					flag = false;
					break;
				}// if
			}// for
			if (!flag) continue;                                          // ���� ���������� �� �������� �� ��������� ������
			 
			if (y_t - 1 >= 0)                                             // �������� "����" �� �������
			{
				if (x_t - 1 >= 0)Battlefield[y_t - 1][x_t - 1] = 2;
				if (x_t + 1 <= x - 1)Battlefield[y_t - 1][x_t + 1] = 2;
				Battlefield[y_t - 1][x_t] = 2;
			}// if 
			for (int i = 0; i < nDeck; i++)                               // �������� ����� � "����" �� �������� �����
			{
				Battlefield[y_t + i][x_t] = 40 + nDeck;
				if (x_t + 1 <= x - 1)Battlefield[y_t + i][x_t + 1] = 2;
				if (x_t - 1 >= 0)Battlefield[y_t + i][x_t - 1] = 2;
			}// for i
			if (y_t + nDeck <= y - 1)                                     // �������� "����" ����� �������
			{
				if (x_t - 1 >= 0)Battlefield[y_t + nDeck][x_t - 1] = 2;
				if (x_t + 1 <= x - 1)Battlefield[y_t + nDeck][x_t + 1] = 2;
				Battlefield[y_t + nDeck][x_t] = 2;
			}// if
			if (test == 0 || test == 2 || test == 5 || test == 9)nDeck--; // ���� ������� ��� 4\3\2\1 - ��������� ������ ���������� �����
			x_t = 0;                                                      // ��������� ���������
			y_t = 0;                                                      // ��������� ���������
			test++;                            
			ItRotated = false;                               
		}// if
		if (test == 10) return;                                           // ���� ��� ������� ����������� �� ����� �� �������
	}//while
}// RandomShipArrangement 
