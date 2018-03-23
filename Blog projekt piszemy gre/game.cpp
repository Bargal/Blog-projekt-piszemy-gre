#include "World.h"
#include "Player.h"
#include "game.h"
#include <iostream>
#include <conio.h>     //dzieki temu mozemy uzyc komendy _getch()

int startGame(Player *p_player, World **p_p_worldArr)
{
	system("cls");                                            //tu moga sie pojawic pierwsze klopoty na niektorych IDE.
	std::cout << "Witam w qube txt" << std::endl;
	std::cout << "\nzaraz wejdziesz do losowego boxu " << std::endl;
	std::cout << "twoim zadaniem bedzie wydostanie sie na zewnatrz" << std::endl;
	std::cout << "w tym celu uzyj klawiszy WSAD :" << std::endl;
	std::cout << "\n W - polnoc\n E - poludnie\n A - zachod\n D - wschod" << std::endl;
	std::cout << "lub klawiszami strza³ek" << std::endl;
	std::cout << "spokojnie - nie musisz tego zapamietac - bedzie to podawane podczas gry :)" << std::endl;
	std::cout << "\nNa poczatek masz 10 punktow zycia.\nCzesc pokojow zadaje obrazena a odpoczynek w czesci pokojow leczy rany"<< std::endl;
	std::cout << "odpoczywasz uzywajac klawisza Q" << std::endl;
	std::cout << "masz okreslona ilosc jednostek czasu a kazdy pokoj zabiera pewna ilosc czasu na ture" << std::endl;
	std::cout << "\nzycze milej zabawy, nacisnij dowolny klawisz aby zaczac." << std::endl;
	std::cout << "koncowy wynik zalezy od czasu przejscia i pozostalgo zdrowia" << std::endl;
	std::cout << "\n\nwybierz trudnosc gry: 1 - latwa 2- trudna - uwaga, gra moze byc sporadycznie nie mozliwa do ukonczenia " << std::endl;
              	//ale bedzie zawsze mozliwa jak dodamy eventy i klucze, i wtedy zmienimy opis
		

	int tmp;
	do
	{
		tmp = 0;
		char tempMode = _getch();                                 //wczytujemy z klawiatury znak i przypisujemy do zmiennej. _getch() zwraca nam pojedynczy znak wczytany z klawiatury.
		if (tempMode == '1') p_player->set_hardMode(false);      //ustawiamy trudnosc gry w obiekcie p_player
		else if (tempMode == '2')p_player->set_hardMode(true);  // 
		else tmp = 1;                                          // a jesli podano inna wartosc niz 1 albo 2...
	} while (tmp == 1);                                       //wracamy na poczatek petli i czekamy na wlasciwa reakcje gracza.

	p_player->hpTimeInit();                                            //Inicjalizacja czasu i zdrowia gracza zgodnie z trudnoscia gry (zapisana juz w obiekcie p_player)
	lockArea(p_player, p_p_worldArr);                                 // zamykanie wyjsc poza obszar gry
	if (p_player->get_hardMode()) hardMode(p_player, p_p_worldArr);  //implementacja wysokiej trudnosci w ukladzie obszazru gry
	p_player->set_endGame(gameLoop(p_player, p_p_worldArr));        //tu zaczyna sie i konczy petla gry

	return p_player->get_endGame();                               //koniec gry, wraz z zwroceniem informacji o przyczynie
}

void lockArea(Player* p_player, World** p_p_worldArr)
{
	int p = 1;                                  //numerator pokojow do opisu
	const int xM = p_player->get_sizeX();       //wyciagamy z obiektu rozmiar gry, mozemy zastosowac odwolanie do metody w kodzie za kazdym razem, ale tak bedzie to bardziej przejrzyste
	const int yM = p_player->get_sizeY();       //

	for (int i = 0; i < xM; i++)
		for (int j = 0; j < yM; j++)
		{
			p_p_worldArr[i][j].set_infoCell(p);                           //wprowadzamy przy okazji mumer pokoju (reszte roboty za³atwia za nas metoda interfejsu set_infoCell()
			p++;
			                                                              //blokujemy drzwi zewnetrzne
			if (i == 0) p_p_worldArr[i][j].set_exitCell(0, false);        //zamykamy drzwi na "polnocy"
			if (j == (yM - 1)) p_p_worldArr[i][j].set_exitCell(1, false); //zamykamy drzwi na "wschodzie"
			if (i == (xM - 1)) p_p_worldArr[i][j].set_exitCell(2, false); //zamykamy drzwi na "poludniu"
			if (j == 0) p_p_worldArr[i][j].set_exitCell(3, false);        //zamykamy drzwi na "zachodzie"
		}
	}

void hardMode(Player *p_player, World** p_p_worldArr)
//zamykamy jedno losowe przejscie w kazdym pokoju, z wylaczeniem pokojow zewnetrznych  (po zaimplementowaniu kluczy, mozliwe, ze zmienimy na zmiany bez wykluczenia pokoi zewnetrznych)
//taki sposob losowania i ustawiania parametrow, pozwala na to, ze sporo drzwi bedzie nie do przejscia tylko w jedna strone, co dodatkowo urozmaici zabawe.
{
	for (int i = 1; i < (p_player->get_sizeX() - 1); i++)
		for (int j = 1; j < (p_player->get_sizeY() - 1); j++)
		{
			int tmp = (rand() % 4);                         //wartosc tymczasowa, wykorzystywana tylko w nastepnej linijce do okreslenia ktore (z 4) drzwi zamknac
			p_p_worldArr[i][j].set_exitCell(tmp, false);
		}
}

//  **  t¹ czêœæ zostawiamy sobie na kolejny raz. **

int gameLoop(Player * p_player, World ** p_p_worldArr)
{
	std::cout << "Tu bedziemy grali!!" << std::endl;
	_getch();
	return 0;
}