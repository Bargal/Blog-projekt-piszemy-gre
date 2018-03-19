#include "World.h"

World::World() : beInside(0), eventType(0), hpCell(0), timeCell(0)
{
	hpCell = (rand() % 5) - 2; //losowe wyznaczanie wp³ywu lokacji na zdrowie gracza
	timeCell = (rand() % 4) + hpCell; // Losowe wyznaczanie czasu rundy na lokacji, jednak im bezpieczniej, tym wiêcej czasu mija (zale¿noœæ z wp³ywem na zdrowie)
}

World::~World() = default;

std::string World::get_infoCell() { return std::string(); }
int World::get_hpCell() { return hpCell; }
int World::get_timeCell() { return timeCell; }
int World::get_beInside() { return beInside; }
int World::get_eventType() { return eventType; }
bool World::get_exitCell(int arr1) { return exitCell[arr1]; }

void World::set_beInside(int data1) { beInside = data1; } //mo¿na te¿ napisaæ: ...set_beInside(int beInside) { this -> beInside = beInside; }
void World::set_exitCell(int arr1, bool data1) { exitCell[arr1] = data1; }
void World::set_eventType(int data1) { eventType = data1; }

void World::set_infoCell(std::string data1 = "Pomieszczenie", int data2 = 0)  //ustawiamy wartoœci domyœlne zmiennych
{
	infoCell = data1;                          //pocz¹tek opisu lokacji
	infoCell += ' ';                          //wstawienie spacji po pierwszym czlonie opisu
	if (data2 > 0)                           //jeœli numer jest wiêkszy od zera
	{
		infoCell += "numer: ";              //dopisujemy informacje o numerowaniu
		infoCell += std::to_string(data2); //dopisanie do nazwy otrzymanego numeru pokoju (bardzo wygodna konwersja int na string)
	}
	else
		infoCell += "bez numeru";
}