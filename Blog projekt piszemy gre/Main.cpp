#include "World.h"
#include "Player.h"



main()
{
	int worldSize = 10; //tutaj mamy wymiary naszego swiata.
	
	auto **p_p_arr = new World*[worldSize];   //tworzymy wskaŸnik do 1 wymiarowej tablicy i tablicê.
	for (int i = 0; i < worldSize; i++)       //pêtla dziêki której stworzymy:
		p_p_arr[i] = new World[worldSize];    //w ka¿dej komórce wskaŸnik do nowej tablicy i now¹ tablicê.
}