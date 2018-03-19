#include "Player.h"
#include <cstdlib>
#include <iostream>

//inicjujemy playerError od razu jako blad krytyczny - poniewa¿ jest to sta³a "static bool" to tu jest na to ostatnie miejsce.
//przy okazji inicjujemy reszte zmiennych.
Player::Player() : endGame(0), playerMove(0), playerTime(0), playerHp(0), playerRounds(0), hardMode(false),
                   playerError(true)
{
	std::cout << "Blad inicjacji obiektu: nie podano rozmiaru obszaru gry" << std::endl;
}

//konstruktor: dane wejsciowe ustawiay jako const, zeby nic nam przypadkiem ich nie zmienilo!
Player::Player(const int sizeX, const int sizeY) : endGame(0), playerMove(0), playerTime(0), playerHp(0),
                                                   playerRounds(0), hardMode(false), playerError(false)

{
	//tworzymy zmienne dla generatora w celu wylosowania malych liczb, ktore umieszc¹ start mniej wiecej po przeciwnej stronie swiata.
	const int rndX = (sizeX / 3);
	const int rndY = (sizeY / 3);

	positionArray[0] = (std::rand() % rndX); //Losujemy pozycje startowa
	positionArray[1] = (std::rand() % rndY); //Losujemy pozycje startowa
	positionArray[2] = (std::rand() % rndX) + (rndX * 2); //Losujemy pozycje koñcowa
	positionArray[3] = (std::rand() % rndY) + (rndY * 2); //Losujemy pozycje koñcowa
	positionArray[4] = positionArray[0]; //ustawiamy gracza na pozycji startowej
	positionArray[5] = positionArray[1]; //ustawiamy gracza na pozycji startowej
}

void Player::hpTimeInit()
{
	if (get_hardMode())set_playerHp(40);			//zdrowie gracza
	else set_playerHp(30);

	if (get_hardMode())set_playerTime(150);		    //ilosc rund rozgrywki
	else set_playerTime(30);
}

int Player::get_playerMove() { return playerMove; }
int Player::get_startX() { return positionArray[0]; }
int Player::get_startY() { return positionArray[1]; }
int Player::get_endX() { return positionArray[2]; }
int Player::get_endY() { return positionArray[3]; }
int Player::get_actX() { return positionArray[4]; }
int Player::get_actY() { return positionArray[5]; }
int Player::get_playerTime() { return playerTime; }
int Player::get_playerHp() { return playerHp; }
int Player::get_playerRounds() { return playerRounds; }
int Player::get_endGame() { return endGame; }
bool Player::get_hardMode() { return hardMode; }

void Player::set_playerMove(int x) { playerMove = x; }
void Player::set_actY(int x) { positionArray[5] = x; }
void Player::set_actX(int x) { positionArray[4] = x; }
void Player::set_playerTime(int x) { playerTime = x; }
void Player::set_playerHp(int x) { playerHp = x; }
void Player::set_playerRounds(int x) { playerRounds = x; }
void Player::set_endGame(int  x) { endGame = x; }
void Player::set_hardMode(bool x) { hardMode = x; }

Player::~Player() = default;