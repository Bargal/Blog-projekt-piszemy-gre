#include "Player.h"

Player::Player(): endGame(0)
{
}

Player::Player(int sizeX, int sizeY): endGame(0)
{
	//tworzymy zmienne dla generatora w celu wylosowania ma³ych liczb, które umieszc¹ start mniej wiêcej po przeciwnej stronie œwiata.
	const int rndX = (sizeX / 3);
	const int rndY = (sizeY / 3);
	 
	positionArray[0] = (std::rand() % rndX);              //Losujemy pozycjê startow¹
	positionArray[1] = (std::rand() % rndY);              //Losujemy pozycjê startow¹
	positionArray[2] = (std::rand() % rndX) + (rndX * 2); //Losujemy pozycjê koñcow¹
	positionArray[3] = (std::rand() % rndY) + (rndY * 2); //Losujemy pozycjê koñcow¹
	positionArray[4] = positionArray[0];                  //ustawiamy gracza na pozycji startowej
	positionArray[5] = positionArray[1];                  //ustawiamy gracza na pozycji startowej
}

Player::~Player()
{
}
