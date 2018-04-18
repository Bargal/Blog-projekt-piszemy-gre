#include "World.h"
#include "Player.h"
#include "game.h"
#include <iostream>
#include <string>
#include <conio.h>  //tylko dla _getch()

int startGame(Player *p_player, World **p_p_worldArr)
{
	system("cls");
	std::cout << "Witam w qube txt" << std::endl;
	std::cout << "\nzaraz wejdziesz do losowego boxu " << std::endl;
	std::cout << "twoim zadaniem bedzie wydostanie sie na zewnatrz" << std::endl;
	std::cout << "w tym celu uzyj klawiszy WSAD :" << std::endl;
	std::cout << "\n W - polnoc\n E - poludnie\n A - zachod\n D - wschod" << std::endl;
	std::cout << "lub klawiszami strzalek" << std::endl;
	std::cout << "spokojnie - nie musisz tego zapamietac - bedzie to podawane podczas gry :)" << std::endl;
	std::cout << "\nNa poczatek masz 10 punktow zycia.\nCzesc pokojow zadaje obrazena a odpoczynek w czesci pokojow leczy rany" << std::endl;
	std::cout << "odpoczywasz uzywajac klawisza Q" << std::endl;
	std::cout << "masz okreslona ilosc jednostek czasu a kazdy pokoj zabiera pewna ilosc czasu na ture" << std::endl;
	std::cout << "\nzycze milej zabawy, nacisnij dowolny klawisz aby zaczac." << std::endl;
	std::cout << "koncowy wynik zalezy od czasu przejscia i pozostalgo zdrowia" << std::endl;
	std::cout << "\n\nwybierz trudnosc gry: 1 - latwa 2- trudna - uwaga, gra moze byc sporadycznie nie mozliwa do ukonczenia " << std::endl;
	//TODO: ale bedzie zawsze mozliwa jak dodamy eventy i klucze, i wtedy zmienimy opis

	int tmp;
	do
	{
		tmp = 0;
		char tempMode = _getch();                                 //wczytujemy z klawiatury znak i przypisujemy do zmiennej. _getch() zwraca nam pojedynczy znak wczytany z klawiatury.
		if (tempMode == '1') p_player->set_hardMode(false);      //ustawiamy trudnosc gry w obiekcie p_player
		else if (tempMode == '2')p_player->set_hardMode(true);  //
		else tmp = 1;                                          // a jesli podano inna wartosc niz 1 albo 2...
	} while (tmp == 1);                                       //wracamy na poczatek petli i czekamy na wlasciwa reakcje gracza.

	p_player->hpTimeInit();                                            //Inicjalizacja czasu i zdrowia gracza zgodnie z trudnoscia gry
	lockArea(p_player, p_p_worldArr);                                 // zamykanie wyjsc poza obszar gry
	if (p_player->get_hardMode()) hardMode(p_player, p_p_worldArr);  //implementacja wysokiej trudnosci w ukladzie obszazru gry
	p_player->set_endGame(gameLoop(p_player, p_p_worldArr));        //tu zaczyna sie i konczy petla gry
	return p_player->gameOver();                                   //sprawdzenie i obsluga konca gry.
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
//zamykamy jedno losowe przejscie w kazdym pokoju, z wylaczeniem pokojow zewnetrznych  (po zaimplementowaniu kluczy zmienimy na: bez wykluczenia pokoi zewnetrznych)
//taki sposob losowania i ustawiania parametrow, pozwala na to, ze sporo drzwi bedzie nie do przejscia tylko w jedna strone, co dodatkowo urozmaici zabawe.
{
	for (int i = 1; i < (p_player->get_sizeX() - 1); i++)
		for (int j = 1; j < (p_player->get_sizeY() - 1); j++)
		{
			int tmp = (rand() % 4);                         //wartosc tymczasowa, wykorzystywana tylko w nastepnej linijce do okreslenia ktore (z 4) drzwi zamknac
			p_p_worldArr[i][j].set_exitCell(tmp, false);
		}
}

int gameLoop(Player * p_player, World ** p_p_worldArr)
{
	// Informujemy gracza o dokladnym celu misji
	system("cls");

	std::cout << "\n\n\n\nZaraz wejdziesz do gry!!!" << std::endl;
	std::cout << "\nzaczniesz w miejscu oznaczonym jako: " << p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_infoCell() << std::endl;
	std::cout << "wyjscie znajduje sie w pokoju oznaczonym jako: " << p_p_worldArr[p_player->get_endX()][p_player->get_endY()].get_infoCell() << std::endl;
	std::cout << "\nzapamietaj to, bo od teraz podawany bedzie tylko numer pokoju w ktorym aktualnie jestes!" << std::endl;
	std::cout << "\n\nWspinasz sie po drabince do pomieszczenia od ktorego zaczniesz gre," << std::endl;
	std::cout << "celem jest dotrzec jak najszybciej do pomieszczenia z taka sama klapa w podlodze i wyjscie" << std::endl;
	std::cout << "\n\nNacisnij dowolny klawisz" << std::endl;
	_getch();

	do //pêtla wewnêtrzna - tudzieje sie wszystko
	{
		system("cls");

		p_player->change_plus_PlayerHp(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_hpCell()); //zmiana zdrowia gracza w nowym pokoju
		if (p_player->get_playerHp() <= 0) return 1;                                                          //sprawdzenie czy HP s¹ powyzej zero, jesli nie to koniec gry

		p_player->change_minus_PlayerTime(p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_timeCell()); //zmiana czasu zgodna z wlasciwoscia nowego obszaru
		if (p_player->get_playerTime() < 0) return 4;                                                              //sprawdzanie czasu, jesli ponizej zera to koniec gry

																		 // wypisujemy gorny pasek statusu gry
		std::cout << "    HP  " << p_player->get_playerHp()
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

void areaTextInformation(Player * p_player, World ** p_p_worldArr) //mniej komentarzy, poniewaz sam tekst wyswietlany doskonale komentuje kod.
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
void areaTextGraphics(Player * p_player, World ** p_p_worldArr)  //Grafika tekstowa przedstawiaj¹ca pokoj wraz z stanem otwarcia drzwi.
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

void areaTextPlayerInfo(Player * p_player, World ** p_p_worldArr)//opis wplywu pokoju na gracza
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

int movePlayer(Player* p_player, World ** p_p_worldArr)
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

	//pobranie reakcji gracza z klawiatury, sprawdzenie i zwrotu parametru decyzji gracza.
	// w celach pogladowych dwie wersje: pierwsza z wykorzystaniem operatora warunkowego ?:

	do
	{
		tst = 0;
		char keyboardChar = _getch(); //Pobieranie znaku z klawiatury

		actualMove = (keyboardChar == 'w' || keyboardChar == 'W') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(0) ? 0
			: (keyboardChar == 'd' || keyboardChar == 'D') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1) ? 1
			: (keyboardChar == 's' || keyboardChar == 'S') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(2) ? 2
			: (keyboardChar == 'a' || keyboardChar == 'A') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3) ? 3
			: (keyboardChar == 'q' || keyboardChar == 'Q') && (p_player->get_actX() == p_player->get_endX() && p_player->get_actY() == p_player->get_endY()) ? 4 //obs³uga pola koñcowego
			: keyboardChar == 'e' || keyboardChar == 'E' ? 5
			: keyboardChar == 'r' || keyboardChar == 'R' ? 6
			: tst = 1;
	} while (tst == 1);
	return actualMove;

	/* Ponizej, dla porownania to samo z wykorzystaniem komendy if - else if

	do
	{
		tst = 0;a
		char keyboardChar = _getch(); //Pobieranie znaku z klawiatury

		if ((keyboardChar == 'w' || keyboardChar == 'W') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(0)) actualMove = 0;
		else if ((keyboardChar == 'd' || keyboardChar == 'D') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(1)) actualMove = 1;
		else if ((keyboardChar == 's' || keyboardChar == 'S') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(2)) actualMove = 2;
		else if ((keyboardChar == 'a' || keyboardChar == 'A') && p_p_worldArr[p_player->get_actX()][p_player->get_actY()].get_exitCell(3)) actualMove = 3;
		else if ((keyboardChar == 'q' || keyboardChar == 'Q') && (p_player->get_actX() == p_player->get_endX() && p_player->get_actY() == p_player->get_endY())) actualMove = 4;
		else if (keyboardChar == 'e' || keyboardChar == 'E') actualMove = 5;
		else if (keyboardChar == 'r' || keyboardChar == 'R') actualMove = 6;
		else tst = 1;
	} while (tst == 1);
	return actualMove;
	*/
}