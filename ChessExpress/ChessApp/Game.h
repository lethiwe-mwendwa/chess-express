#pragma once
#include "SDL.h"
#include "Constants.h"

void titleSequence(SDL_Renderer* renderer, int sWidth, int sHeight);
void makeMove(SDL_Renderer* renderer, int x, int y);
void startMove(SDL_Renderer* renderer, int x, int y);
void dragPiece(SDL_Renderer* renderer, int x, int y);
void setCheckValue(SDL_Renderer* renderer);
void initChessGame(SDL_Renderer* renderer);
void menuSequence(SDL_Renderer* renderer, int sWidth, int sHeight);