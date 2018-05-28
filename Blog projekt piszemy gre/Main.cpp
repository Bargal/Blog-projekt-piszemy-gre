#include "Player.h"
#include "World.h"
#include "game.h"
#include "Windows.h"

int main() {
	// zmiana wielkosci okna konsoli
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 900, 800, TRUE);

	int endGame; // 0 - kontynuacja gry
	// TODO: tu mo¿na umiescic zmiane wielkosci obszaru gry, i dla tego nie traktujemy w kodzie tych wartoœci jako niezmiennych i identycznych.
	const int worldSizeX = 10;
	const int worldSizeY = 10;

	do {
		auto p_p_worldArr = new World *[worldSizeX];
		for (int i = 0; i < worldSizeX; i++)
			p_p_worldArr[i] = new World[worldSizeY];

		Player player(worldSizeX, worldSizeY); // dane gracza

		endGame = startGame(&player, p_p_worldArr); // game.h

		for (int i = 0; i < worldSizeX; i++)
			delete[] p_p_worldArr[i];
		delete[] p_p_worldArr;
	} while (endGame == 0);

	return 0;
}