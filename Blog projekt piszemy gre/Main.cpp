#include "World.h"
#include "Player.h"



main()
{
	int worldSize = 10; //tutaj mamy wymiary naszego swiata.
	
	auto **p_p_arr = new World*[worldSize];   //tworzymy wska�nik do 1 wymiarowej tablicy i tablic�.
	for (int i = 0; i < worldSize; i++)       //p�tla dzi�ki kt�rej stworzymy:
		p_p_arr[i] = new World[worldSize];    //w ka�dej kom�rce wska�nik do nowej tablicy i now� tablic�.
}