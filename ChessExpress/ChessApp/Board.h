#pragma once
#include "SDL.h"
#include "Constants.h"

class Board
{
public:
	Board();
	static void drawBoard(SDL_Renderer* renderer, float width, float height);
	static void fenDisplay(SDL_Renderer* renderer, char fen[]);
	static void fenSplitter(char fen[]);

private:
	
};


