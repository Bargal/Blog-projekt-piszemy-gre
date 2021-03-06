#include "World.h"

World::World() : beInside(0), exitCell{ true, true, true, true }, eventType(0), hpCell(0), timeCell(0)
{
	hpCell = (rand() % 5) - 2;        //losowe wyznaczanie wp�ywu lokacji na zdrowie gracza
	timeCell = (rand() % 4) + hpCell; // Losowe wyznaczanie czasu rundy na lokacji (zale�no�� z wp�ywem na zdrowie)
}

World::~World() = default;

std::string World::get_infoCell() { return infoCell; }
int World::get_hpCell() { return hpCell; }
int World::get_timeCell() { return timeCell; }
int World::get_beInside() { return beInside; }
int World::get_eventType() { return eventType; }
bool World::get_exitCell(int arr1) { return exitCell[arr1]; }

void World::set_beInside(int beInside) { this -> beInside = beInside; } 
void World::set_exitCell(int arr1, bool data1) { exitCell[arr1] = data1; }
void World::set_eventType(int eventType) { this -> eventType = eventType; }

void World::set_infoCell(int data2, std::string infoCell)  //ustawiamy warto�ci domy�lne zmiennych
{
	this -> infoCell = infoCell;                       //pocz�tek opisu lokacji
	infoCell += ' ';                        //wstawienie spacji po pierwszym czlonie opisu
	if (data2 > 0)                          //je�li numer jest wi�kszy od zera
	{
		infoCell += "numer: ";              //dopisujemy informacje o numerowaniu
		infoCell += std::to_string(data2);  //dopisanie do nazwy otrzymanego numeru pokoju (bardzo wygodna konwersja int na string)
	}
	else
		infoCell += "bez numeru";           //je�eli numer pokoju bedzie rowny lub mniejszy od zera.
}
