#include <ctime>
#include "World.h"
#include "Player.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); //inicjujemy generator pseudolosowy, poniewaz bedziemy w grze go wykorzystywac. uzywam static_cast, zeby pozbyc sie irytujacych ostrzezen :)

	int endGame = 0;  //jezeli zmienna bedzie rozna od 0 na koncu pentli nastapi zamkniecie gry i wyjscie do systemu.

	do //pomocnicza petla gry (jednoczesnie bedaca cyklem zycia obiektow)
	{
		/*
		 *na razie ustalamy stala wielkosc swiata dla ulatwienia.
		 *ale to tutaj jest miejsce na menu z wyborem wielkosci swiata
		 */
		int worldSizeX = 10; //wielkosc swiata - wspolrzedna X
		int worldSizeY = 10; //wielkosc swiata - wspolrzedna Y

		auto **p_p_worldArr = new World*[worldSizeX];   //tworzymy wskaznik do 1 wymiarowej tablicy i od razu tablice z wskaznikami do tablic zawieraj¹cych obiekty klasy World.
		for (int i = 0; i < worldSizeX; i++)           //petla dzieki ktorej stworzymy:
			p_p_worldArr[i] = new World[worldSizeY];  //w kazdej komorce tablicy tworzymy wskaznik do nowej tablicy i od razu nowa tablice obiektow klasy World.

		auto p_player = new Player(worldSizeX, worldSizeY);               //Inicjujemy obiekt przechowujacy dane gracza i od razu przekazujemy do niego rozmiar swiata
		if (!p_player->playerError)  return 1;                           //jesli nie udalo sie poprawnie zainicjowac obiektu wychodzimy z gry, zwracajac kod bledu.
																		//pamietajmy - p_player to wskaznik do obiektu, wiec metody i zmienne wywolujemy nie przez '.' tylko '->'
		/*
		 *
		 *
		 *tu bedzie program ;)
		 *
		 *
		 */

		 //kasujemy obiekt przechowujacy dane gracza
		delete p_player;

		//kasujemy wszystkie dane swiata, robimy to odwrotnie ni¿ podczas inicjalizacji:
		for (int i = 0; i < worldSizeX; i++)
			delete[] p_p_worldArr[i];  //najpierw wskazniki do tablic
		delete[] p_p_worldArr;        //a nastêpnie wskaznik do tablicy wskaznikow
	} while (endGame == 0);  //warunek koncowy pomocniczej petli gry

	return 0;
}