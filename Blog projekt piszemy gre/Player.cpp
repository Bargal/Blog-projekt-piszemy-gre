#include "Player.h"
#include "ScoreBoard.h"
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <random>

Player::Player(const int sizeX, const int sizeY)
    : endGame(0), playerLastMove(9), playerTime(0), playerHp(0),
      playerRounds(0), hardMode(false)

{
  std::default_random_engine generator;
  unsigned seed =
      std::chrono::steady_clock::now().time_since_epoch().count(); // ziarno
  generator.seed(seed); // inicjujemy silnik ziarnem

  const int rndX = (sizeX / 3);
  const int rndY = (sizeY / 3);
  std::uniform_int_distribution<> distX(0, rndX);
  std::uniform_int_distribution<> distY(0, rndY);
  std::uniform_int_distribution<> distEndX(rndX * 2, (rndX + rndX * 2));
  std::uniform_int_distribution<> distEndY(rndY * 2, (rndY + rndY * 2));

  positionArray[0] = distX(generator);    // Losujemy pozycje startowa
  positionArray[1] = distY(generator);    // Losujemy pozycje startowa
  positionArray[2] = distEndX(generator); // Losujemy pozycje koñcowa
  positionArray[3] = distEndY(generator); // Losujemy pozycje koñcowa
  positionArray[4] = positionArray[0];    // ustawiamy gracza na start
  positionArray[5] = positionArray[1];    // ustawiamy gracza na start
  positionArray[6] = sizeX;               // wpisujemy  wielkosc swiata
  positionArray[7] = sizeY;               // wpisujemy  wielkosc swiata
}

void Player::hpTimeInit() {
  if (get_hardMode())
    set_playerHp(40); // zdrowie gracza
  else
    set_playerHp(30);

  if (get_hardMode())
    set_playerTime(150 + (positionArray[6] * positionArray[7]) / 100);
  else
    set_playerTime(30 + (positionArray[6] * positionArray[7]) / 150);
}

void Player::move() {
  auto x = get_actX();
  auto y = get_actY();

  switch (get_playerLastMove()) {
  case 0: {
    --x;
    set_actX(x);
  } break;

  case 1: {
    ++y;
    set_actY(y);
  } break;

  case 2: {
    ++x;
    set_actX(x);
  } break;

  case 3: {
    --y;
    set_actY(y);
  } break;

  case 4:
    set_endGame(3);
    break;

  case 5:
    set_endGame(0);
    break;

  case 6:
    set_endGame(2);
    break;

  default:
    set_endGame(0);
  }
}

int Player::gameOver() {
  system("cls");
  std::cout << "    HP  " << get_playerHp() << "   zakonczone rundy  "
            << get_playerRounds() << "    Pozostalo czasu  " << get_playerTime()
            << std::endl
            << std::endl;

  switch (get_endGame()) {
  case 1:
    std::cout << "\nNiestety twoje zdrowie spadlo do zera... umarles :) "
              << std::endl;
    break;
  case 2:
    std::cout
        << "\nUciekasz wyjsciem bezpieczenstwa przed zakonczeniem zadania."
        << std::endl;
    break;
  case 4:
    std::cout << "\nNiestety koniec czasu - przegrales." << std::endl;
    break;
  case 3: {
    std::cout << "\n\nGRATULACJE udalo ci sie wygrac !!!!" << std::endl;
    if (hardMode) // tabele wynikow wprowadzamy tylko dla wysokiej trudnosci gry
    {
      ScoreBoard scoreQ;
      scoreQ.showScoreBoard(get_playerHp() / 2 + get_playerTime());
    } else
      std::cout << "\nuzyskales " << get_playerHp() / 2 + get_playerTime()
                << " punktow" << std::endl;
  } break;
  default:
    std::cout << "\nNie wiem co sie stalo, nie moge stwierdzic czy wygrales..."
              << std::endl;
    ;
  }

  std::cout << "\nKoniec gry nacisnij Q\nPonowna gra nacisnij E" << std::endl;
  int tst;
  do {
    char endChoice = _getch();
    if (endChoice == 'e' || endChoice == 'E')
      return 0;
    if (endChoice == 'q' || endChoice == 'Q')
      return 1;
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

void Player::set_playerLastMove(int playerLastMove) {this->playerLastMove = playerLastMove;}
void Player::set_actY(int y) { positionArray[5] = y; }
void Player::set_actX(int x) { positionArray[4] = x; }
void Player::set_playerTime(int playerTime) { this->playerTime = playerTime; }
void Player::set_playerHp(int playerHp) { this->playerHp = playerHp; }
void Player::set_endGame(int endGame) { this->endGame = endGame; }
void Player::set_hardMode(bool hardMode) { this->hardMode = hardMode; }

void Player::change_plus_PlayerHp(int playerHp) { this->playerHp += playerHp; }
void Player::change_minus_PlayerTime(int playerTime) {this->playerTime -= playerTime;}
void Player::change_addOne_PlayerRounds() { playerRounds++; }

Player::~Player() = default;
