#pragma once

#include <cstdlib>

class Player
{
		int positionArray[6]{0}; //Tablica lokacjy gry: 0-startX, 1-startY(wsp�rz�dne startu gry) , 2-endX, 3-endY (wsp�rz�dne ko�ca gry) , 4 actX, 5 actY (aktualna pozycja gracza)
		int endGame;            // znacznik ko�ca gry

public:
	Player();
	Player(int, int);
	~Player();
};
