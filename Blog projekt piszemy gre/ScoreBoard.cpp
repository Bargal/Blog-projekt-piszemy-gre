#include "ScoreBoard.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

ScoreBoard::ScoreBoard() : filestatus(true) {
  std::ifstream scoreFile("score.dat");

  if (!scoreFile.is_open()) {
    filestatus = false;

    for (auto &i : score)
      i = 0;
  } else {
    for (auto &i : score)
      scoreFile >> i;

    std::sort(score, score + 10, std::greater<>());
  }
}

ScoreBoard::~ScoreBoard() {
  std::ofstream scoreFile("score.dat");
  if (!scoreFile.is_open()) {
    std::cout << " BLAD ZAPISU PLIKU WYNIKOW !!" << std::endl;
  } else {
    for (auto &i : score)
      scoreFile << i << std::endl;
  }
}

void ScoreBoard::showScoreBoard(const int current) {
  if (filestatus) {
    int position = 1;
    for (int i = 0; i < 10; i++) {
      std::cout << "Miejsce " << i + 1 << " - " << score[i] << "  punkty"
                << std::endl;

      if (score[i] > current)
        position++;
    }
    std::cout << "\nTwoj wynik " << current << " zapewnia ci " << position
              << " miejsce" << std::endl;

    if (position <= 10)
      score[9] = current;
  } else {
    std::cout << "Twoj wynik " << current << " zapewnia ci pierwsze miejsce"
              << std::endl;
    score[0] = current;
  }
}
