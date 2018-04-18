#include "Player.h"
#include "ScoreBoard.h"
#include <cstdlib>
#include <iostream>
#include <conio.h>

//inicjujemy playerError od razu jako blad krytyczny - poniewa¿ jest to sta³a "static bool" to tu jest na to ostatnie miejsce.
//przy okazji inicjujemy reszte zmiennych.
Player::Player() : endGame(0), playerLastMove(0), playerTime(0), playerHp(0), playerRounds(0), hardMode(false),
playerError(true)
{
	std::cout << "Blad inicjacji obiektu: nie podano rozmiaru obszaru gry" << std::endl;
}

//konstruktor: dane wejsciowe ustawiay jako const, zeby nic nam przypadkiem ich nie zmienilo!
Player::Player(const int sizeX, const int sizeY) : endGame(0), playerLastMove(9), playerTime(0), playerHp(0),
playerRounds(0), hardMode(false), playerError(false)

{
	//tworzymy zmienne dla generatora w celu wylosowania malych liczb, ktore umieszc¹ start mniej wiecej po przeciwnej stronie swiata.
	const int rndX = (sizeX / 3);
	const int rndY = (sizeY / 3);

	positionArray[0] = (std::rand() % rndX);              //Losujemy pozycje startowa
	positionArray[1] = (std::rand() % rndY);              //Losujemy pozycje startowa
	positionArray[2] = (std::rand() % rndX) + (rndX * 2); //Losujemy pozycje koñcowa
	positionArray[3] = (std::rand() % rndY) + (rndY * 2); //Losujemy pozycje koñcowa
	positionArray[4] = positionArray[0];                  //ustawiamy gracza na pozycji startowej
	positionArray[5] = positionArray[1];                  //ustawiamy gracza na pozycji startowej
	positionArray[6] = sizeX;                             //wpisujemy do tablicy wielkosc swiata
	positionArray[7] = sizeY;                             //wpisujemy do tablicy wielkosc swiata
}

void Player::hpTimeInit()
{
	if (get_hardMode())set_playerHp(40);			//zdrowie gracza
	else set_playerHp(30);

	if (get_hardMode())set_playerTime(150);		    //ilosc rund rozgrywki
	else set_playerTime(30);
}

void Player::move()
{
	auto x = get_actX();
	auto y = get_actY();

	if (get_playerLastMove() == 0) { --x; set_actX(x); }
	else if (get_playerLastMove() == 1) { ++y; set_actY(y); }
	else if (get_playerLastMove() == 2) { ++x; set_actX(x); }
	else if (get_playerLastMove() == 3) { --y; set_actY(y); }
	else if (get_playerLastMove() == 4) set_endGame(3);
	else if (get_playerLastMove() == 5) set_endGame(0);
	else if (get_playerLastMove() == 6) set_endGame(2);
	else set_endGame(0);
}

int Player::gameOver()
{
	system("cls");
	std::cout << "    HP  " << get_playerHp() << "   zakonczone rundy  " << get_playerRounds() << "    Pozostalo czasu  "
		<< get_playerTime() << std::endl << std::endl;
	if (get_endGame() == 1) std::cout << "\nNiestety twoje zdrowie spadlo do zera... umarles :) " << std::endl;
	if (get_endGame() == 2) std::cout << "\nUciekasz wyjsciem bezpieczenstwa przed zakonczeniem zadania." << std::endl;
	if (get_endGame() == 4) std::cout << "\nNiestety koniec czasu - przegrales." << std::endl;
	if (get_endGame() == 3)
	{
		std::cout << "\n\nGRATULACJE udalo ci sie wygrac !!!!" << std::endl;
		if (hardMode)   //tabele wynikow wprowadzamy tylko dla wysokiej trudnosci gry
		{
			ScoreBoard scoreQ;
			scoreQ.showScoreBoard(get_playerHp() / 2 + get_playerTime());
		}
		else
			std::cout << "\nuzyskales " << get_playerHp() / 2 + get_playerTime() << " punktow" << std::endl;
	}
	std::cout << "\nKoniec gry nacisnij Q\nPonowna gra nacisnij E" << std::endl;
	int tst;
	do
	{
		char endChoice = _getch();
		if (endChoice == 'e' || endChoice == 'E')return 0;
		if (endChoice == 'q' || endChoice == 'Q')return 1;
		tst = 1;
	} while (tst == 1);
	return 1;
}

int Player::get_playerLastMove() { return playerLastMove; }
int Player::get_startX() { return positionArray[0]; }
int Player::get_startY() { return positionArray[1]; }
int Player::get_endX() { return positionArray[2]; }
int Player::get_endY() { return positionArray[3]; }
int Player::get_actX() { return positionArray[4]; }
int Player::get_actY() { return positionArray[5]; }
int Player::get_sizeX() { return positionArray[6]; }
int Player::get_sizeY() { return positionArray[7]; }
int Player::get_playerTime() { return playerTime; }
int Player::get_playerHp() { return playerHp; }
int Player::get_playerRounds() { return playerRounds; }
int Player::get_endGame() { return endGame; }
bool Player::get_hardMode() { return hardMode; }

void Player::set_playerLastMove(int x) { playerLastMove = x; }
void Player::set_actY(int x) { positionArray[5] = x; }
void Player::set_actX(int x) { positionArray[4] = x; }
void Player::set_playerTime(int x) { playerTime = x; }
void Player::set_playerHp(int x) { playerHp = x; }
void Player::set_endGame(int  x) { endGame = x; }
void Player::set_hardMode(bool x) { hardMode = x; }

void Player::change_plus_PlayerHp(int x) { playerHp += x; }
void Player::change_minus_PlayerTime(int x) { playerTime -= x; }
void Player::change_addOne_PlayerRounds() { playerRounds++; }

Player::~Player() = default;