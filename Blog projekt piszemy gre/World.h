#pragma once
/* Klasa opisuj¹ca pojedyñcze pole gry.
 * s³u¿y g³ównie jako magazyn danych.
 */

#include<string>

class World
{
	int beInside;               // ilosc odwiedzin w pokoju
	bool exitCell[4]{ true };  //wyjscia z pokoju:  | 0-Pó³noc | 1-wschód | 2-po³udnie  | 3-zachód || (w-d-s-a) * true = otwarte *
	int eventType;            //rodzaj wydarzenia lub jego brak.
	int hpCell;				 //wartoœæ o jak¹ zmienia siê zdrowie gracza na tym polu
	int timeCell;           //wartoœæ o jak¹ zmienia siê czas pozosta³y do koñca rozgrywki
	std::string infoCell;  //opis tekstowy obszaru

public:
	World();    //konstruktor
	~World();  //destruktor

	//gettery - czyli metody pobieraj¹ce prywatne dane z obiektu

	std::string get_infoCell();
	int get_hpCell();
	int get_timeCell();
	int get_beInside();
	int get_eventType();
	bool get_exitCell(int);

	//settery - czyli metody zmieniaj¹ce prywatne dane w obiekcie

	void set_beInside(int);
	void set_exitCell(int, bool);
	void set_eventType(int);
	void set_infoCell(std::string, int);
};
