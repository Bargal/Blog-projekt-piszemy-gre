#pragma once

#include "Player.h"
#include "World.h"

/*
*Plik z wszystkimi funkcjami glownej petli gry
*/

int startGame(Player *p_player, World **p_p_worldArr);   //menu startowe gry i wywolania wszystkich funkcji przygotowawczych i konczacych gre, oraz glowna petle gry
void lockArea(Player *p_player, World **p_p_worldArr);   //zamykanie wszystkich wyjsc poza obszar gry
void hardMode(Player *p_player, World **p_p_worldArr);   //zamykanie gdrzwi dla hardmode
int gameLoop(Player *p_player, World **p_p_worldArr);    //glowna petla gry, zwraca znacznik konca gry: 0 - gramy dalej, 1 - zwyciestwo 2 - przegrana: brak zycia, 3 - przegrana: koniec czasu 4 - przegrana: ucieczka.
void areaTextInformation(Player *p_player, World **p_p_worldArr);
int movePlayer(Player* p_player, World **p_p_worldArr);
void areaTextGraphics(Player * p_player, World **p_p_worldArr);
void areaTextPlayerInfo(Player * p_player, World **p_p_worldArr); //opis wplywu pokoju na gracza