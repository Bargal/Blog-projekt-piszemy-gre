/*
#include "ScoreBoard.h"
#include <fstream>
#include <string>
#include <iostream>

ScoreBoard::ScoreBoard() : filestatus(true)
{
	std::ifstream scoreFile("score.dat");
	if (!scoreFile.is_open())
	{
		filestatus = false;
		for (int i = 0; i < 10; i++)
			score[i] = 0;
	}
	else
	{
		for (int i = 0; i < 10; i++)
			scoreFile >> score[i];

		scoreFile.close();

		//sorting table of scores

		for (int i = 0; i < 10; i++)
		{
			for (int j = 9; j >= 1; j--)
			{
				if (score[j] > score[j - 1])
				{
					int swap = score[j - 1];
					score[j - 1] = score[j];
					score[j] = swap;
				}
			}
		}
	}
}

ScoreBoard::~ScoreBoard()
{
	std::ofstream scoreFile("score.dat");
	if (!scoreFile.is_open())
	{
		std::cout << " BLAD ZAPISU PLIKU WYNIKOW !!" << std::endl;
	}
	else
	{
		for (int i = 0; i < 10; i++)
			scoreFile << score[i] << std::endl;
	}
	scoreFile.close();
}

void ScoreBoard::showScoreBoard(const int current)
{
	if (filestatus)
	{
		int position = 1;
		for (int i = 0; i < 10; i++)
		{
			std::cout << "Miejsce " << i + 1 << " - " << score[i] << "  punkty" << std::endl;

			if (score[i] > current) position++;
		}
		std::cout << "\nTwoj wynik " << current << " zapewnia ci " << position << " miejsce" << std::endl;

		if (position <= 10)	score[9] = current;
	}
	else
	{
		std::cout << "wyglada na to, ze grasz pierwszy raz, lub plik z wynikami jest uszkodzony" << std::endl;
		std::cout << "Twoj wynik " << current << " zapewnia ci automatycznie pierwsze miejsce" << std::endl;
		score[0] = current;
	}
}
*/