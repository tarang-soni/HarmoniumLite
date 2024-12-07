#include <iostream>
#include "Game.h"
#include <windows.h> 
int main() {
	HWND window;
	window = FindWindowA("ConsoleWindowClass", NULL);
#ifdef NDEBUG
	ShowWindow(window, 0);
#elif _DEBUG
	ShowWindow(window, 1);

#endif // NDEBUG


	Game game("Hello World", 800, 800);
	game.Run();
	return 0;
}