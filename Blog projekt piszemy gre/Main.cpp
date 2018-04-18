#include <ctime>
#include <windows.h>
#include "World.h"
#include "Player.h"
#include "game.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); //inicjujemy generator pseudolosowy - static_cast dla zlikwidowania warningu (generalnie zbêdny)

	//modu³ opcjonalny
	HWND console = GetConsoleWindow();                  //zmiana wielkosci okna konsoli   copy-paste - wazne, ze dziala, nie wazne jak ;)  (windows.h lib);)
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 900, 600, TRUE); // tu ustawiamy wysokosc i szerokosc okna konsoli ... koniec copy-paste.

	int endGame;  // 0 - kontynuacja gry

	do //pomocnicza petla gry (jednoczesnie cykl zycia obiektow)
	{
		//TODO: tu mo¿na umiescic zmiane wielkosci obszaru gry.

		const int worldSizeX = 10; 
		const int worldSizeY = 10; 

							 //G³ówna tablica œwiata gry
		auto p_p_worldArr = new World*[worldSizeX];
		for (int i = 0; i < worldSizeX; i++)
			p_p_worldArr[i] = new World[worldSizeY];

		auto p_player = new Player(worldSizeX, worldSizeY);  //Inicjujemy obiekt przechowujacy dane gracza i od razu przekazujemy do niego rozmiar swiata
		if (p_player->playerError)  return 1;                //jesli nie udalo sie poprawnie zainicjowac obiektu wychodzimy z gry, zwracajac kod bledu.
															 //pamietajmy - p_player to wskaznik do obiektu, wiec metody i zmienne wywolujemy nie przez '.' tylko '->'

		endGame = startGame(p_player, p_p_worldArr);         //tu bêdzie toczyæ siê ca³a gra
		//prototyp funkcji w pliku game.h

		//czyszczenie pamieci: gdyby gra nie miala opcji ponownej rozgrywki mozna by bylo pominac
		//bo po skonczeniu programu i tak pamiec jest uwalniana, ale gracz moze wybrac ponowna gre.

		//kasujemy obiekt przechowujacy dane gracza
		delete p_player;

		//kasujemy wszystkie dane swiata, robimy to odwrotnie ni¿ podczas inicjalizacji:
		for (int i = 0; i < worldSizeX; i++)
			delete[] p_p_worldArr[i];  //najpierw wskazniki do tablic
		delete[] p_p_worldArr;         //a nastêpnie wskaznik do tablicy wskaznikow
	} while (endGame == 0);            //warunek koncowy pomocniczej petli gry

	return 0;
}