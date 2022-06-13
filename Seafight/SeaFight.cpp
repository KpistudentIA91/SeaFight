#include "stdafx.h"
#include "Menu.h"
#include "UserUI.h"
#include "EnemyAI.h"
#include "Game.h"
#include "Utils.h"
#include <Windows.h>

int main()
{
	Init();
	

	while (true)
	{
		int menu = MainMenu();
		while (true)
		{
			switch (menu)
			{
			case 1:
				StartGame();
				break;
			case 2:
				HowToPlay();
				break;
			case 3:

				break;
			case 4:

				break;
			case 0:
				exit(1);
			}//switch
			if (PostMenu() == 1)continue;
			else break;//if
		}//while
	}//while
}//main