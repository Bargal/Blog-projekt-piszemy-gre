#include <ctime>
#include <windows.h> //****** - tylko dla bloku zmiany wielkosci konsoli (copy-paste).
#include "World.h"
#include "Player.h"
#include "game.h"
#include <iostream>
//#include <conio.h>     //dzieki tej bibliotece mozemy uzyc komendy _getch()

int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); //inicjujemy generator pseudolosowy, poniewaz bedziemy w grze go wykorzystywac. uzywam static_cast, zeby pozbyc sie irytujacych ostrzezen :)

	// ********* moze nie dzioalac poprawnie na innych IDE niz Visual Studio!***********
	HWND console = GetConsoleWindow();                  //zmiana wielkosci okna konsoli   copy-paste - wazne, ze dziala, nie wazne jak ;)  (windows.h lib);)
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 900, 600, TRUE); // tu ustawiamy wysokosc i szerokosc okna konsoli ... koniec copy-paste.

	int endGame;  //jezeli zmienna bedzie rozna od 0 na koncu pentli nastapi zamkniecie gry i wyjscie do systemu.

	do //pomocnicza petla gry (jednoczesnie bedaca cyklem zycia obiektow)
	{
		/*
		 *na razie ustalamy stala wielkosc swiata dla ulatwienia.
		 *ale to tutaj jest miejsce na menu z wyborem wielkosci swiata
		 */

		int worldSizeX = 10; //wielkosc swiata - wspolrzedna X
		int worldSizeY = 10; //wielkosc swiata - wspolrzedna Y

		auto p_p_worldArr = new World*[worldSizeX];   //tworzymy wskaznik do 1 wymiarowej tablicy i od razu tablice z wskaznikami do tablic zawieraj¹cych obiekty klasy World.
		for (int i = 0; i < worldSizeX; i++)           //petla dzieki ktorej stworzymy:
			p_p_worldArr[i] = new World[worldSizeY];  //w kazdej komorce tablicy tworzymy wskaznik do nowej tablicy i od razu nowa tablice obiektow klasy World.

		auto p_player = new Player(worldSizeX, worldSizeY);              //Inicjujemy obiekt przechowujacy dane gracza i od razu przekazujemy do niego rozmiar swiata
		if (p_player->playerError)  return 1;                           //jesli nie udalo sie poprawnie zainicjowac obiektu wychodzimy z gry, zwracajac kod bledu.
																	   //pamietajmy - p_player to wskaznik do obiektu, wiec metody i zmienne wywolujemy nie przez '.' tylko '->'

		endGame = startGame(p_player, p_p_worldArr);                  //tu bêdzie toczyæ siê ca³a nasza gra, przechodzimy do plikow game.h i game.cpp   ** i jak wskazuje logika - koniec gry jest spowodowany jej rozpoczêciem ;) *
		//prototyp funkcji w pliku game.h

		 //kasujemy obiekt przechowujacy dane gracza
		delete p_player;

		//kasujemy wszystkie dane swiata, robimy to odwrotnie ni¿ podczas inicjalizacji:
		for (int i = 0; i < worldSizeX; i++)
			delete[] p_p_worldArr[i];  //najpierw wskazniki do tablic
		delete[] p_p_worldArr;        //a nastêpnie wskaznik do tablicy wskaznikow
	} while (endGame == 0);  //warunek koncowy pomocniczej petli gry

	return 0;
}