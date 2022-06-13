#pragma once


void StartGame();                                                                                                         // игра
void Fire(int **EnemyBattlefield, int x_t, int y_t, bool &hit, int &score, bool playerChek, int &enemyScore, bool health);// ход ИИ
void playerFire(int **ptrEnemyBattlefield, int **ptrMainUserBattlefield, int x, int y, int x_t, int y_t, int &score, bool hit, bool &playerChek, int &enemyScore, int &ch, bool health); // ход игрока