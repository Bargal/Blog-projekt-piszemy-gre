#include "World.h"
#include "Player.h"
#include "game.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <chrono>

int startGame(Player *p_player, World **p_p_worldArr)
{
	system("cls");
	std::cout
		<< "Witam w qube txt" << std::endl
		<< "\nzaraz wejdziesz do losowego boxu " << std::endl
		<< "twoim zadaniem bedzie wydostanie sie na zewnatrz" << std::endl
		<< "w tym celu uzyj klawiszy WSAD :" << std::endl
		<< "\n W - polnoc\n E - poludnie\n A - zachod\n D - wschod" << std::endl
		<< "lub klawiszami strzalek" << std::endl
		<< "spokojnie - nie musisz tego zapamietac - bedzie to podawane podczas gry :)" << std::endl
		<< "\nNa poczatek masz 10 punktow zycia.\nCzesc pokojow zadaje obrazena a odpoczynek w czesci pokojow leczy rany" << std::endl
		<< "odpoczywasz uzywajac klawisza Q" << std::endl
		<< "masz okreslona ilosc jednostek czasu a kazdy pokoj zabiera pewna ilosc czasu na ture" << std::endl
		<< "\nzycze milej zabawy, nacisnij dowolny klawisz aby zaczac." << std::endl
		<< "koncowy wynik zalezy od czasu przejscia i pozostalgo zdrowia" << std::endl
		<< "\n\nwybierz trudnosc gry: 1 - latwa 2- trudna - uwaga, gra moze byc sporadycznie nie mozliwa do ukonczenia " << std::endl;
	//TODO: ale bedzie zawsze mozliwa jak dodamy eventy i klucze, i wtedy zmienimy opis

	int tmp;
	do
	{
		tmp = 0;
		char tempMode = _getch();
		if (tempMode == '1') p_player->set_hardMode(false);      //ustawiamy trudnosc gry w obiekcie p_player
		else if (tempMode == '2')p_player->set_hardMode(true);
		else tmp = 1;
	} while (tmp == 1);
	p_player->hpTimeInit();                                            //Inicjalizacja czasu i zdrowia gracza zgodnie z trudnoscia gry
	lockArea(p_player, p_p_worldArr);                                 // zamykanie wyjsc poza obszar gry
	if (p_player->get_hardMode()) hardMode(p_player, p_p_worldArr);  //implementacja wysokiej trudnosci w ukladzie obszazru gry
	p_player->set_endGame(gameLoop(p_player, p_p_worldArr));        //tu zaczyna sie i konczy petla gry
	return p_player->gameOver();                                   //sprawdzenie i obsluga konca gry.
}

void lockArea(Player* p_player, World **p_p_worldArr)
{
	int p = 1;                                  //numerator pokojow do opisu
	const int xM = p_player->get_sizeX();
	const int yM = p_player->get_sizeY();

	for (int i = 0; i < xM; i++)
		for (int j = 0; j < yM; j++)
		{
			p_p_worldArr[i][j].set_infoCell(p);                           //wprowadzamy mumer pokoju
			p++;
			//blokujemy drzwi zewnetrzne
			if (i == 0) p_p_worldArr[i][j].set_exitCell(0, false);        //zamykamy drzwi na "polnocy"
			if (j == (yM - 1)) p_p_worldArr[i][j].set_exitCell(1, false); //zamykamy drzwi na "wschodzie"
			if (i == (xM - 1)) p_p_worldArr[i][j].set_exitCell(2, false); //zamykamy drzwi na "poludniu"
			if (j == 0) p_p_worldArr[i][j].set_exitCell(3, false);        //zamykamy drzwi na "zachodzie"
		}
}

void hardMode(Player *p_player, World** p_p_worldArr)
//zamykamy jedno losowe przejscie w kazdym pokoju, z wylaczeniem pokojow zewnetrznych
{
	std::default_random_engine generator;
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	generator.seed(seed);
	std::uniform_int_distribution<> distDoor(0, 3);

	for (int i = 1; i < (p_player->get_sizeX() - 1); i++)
		for (int j = 1; j < (p_player->get_sizeY() - 1); j++)
		{
			p_p_worldArr[i][j].set_exitCell(distDoor(generator), false);
		}
}

