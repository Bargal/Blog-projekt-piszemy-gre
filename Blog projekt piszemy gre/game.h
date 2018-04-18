#pragma once

#include "Player.h"
#include "World.h"

/*
*Plik z wszystkimi funkcjami glownej petli gry
*/

int startGame(Player *p_player, World **p_p_worldArr);   //funkcja zawiera menu startowe gry i wywolania wszystkich funkcji przygotowawczych i konczacych gre, oraz glowna petle gry
void lockArea(Player *p_player, World **p_p_worldArr);   //funkcja zamykajaca wszystkie wyjscia poza obszar gry
void hardMode(Player *p_player, World **p_p_worldArr);   //procedura dostosowania planszy gry do trybu trudnego (losowe zamykanie drzwi wewnetrznych)
int gameLoop(Player *p_player, World **p_p_worldArr);    //glowna petla gry, zwraca znacznik konca gry: 0 - gramy dalej, 1 - zwyciestwo 2 - przegrana: brak zycia, 3 - przegrana: koniec czasu 4 - przegrana: ucieczka.
void areaTextInformation(Player *p_player, World **p_p_worldArr);
int movePlayer(Player* p_player, World ** p_p_worldArr);
void areaTextGraphics(Player * p_player, World ** p_p_worldArr);   //Grafika tekstowa przedstawiaj�ca pokoj wraz z stanem otwarcia drzwi.
void areaTextPlayerInfo(Player * p_player, World ** p_p_worldArr); //opis wplywu pokoju na gracza