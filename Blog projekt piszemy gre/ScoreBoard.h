#pragma once

/*
* Tworzenie tabeli wygranych i zapis do pliku
*/
class ScoreBoard
{
	int score[10]{}; //Tabela najwyzszych 10 wynikow
	bool filestatus; //status odczytu pliku

public:
	ScoreBoard();
	~ScoreBoard();
	//pokazywanie i obsluga wyswietlania i dodawania wyniku do listy.
	void showScoreBoard(int);
};