int gameLoop(Player * p_player, World **p_p_worldArr)
{
	// Informujemy gracza o dokladnym celu misji
	system("cls");

	std::cout
		<< "\n\n\n\nZaraz wejdziesz do gry!!!" << std::endl
		<< "\nzaczniesz w miejscu oznaczonym jako: " << p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_infoCell() << std::endl
		<< "wyjscie znajduje sie w pokoju oznaczonym jako: " << p_p_worldArr[p_player->get_endX()][p_player->get_endY()].get_infoCell() << std::endl
		<< "\nzapamietaj to, bo od teraz podawany bedzie tylko numer pokoju w ktorym aktualnie jestes!" << std::endl
		<< "\n\nWspinasz sie po drabince do pomieszczenia od ktorego zaczniesz gre," << std::endl
		<< "celem jest dotrzec jak najszybciej do pomieszczenia z taka sama klapa w podlodze i wyjscie" << std::endl
		<< "\n\nNacisnij dowolny klawisz" << std::endl;
	while (_kbhit()) //czyszczenie buforu klawiatury
	{
		_getche();
	}
	_getch();

	do //pêtla wewnêtrzna
	{
		system("cls");

		p_player->change_plus_PlayerHp(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_hpCell()); //zmiana zdrowia gracza w nowym pokoju
		if (p_player->get_playerHp() <= 0) return 1;                                                          //sprawdzenie czy HP s¹ powyzej zero, jesli nie to koniec gry

		p_player->change_minus_PlayerTime(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_timeCell()); //zmiana czasu zgodna z wlasciwoscia nowego obszaru
		if (p_player->get_playerTime() < 0) return 4;                                                              //sprawdzanie czasu, jesli ponizej zera to koniec gry

																		 // wypisujemy gorny pasek statusu gry
		std::cout 
			<< "    HP  " << p_player->get_playerHp()
			<< "   zakonczone rundy  " << p_player->get_playerRounds()
			<< "    Pozostalo czasu  " << p_player->get_playerTime() << std::endl << std::endl;

		areaTextInformation(p_player, p_p_worldArr); //opisujemy i pokazujemy aktualny obszar gry
		areaTextGraphics(p_player, p_p_worldArr);    //Grafika tekstowa przedstawiaj¹ca pokoj wraz z stanem otwarcia drzwi.
		areaTextPlayerInfo(p_player, p_p_worldArr); //opis wplywu pokoju na gracza
		p_player->change_addOne_PlayerRounds();      //dodajemy do licznika jedna runda gry
		p_player->set_playerLastMove(movePlayer(p_player, p_p_worldArr));  //pobieranie i zapis nowego ruchu gracza
		p_player->move(); //wykonujemy ruch gracza zgodnie z poleceniem z klawiatury.

		/*
		 * TODO: Tu jest miejsce na dopisywanie kolejnych funkcjonalnosci gry
		 */
	} while (p_player->get_endGame() == 0);

	return p_player->get_endGame();
}

