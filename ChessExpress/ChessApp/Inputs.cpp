#pragma once
#include "SDL.h"
#include "Constants.h"

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