#pragma once
/* Klasa opisuj�ca pojedy�cze pole gry.
 * s�u�y g��wnie jako magazyn danych.
 */

#include<string>

class World
{
	int beInside;               // ilosc odwiedzin w pokoju
	bool exitCell[4]{ true };  //wyjscia z pokoju:  | 0-P�noc | 1-wsch�d | 2-po�udnie  | 3-zach�d || (w-d-s-a) * true = otwarte *
	int eventType;            //rodzaj wydarzenia lub jego brak.
	int hpCell;				 //warto�� o jak� zmienia si� zdrowie gracza na tym polu
	int timeCell;           //warto�� o jak� zmienia si� czas pozosta�y do ko�ca rozgrywki
	std::string infoCell;  //opis tekstowy obszaru

public:
	World();    //konstruktor
	~World();  //destruktor

	//gettery - czyli metody pobieraj�ce prywatne dane z obiektu

	std::string get_infoCell();
	int get_hpCell();
	int get_timeCell();
	int get_beInside();
	int get_eventType();
	bool get_exitCell(int);

	//settery - czyli metody zmieniaj�ce prywatne dane w obiekcie

	void set_beInside(int);
	void set_exitCell(int, bool);
	void set_eventType(int);
	void set_infoCell(std::string, int);
};
