



#include <ctime>
#include "World.h"
#include "Player.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); //inicjujemy generator pseudolosowy, poniewa� b�dziemy w grze go wykorzystywa�. u�ywam static_cast, �eby pozby� si� irytuj�cych ostrz�e� :) 

	int endGame = 0;  //je�eli zmienna b�dzie r�na od 0 na ko�cu pentli nast�pi zamkni�cie gry i wyj�cie do systemu.

	do //pomocnicza p�tla gry (jednocze�nie b�d�ca cyklem �ycia obiekt�w)
	{
		int worldSizeX = 10; //wielkosc swiata - wspolrzedna X
		int worldSizeY = 10; //wielkosc swiata - wspolrzedna Y

		auto **p_p_worldArr = new World*[worldSizeX];   //tworzymy wska�nik do 1 wymiarowej tablicy i od razu tablic� z wska�nikami do tablic zawieraj�cych obiekty klasy World.
		for (int i = 0; i < worldSizeX; i++)           //p�tla dzi�ki kt�rej stworzymy:
			p_p_worldArr[i] = new World[worldSizeY];  //w ka�dej kom�rce tablicy tworzymy wska�nik do nowej tablicy i od razu now� tablic� obiekt�w klasy World.

		auto p_player = new Player(worldSizeX, worldSizeY);               //Inicjujemy obiekt przechowuj�cy dane gracza i od razu przekazujemy do niego rozmiar �wiata

		/*
		 *
		 *
		 *tu b�dzie program ;)
		 *
		 *
		 */

		 //kasujemy obiekt przechowuj�cy dane gracza
		delete p_player;

		//kasujemy wszystkie dane �wiata, robimy to odwrotnie ni� podczas inicjalizacji:
		for (int i = 0; i < worldSizeX; i++)
			delete[] p_p_worldArr[i];  //najpierw wska�niki do tablic
		delete[] p_p_worldArr;        //a nast�pnie wska�nik do tablicy wska�nik�w

	} while (endGame == 0);  //warunek ko�cowy pomocniczej p�tli gry

	return 0;
}