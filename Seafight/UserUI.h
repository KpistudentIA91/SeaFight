#pragma once

void ShowUserBattlefield(int **MainUserBattlefield, int x, int y, int **TempUserBattlefield, register int x_t, register int y_t, int nDeck, bool ItRotated); // вывод поля
void CreateShip(int **TempUserBattlfield, int y_t, int x_t, int nDeck);                                                                                      // создание корабля
void ShipArrangement(int **TempUserBattlfield, int x, int y, int **MainUserBattlefield, int &ch);                                                            // расстановка кораблей
void HowToPlay();                                                                                                                                            // вывод инструкции


