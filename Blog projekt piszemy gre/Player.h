#pragma once

/*
 * Klasa przechowujaca i manipulijaca danymi gry zwiazanymi z polozeniem obiektow w swiecie gry oraz danych gracza
 * takich jak zdrowie czy pozostaly czas gry.
 *
 * endGame:             znacznik koñca gry  0-kontynuacja | 1-brak zdrowia | 2-ucieczka | 3-wygrana! | 4-koniec czasu |8 - z³y klawisz| 9-b³¹d pliku
 * Tablica lokacji gry: 0-startX, 1-startY(wspolrzedne startu gry) , 2-endX, 3-endY (wspolrzedne konca gry) , 4 actX, 5 actY (aktualna pozycja gracza)
 * playerLastMove;	    wybor ruchu przez gracza: 0-w | 1-d | 2-s | 3-a | 4-klapa | 5-odpoczynek | 6- koniec | 9 - wartoœæ startowa
 */

class Player
{
	int  positionArray[8]{};    // 0-startX, 1-startY(wspolrzedne startu gry) , 2-endX, 3-endY (wspolrzedne konca gry) , 4 actX, 5 actY (aktualna pozycja gracza), 6 sizeX, 7 sizeY (wielkosc swiata)
	int  endGame;              // 0-kontynuacja | 1-brak zdrowia | 2-ucieczka | 3-wygrana! | 4-koniec czasu |8 - z³y klawisz| 9-b³¹d pliku
	int  playerLastMove;	  // 0-w | 1-d | 2-s | 3-a | 4-klapa | 5-odpoczynek | 6- koniec | 9 - wartoœæ startowa
	int  playerTime;	     //czas do konca gry
	int  playerHp;		    //zdrowie gracza
	int  playerRounds;	   //ilosc rund w grze
	bool hardMode;		  //trudnosc gry - false: latwa, true: trudna

	void set_playerTime(int);   //czas rozgrywki

public:

	Player(int, int);
	~Player();

	void hpTimeInit();    //ustawianie zdrowia gracza i czasu rozgrywki w zaleznosci od trudnosci gry
	void move();         //Realizacja przemieszczenia na mowy obszar
	int gameOver();     //obsluga konca gry.

	int get_startX();   //pobieranie wspolrzednej X pola startowego   [0]
	int get_startY();   //pobieranie wspolrzednej y pola startowego   [1]
	int get_endX();     //pobieranie wspolrzednej X pola koncowego    [2]
	int get_endY();     //pobieranie wspolrzednej y pola koncowego    [3]
	int get_actX();     //pobieranie wspolrzednej X aktualnej pozycji [4]
	int get_actY();     //pobieranie wspolrzednej y aktualnej pozycji [5]
	int get_sizeX();    //pobieranie parametru x wielkosci swiata     [6]
	int get_sizeY();    //pobieranie parametru y wielkosci swiata     [7]

	int get_playerLastMove();
	int  get_endGame();
	int  get_playerTime();
	int  get_playerHp();
	int  get_playerRounds();
	bool get_hardMode();

	void set_playerLastMove(int);
	void set_endGame(int);
	void set_actY(int);
	void set_actX(int);
	void set_playerHp(int);
	void set_hardMode(bool);

	void change_plus_PlayerHp(int);      //zmiana wartosci zdrowia gracza o podany parametr (dodawanie).
	void change_minus_PlayerTime(int);   //zmiana wartosci czasu do konca gry o podana wartosc (odejmowanie).
	void change_addOne_PlayerRounds();   //dodanie jednej rundy gry do licznika
};
