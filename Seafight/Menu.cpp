#include "stdafx.h"
#include "Menu.h"
#include "Utils.h"
int MainMenu()
{
	// ���� v2.2!  ������ ������������ esc!
	const int HEIGHT = 2, LONG = 11, M = 10, N = 10, iHEIGHT = 2, iLONG = 4;
	int ch, t = 1, menu = 1, j, imenu = 1;
	char name[HEIGHT][LONG] = { "�����", "��� ������"}, iname[iHEIGHT][iLONG] = { "��", "���" }; //������ ������������ �����
	while (true)
	{
		menu = 1;
		//����� ����
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\b\b\b\b������� ���\n\n";
		for (j = 0; j < HEIGHT; j++)
		{
			if (t == 0) t = 2;//if
			if (t == 3) t = 1;//if
			if (menu == t) SetColor(TURQUOISE);//if
			cout << "\t\t\t\t\t\t\t\t\t\b\b\b\b\b\b ";
			for (int i = 0; i < LONG; i++) cout << name[j][i];//for i
			cout << "\n";
			menu++;
			SetColor(GREY);
		}//for j
		if (menu == t) SetColor(TURQUOISE);//if
		cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t*esc - �����";
		//cout << "\n\t\t\t\t\t\t\t*1-3 - ������� �������";
		//����� �������� ����
		for (;;)
		{
			ch = _getch();
			// ������� �� �����
			switch (ch)
			{
			// ���� ������ ��������� ����
			case 72: case 119:
				t--;
				break;
		    // ���� ������ ��������� �����
			case 80: case 115:
				t++;
				break;
			// ���� ����� esc 
			case 27:
				t = 1;
				while(true)
				{
					imenu = 1;
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n";
					cout << "\t\t\t\t\t\t\t\t�� ������� ��� ������ �����?";
					cout << "\n\n\n\n";
					cout << "\t\t\t\t\t";
					for (j = 0; j < iHEIGHT; j++)
					{
						if (t == 0) t = 2;//if
						if (t == 3) t = 1;//if
						if (imenu == t) SetColor(TURQUOISE);//if
						cout << "\t\t\t";
						for (int i = 0; i < iLONG; i++) cout << iname[j][i];//for i
						imenu++;
						SetColor(GREY);
					}//for j
					ch = _getch();
					switch(ch)
					{
					case 75:
						t++;
						break;
					case 77:
						t--;
						break;
					}//switch
					if(ch == 13)
					{
						if (t == 2) break;
						else return 0;
					}
				}//while
				ch = 0;
				break;
			//case 49:
				//t = 1;
				//break;
			//case 50:
				//t = 2;
				//break;
			//case 51:
				//t = 3;
				//break;
			//case 52:
				//t = 4;
				//break;
			//case 53:
				//t = 5;
				//break;
			//default:
				//cout << "\n"; //��� ������ ������ ��� �������� ID ������ 
				//cout << ch;
				//break;
			}//switch
			break;
		}//for
		if (ch == 13) return t;
	}//while
}//Menu


int PostMenu()
{
	
	int it, ch;
	cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t*esc - ������� � ����";
	//cout << "\n\t\t\t\t\t\t\t*R - ��������� ������";
	while (true)
	{
		for (;;)
		{
			ch = _getch();
			switch (ch)
			{
			case 114:
				it = 1;
				break;
			case 27:
				it = 2;
				break;
				//default:
					//cout << "\n"; //��� ������ ������ ��� �������� ID ������ 
					//cout << ch;
					//break;
			}//switch
			break;
		}//for
		break;
	}//while
	if (ch == 114 || ch == 27)
	{
		return it;
	}//if
}//post menu










