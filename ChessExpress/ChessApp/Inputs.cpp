#pragma once
#include "SDL.h"
#include "Constants.h"
#include <iostream>
using namespace std;

SDL_Rect *findClickedRect(int x, int y) {

	SDL_Point inputPoint = { x, y };
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (SDL_PointInRect(&inputPoint, &boardTiles[i][j])) {
				return &boardTiles[i][j];
			}
		}
	}
	return NULL;
};

Piece *findClickedPiece(int x, int y) {

	SDL_Point inputPoint = { x, y };
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (SDL_PointInRect(&inputPoint, &boardTiles[i][j])) {
				return piecesOnBoard[i][j];

			}
		}
	}
	return NULL;
};