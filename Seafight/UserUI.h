#pragma once

void ShowUserBattlefield(int **MainUserBattlefield, int x, int y, int **TempUserBattlefield, register int x_t, register int y_t, int nDeck, bool ItRotated); // ����� ����
void CreateShip(int **TempUserBattlfield, int y_t, int x_t, int nDeck);                                                                                      // �������� �������
void ShipArrangement(int **TempUserBattlfield, int x, int y, int **MainUserBattlefield, int &ch);                                                            // ����������� ��������
void HowToPlay();                                                                                                                                            // ����� ����������


