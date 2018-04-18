#include "ScoreBoard.h"
#include <fstream>
#include <string>
#include <iostream>

ScoreBoard::ScoreBoard() : filestatus(true)
{
	std::ifstream scoreFile("score.dat");  //otwieranie pliku z wynikami do odczytu
	if (!scoreFile.is_open())              //sprawdzanie czy plik jest poprawnie otwarty
	{
		filestatus = false;

		for (auto& i : score)         //zapis wyliczaj�cy kolejne kom�rki trablicy (uniemo�liwia wyj�cie poza zakres)
			i = 0;                   //poniewa� brak danych z pliku tworzymy tablic� i zapisujemy zerami
	}
	else
	{
		for (auto& i : score)
			scoreFile >> i;        //odczytyjemy wyniki z pliku i zapisujemy do tablicy wynik�w

		scoreFile.close();         //zamykanie dost�pu do pliku

		//Sortowanie tabeli wynikow (bubble sorting)

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
	std::ofstream scoreFile("score.dat"); //otwieranie(lub tworzenie) pliku z wynikami do zapisu
	if (!scoreFile.is_open())             //sprawdzenie poprawno�ci otwarcia pliku
	{
		std::cout << " BLAD ZAPISU PLIKU WYNIKOW !!" << std::endl;
	}
	else
	{
		for (int i : score)             //zapis tabeli wynik�w do pliku
			scoreFile << i << std::endl;
	}
	scoreFile.close();                 //zamykanie dost�pu do pliku
}

void ScoreBoard::showScoreBoard(const int current)  //interfejs i dodawanie wynik�w do tablicy
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

		if (position <= 10)	score[9] = current;  //zapisujemy obecny ynik na ostatnim miejscu, czyli na miejscu wyniku, kt�ry "wypada z listy". Sortowanie nast�pi przy nast�pnym odczycie.
	}
	else
	{
		std::cout << "wyglada na to, ze grasz pierwszy raz, lub plik z wynikami jest uszkodzony" << std::endl;
		std::cout << "Twoj wynik " << current << " zapewnia ci automatycznie pierwsze miejsce" << std::endl;
		score[0] = current;
	}
}