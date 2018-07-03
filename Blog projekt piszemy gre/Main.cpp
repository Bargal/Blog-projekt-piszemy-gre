#include "Player.h"
#include "Windows.h"
#include "World.h"
#include "game.h"
#include <conio.h>
#include <iostream>

int hello();
void worldSize(int &, int &);

int main() {
  // zmiana wielkosci okna konsoli
  HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r);
  MoveWindow(console, r.left, r.top, 900, 800, TRUE);

  int endGame; // 0 - kontynuacja gry

  int worldSizeX = 10;
  int worldSizeY = 10;

  int otherSize = hello();
  if (otherSize == 1)
    worldSize(worldSizeX, worldSizeY);

  do {
    auto p_p_worldArr = new World *[worldSizeX];
    for (int i = 0; i < worldSizeX; i++)
      p_p_worldArr[i] = new World[worldSizeY];

    Player player(worldSizeX, worldSizeY); // dane gracza

    endGame = startGame(&player, p_p_worldArr); // game.h

    for (int i = 0; i < worldSizeX; i++)
      delete[] p_p_worldArr[i];
    delete[] p_p_worldArr;
  } while (endGame == 0);

  return 0;
}

int hello() {
  std::cout
      << std::endl
      << "	Witaj w grze Qube!" << std::endl
      << " jest to projekt pisany na potrzeby bloga devhobby.eu." << std::endl
      << " powastal przede wszystkim aby na jego przykladzie" << std::endl
      << " poznawac tajniki jezyka C++ i doskonalic umiejetnosci." << std::endl
      << " rozwoj kodu mozesz zobaczyc na stronie: " << std::endl
      << " https://github.com/Mighn/Blog-projekt-piszemy-gre/commits/master"
      << std::endl
      << std::endl
      << " Stanardowa wielkosc planszy to 10x10 czy chcesz zmienic wielkosc ?"
      << std::endl
      << "   Tak/Nie: ";
  char size = _getch();
  if ((size == 'T') || (size == 't'))
    return 1;
  else
    return 0;
}

void worldSize(int &x, int &y) {
  std::cout
      << "minimalna wielkosc planszy to 5x5 maksymalna to 100 x 100"
      << std::endl
      << "Nie zalecam ustawiania dowolnego wymiaru poni¿ej 10 i powy¿ej 50"
      << std::endl
      << "gra bedzie dzialac, ale nie byla balansowana dla innych wielkosci"
      << std::endl
      << "i mo¿e okazaæ siê bardzo trudna lub banalnie prosta" << std::endl
      << "podaj dlugoisc obszaru gry: wartoœci 5-100" << std::endl;
  do
    std::cin >> x;
  while (!((x > 4) && (x < 101)));

  std::cout << std::endl
            << "podaj szerokosc obszaru gry: wartoœci 5-100" << std::endl;
  do
    std::cin >> y;
  while (!((y > 4) && (y < 101)));
}