void areaTextInformation(Player * p_player, World **p_p_worldArr)
{
	std::cout << "wchodzisz do pomieszczenia przez ";
	if (p_player->get_playerLastMove() == 9) std::cout << "klape w podlodze " << std::endl;
	if (p_player->get_playerLastMove() == 0) std::cout << "poludniowe drzwi " << std::endl;
	if (p_player->get_playerLastMove() == 1) std::cout << "zachodnie drzwi " << std::endl;
	if (p_player->get_playerLastMove() == 2) std::cout << "polnocne drzwi " << std::endl;
	if (p_player->get_playerLastMove() == 3) std::cout << "wschodnie drzwi " << std::endl;

	if (p_player->get_playerLastMove() == 0 && !p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(2)) std::
		cout << "Drzwi za toba zatrzaskuja sie" << std::endl;
	if (p_player->get_playerLastMove() == 1 && !p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3)) std::
		cout << "Drzwi za toba zatrzaskuja sie" << std::endl;
	if (p_player->get_playerLastMove() == 2 && !p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(0)) std::
		cout << "Drzwi za toba zatrzaskuja sie" << std::endl;
	if (p_player->get_playerLastMove() == 3 && !p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1)) std::
		cout << "Drzwi za toba zatrzaskuja sie" << std::endl;

	std::cout << "\nw jednolicie bialym pokoju widzisz tylko na kazdej scianie napis \n\n    \""
		<< p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_infoCell() << "\"" << std::endl;

	std::cout << "\no ile pamietasz jestes w tym pokoju po raz " << p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_beInside();

	std::cout << "\n\nwychodza z tad drzwi na ";
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(0)) std::cout << "polnoc ";
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1)) std::cout << "wschod ";
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(2)) std::cout << "poludnie ";
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3)) std::cout << "zachod ";
	if (p_player->get_actX() == p_player->get_startX() && p_player->get_actY() == p_player->get_startY())
		std::cout << "\nw podloze widzisz klape przez ktora sie tu dostales" << std::endl;
	if (p_player->get_actX() == p_player->get_endX() && p_player->get_actY() == p_player->get_endY())
		std::cout << "\n w podlodze widzisz nieznana klape, czyzby upragnione wyjscie??" << std::endl;
	std::cout << std::endl;
}
//Grafika tekstowa przedstawiaj¹ca pokoj wraz z stanem otwarcia drzwi.
void areaTextGraphics(Player * p_player, World **p_p_worldArr)
{
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(0))
		std::cout << "  _|____*   *____|_  " << std::endl;
	else
		std::cout << "  _|____*___*____|_  " << std::endl;
	std::cout << "   |             |   " << std::endl;
	std::cout << "   |             |   " << std::endl;
	std::cout << "   *             *   " << std::endl;
	if ((p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1) && (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3))))
		std::cout << "                     " << std::endl;
	if ((p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3)) && !(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1)))
		std::cout << "                 |   " << std::endl;
	if ((p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1)) && !(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3)))
		std::cout << "   |                 " << std::endl;
	if (!(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1)) && !(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3)))
		std::cout << "   |             |   " << std::endl;
	std::cout << "   *             *   " << std::endl;
	std::cout << "   |             |   " << std::endl;
	std::cout << "   |             |   " << std::endl;
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(2))
		std::cout << "  _|____     ____|_  " << std::endl;
	else
		std::cout << "  _|____ ___ ____|_  " << std::endl;
	std::cout << "   |    *   *    |   " << std::endl;
}

//opis wplywu pokoju na gracza
void areaTextPlayerInfo(Player * p_player, World **p_p_worldArr)
{
	std::cout << "\nJednoczesnie czujesz ze w pokoju panuje ";
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_hpCell() == 0) std::cout << "neutralna atmosfera " << std::endl;
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_hpCell() > 0)
		std::cout << "przyjazna atmosfera i orzymujesz "
		<< p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_hpCell() << " HP" << std::endl;
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_hpCell() < 0)
		std::cout << "szkodliwa atmosfera i orzymujesz "
		<< p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_hpCell() << " HP" << std::endl;
	std::cout << "\nPobyt w tym pokoju zajmuje " << p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_timeCell() << " jednostek czasu" << std::endl;
}

int movePlayer(Player* p_player, World **p_p_worldArr)
{
	//Wyliczenie mozliwych wyjsc z obszaru (z wykluczeniem zamknietych drzwi)
	std::cout << std::endl;
	std::cout << "nacisnij E zeby odpoczac w pokoju jedna runde;  R - zrezygnuj i wyjdz z gry\n" << std::endl;
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(0)) std::cout << "nacisnij W zeby isc na polnoc" << std::endl;
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1)) std::cout << "nacisnij D zeby isc na wschod" << std::endl;
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(2)) std::cout << "nacisnij S zeby isc na poludie" << std::endl;
	if (p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3)) std::cout << "nacisnij A zeby isc na zachod" << std::endl;
	if (p_player->get_actX() == p_player->get_endX() && p_player->get_actY() == p_player->get_endY())
		std::cout << "\n\a\a****** nacisnij Q zeby skorzystac z klapy w podlodze *****" << std::endl;

	p_player->set_playerLastMove(9);
	int actualMove;
	int tst;

	//pobranie reakcji gracza z klawiatury, sprawdzenie i zwrotu parametru decyzji gracza
	do
	{
		tst = 0;
		char keyboardChar = _getch();

		actualMove = (keyboardChar == 'w' || keyboardChar == 'W') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(0) ? 0
			: (keyboardChar == 'd' || keyboardChar == 'D') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1) ? 1
			: (keyboardChar == 's' || keyboardChar == 'S') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(2) ? 2
			: (keyboardChar == 'a' || keyboardChar == 'A') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3) ? 3
			: (keyboardChar == 'q' || keyboardChar == 'Q') && (p_player->get_actX() == p_player->get_endX() && p_player->get_actY() == p_player->get_endY()) ? 4
			: keyboardChar == 'e' || keyboardChar == 'E' ? 5
			: keyboardChar == 'r' || keyboardChar == 'R' ? 6
			: tst = 1;
	} while (tst == 1);
	return actualMove;
}
