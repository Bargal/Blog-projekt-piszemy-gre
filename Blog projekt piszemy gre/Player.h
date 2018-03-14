#pragma once

#include <cstdlib>

class Player
{
		int positionArray[6]{0}; //Tablica lokacjy gry: 0-startX, 1-startY(wspó³rzêdne startu gry) , 2-endX, 3-endY (wspó³rzêdne koñca gry) , 4 actX, 5 actY (aktualna pozycja gracza)
		int endGame;            // znacznik koñca gry

public:
	Player();
	Player(int, int);
	~Player();
};
