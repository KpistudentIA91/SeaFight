#pragma once

void ShowEnemyBattlefield(int **MainEnemyBattlefield, int x, int y, int **MainUserBattlefield, int x_t, int y_t, bool playerChek, int enemyScore); // Вывод поля ИИ
void RandomShipArrangement(int **MainEnemyBattlefield, int x, int y);                                                                              // Случайная расстановка кораблей