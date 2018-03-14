#include "Player.h"

Player::Player(): endGame(0)
{
}

Player::Player(int sizeX, int sizeY): endGame(0)
{
	//tworzymy zmienne dla generatora w celu wylosowania ma�ych liczb, kt�re umieszc� start mniej wi�cej po przeciwnej stronie �wiata.
	const int rndX = (sizeX / 3);
	const int rndY = (sizeY / 3);
	 
	positionArray[0] = (std::rand() % rndX);              //Losujemy pozycj� startow�
	positionArray[1] = (std::rand() % rndY);              //Losujemy pozycj� startow�
	positionArray[2] = (std::rand() % rndX) + (rndX * 2); //Losujemy pozycj� ko�cow�
	positionArray[3] = (std::rand() % rndY) + (rndY * 2); //Losujemy pozycj� ko�cow�
	positionArray[4] = positionArray[0];                  //ustawiamy gracza na pozycji startowej
	positionArray[5] = positionArray[1];                  //ustawiamy gracza na pozycji startowej
}

Player::~Player()
{
}
