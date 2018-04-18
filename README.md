 Projekt gry tworzonej specjalnie na potrzeby bloga
 Devhobby - Programowanie z kotem na kolanach
 https://devhobby.eu
 Kod pisany w Visual Studio 2017
 Przez Bartosz Gala '2018

 Za³o¿enia podstawowe:

 Ma to byc gra konsolowa opieraj¹ca siê na dwu wymiarowej planszy podobnej do szachownicy,
 na ktorej mozliwy jest ruch w p³aszczyznie poziomej w kierunkach podstawowych (czyli bez skosow).
 Bede chcial umiescic w grze skrzynie, przeciwnikow a w dalszym etapie fabulê.
 Potrzebny bedzie tez system punktujacy oraz zapis punktacji do pliku na koniec gry.

 
 
 Zmienne globalne:

 BRAK

 
 funkcja main()

 (Main.cpp)
 worldArr[][];   // glowna tablica na ktorej opiera sie konstrukcja swiata.
 

 Klasy :

 (World.h)  World:          //klasa opisujaca pole gry.
 (Player.h) Player:         //klasa przechowujaca dane o graczu i aktualnej rozgrywce.
 (ScoreBoard.h) ScoreBoard: //klasa odpowiadaj¹ca za zapis, odczyt, wyœwietlanie i sortowanie tabeli wyników gry


