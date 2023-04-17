#include "SDL.h"
#include "Constants.h"
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
#include "Inputs.h"
#include "SDL_mixer.h"
#include "King.h"
#include "Game.h"
using namespace std;

bool titleScreen = true;
bool gameRunning = true;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(0);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	// Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
		printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
		return 1;
	}

	// At this point, the audio device is open and ready to use

	dieA = Mix_LoadWAV("assets/die.wav");
	moveA = Mix_LoadWAV("assets/move.wav");
	introA = Mix_LoadWAV("assets/ChessExpress.wav");
	startA = Mix_LoadWAV("assets/Start.wav");
	checkA = Mix_LoadWAV("assets/checkmate.wav");
	endGameA = Mix_LoadWAV("assets/endGame.wav");

	// Clean up SDL_mixer when you're done
	Mix_CloseAudio();

	if (startA == NULL) {
		printf("Failed to load start sound: %s\n", Mix_GetError());
		return 1;
	}

	if (introA == NULL) {
		printf("Failed to load intro sound: %s\n", Mix_GetError());
		return 1;
	}

	if (dieA == NULL) {
		printf("Failed to load die sound: %s\n", Mix_GetError());
		return 1;
	}

	if (moveA == NULL) {
		printf("Failed to load move sound: %s\n", Mix_GetError());
		return 1;
	}
	//Mix_Volume(60);

	//Window and Renderer creation
	SDL_Window* window = SDL_CreateWindow("Chess Express", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	SDL_Surface* icon = SDL_LoadBMP("assets/gameIcon.BMP");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);


	int introChannel = Mix_PlayChannel(-1, introA, 0);
	if (introChannel == -1) {
		printf("Failed to play die sound: %s\n", Mix_GetError());
	}

	cout << chessExpressASCII << endl;
	titleSequence(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	while (titleScreen) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				titleScreen = false;
				gameRunning = false;
				Mix_FreeChunk(dieA);
				Mix_FreeChunk(moveA);
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 0;
			}
			if (event.type == SDL_KEYDOWN) {
				//cout << event.key.keysym.sym << endl;
				if (event.key.keysym.sym == SDLK_RETURN) {

					titleScreen = false;
					menu = true;
				}
			}
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				titleSequence(renderer, event.window.data1, event.window.data2);
			}
		}
	}
	
	
	// The game loop
	while (gameRunning) {
		//Uint64 start = SDL_GetPerformanceCounter();

		if (menu) {
			menuSequence(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		while (menu) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					titleScreen = false;
					gameRunning = false;
					Mix_FreeChunk(dieA);
					Mix_FreeChunk(moveA);
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					SDL_Quit();
					return 0;
				}
				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_RETURN) {

						menu = false;
						chessStarted = true;
					}
				}
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					menuSequence(renderer, event.window.data1, event.window.data2);
					SDL_RenderPresent(renderer);
				}
			}
		}
		
		if (checkmate) {
			cout << "-----------------------------" << endl;
			cout << "Press Enter to go back to Menu" << endl;
		}
		while (checkmate) {
			
			while (SDL_PollEvent(&event)) {
				if(event.type == SDL_QUIT){
					checkmate = false;
					gameRunning = false;
					Mix_FreeChunk(dieA);
					Mix_FreeChunk(moveA);
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					SDL_Quit();
					return 0;
				}
				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_RETURN) {
						checkmate = false;
						menu = true;
					}
				}
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					Board::drawBoard(renderer, event.window.data1, event.window.data2);
					Board::pieceDisplay(renderer);
					setCheckValue(renderer);
					SDL_RenderPresent(renderer);
				}
			}

		}

		if (chessStarted) {
			initChessGame(renderer);
		}
		while(chessStarted){
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					gameRunning = false;

					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						//Chess thing lol /*
						Board::drawBoard(renderer, event.window.data1, event.window.data2);
						Board::pieceDisplay(renderer);
						SDL_RenderPresent(renderer);

						//make a function that displays the current board shape. make a fen notation val called "current", 
						//and every time it resizes it redraws from looking at it
					}

					break;
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {

					case SDL_BUTTON_LEFT:

						//select piece // start move
						startMove(renderer, event.button.x, event.button.y);

						break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {

						makeMove(renderer, event.button.x, event.button.y);

						break;
				case SDL_MOUSEMOTION:

					dragPiece(renderer, event.motion.x, event.motion.y);

					break;
					}
				}
			}
		}
	}
	Mix_FreeChunk(dieA);
	Mix_FreeChunk(moveA);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


