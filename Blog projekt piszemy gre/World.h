#pragma once
/*
 * Klasa opisuj�ca pojedy�cze pole gry.
 * s�u�y g��wnie jako magazyn danych.
 */

#include<string>

class World
{
	int beInside;          // ilosc odwiedzin w pokoju
	bool exitCell[4]{ true, true, true, true };  //wyjscia z pokoju:  | 0-P�noc | 1-wsch�d | 2-po�udnie  | 3-zach�d || (w-d-s-a) * true = otwarte *
	int eventType;         //rodzaj wydarzenia lub jego brak.
	int hpCell;			   //warto�� o jak� zmienia si� zdrowie gracza na tym polu
	int timeCell;          //warto�� o jak� zmienia si� czas pozosta�y do ko�ca rozgrywki
	std::string infoCell;  //opis tekstowy obszaru

public:
	World();
	~World();

	std::string get_infoCell();
	int get_hpCell();
	int get_timeCell();
	int get_beInside();
	int get_eventType();
	bool get_exitCell(int);

	void set_beInside(int);
	void set_exitCell(int, bool);                                   //ustawiamy stan logiczny (true/false) otwarcia drzwi
	void set_eventType(int);                                        //
	void set_infoCell(int data2 = 0, std::string data1 = "Pokoj");  //ustawiamy domyslne parametry funkcji.
};
