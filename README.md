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
 

 Klasy wraz z opisem zmiennych:

 (World.h)  World:     //klasa opisujaca pole gry.
 (Player.h) Player:    //klasa przechowujaca dane o graczu i aktualnej rozgrywce.


 funkcje:

(game.h):
startGame();  //funkcja zawiera menu startowe gry i wywolania wszystkich funkcji przygotowawczych i konczacych gre, oraz glowna petle gry
lockArea();   //funkcja zamykajaca wszystkie wyjscia poza obszar gry
hardMode();   //procedura dostosowania planszy gry do trybu trudnego (losowe zamykanie drzwi wewnetrznych)
gameLoop();   //glowna petla gry, zwraca znacznik konca gry: 0 - gramy dalej, 1 - zwyciestwo 2 - przegrana: brak zycia, 3 - przegrana: koniec czasu 4 - przegrana: ucieczka.

