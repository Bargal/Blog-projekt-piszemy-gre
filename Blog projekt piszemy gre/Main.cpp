



#include <ctime>
#include "World.h"
#include "Player.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); //inicjujemy generator pseudolosowy, poniewa¿ bêdziemy w grze go wykorzystywaæ. u¿ywam static_cast, ¿eby pozbyæ siê irytuj¹cych ostrzê¿eñ :) 

	int endGame = 0;  //je¿eli zmienna bêdzie ró¿na od 0 na koñcu pentli nast¹pi zamkniêcie gry i wyjœcie do systemu.

	do //pomocnicza pêtla gry (jednoczeœnie bêd¹ca cyklem ¿ycia obiektów)
	{
		int worldSizeX = 10; //wielkosc swiata - wspolrzedna X
		int worldSizeY = 10; //wielkosc swiata - wspolrzedna Y

		auto **p_p_worldArr = new World*[worldSizeX];   //tworzymy wskaŸnik do 1 wymiarowej tablicy i od razu tablicê z wska¿nikami do tablic zawieraj¹cych obiekty klasy World.
		for (int i = 0; i < worldSizeX; i++)           //pêtla dziêki której stworzymy:
			p_p_worldArr[i] = new World[worldSizeY];  //w ka¿dej komórce tablicy tworzymy wskaŸnik do nowej tablicy i od razu now¹ tablicê obiektów klasy World.

		auto p_player = new Player(worldSizeX, worldSizeY);               //Inicjujemy obiekt przechowuj¹cy dane gracza i od razu przekazujemy do niego rozmiar œwiata

		/*
		 *
		 *
		 *tu bêdzie program ;)
		 *
		 *
		 */

		 //kasujemy obiekt przechowuj¹cy dane gracza
		delete p_player;

		//kasujemy wszystkie dane œwiata, robimy to odwrotnie ni¿ podczas inicjalizacji:
		for (int i = 0; i < worldSizeX; i++)
			delete[] p_p_worldArr[i];  //najpierw wska¿niki do tablic
		delete[] p_p_worldArr;        //a nastêpnie wska¿nik do tablicy wska¿ników

	} while (endGame == 0);  //warunek koñcowy pomocniczej pêtli gry

	return 0;
}