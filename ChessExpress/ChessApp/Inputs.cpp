#pragma once
#include "SDL.h"
#include "Constants.h"
#include <iostream>
#include "Inputs.h"
using namespace std;

SDL_Rect *findClickedRect(int x, int y) {


	int row;
	int column;

	if (findClickedCords(x, y, row, column)) {
		return &boardTiles[row][column];
	}
	return NULL;
};

Piece *findClickedPiece(int x, int y) {
	int row;
	int column;

	if (findClickedCords(x, y, row, column)) {
		return piecesOnBoard[row][column];
	}
	return NULL;
}

bool findClickedCords(int x, int y, int& row, int& column)
{
	SDL_Point inputPoint = { x, y };
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (SDL_PointInRect(&inputPoint, &boardTiles[i][j])) {
				column = j;
				row = i;
				
				return true;
			}
		}
	}
	return false;
}