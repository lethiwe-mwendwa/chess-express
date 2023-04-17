#include "Constants.h"

int main(int argc, char* argv[])
{

	//Initializing the libs
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(0);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
		printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
		return 1;
	}

	// Audio Device Ready to use
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

	//Window and Renderer creation
	SDL_Window* window = SDL_CreateWindow("Chess Express", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	SDL_Surface* icon = SDL_LoadBMP("assets/gameIcon.BMP");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	// The title Screen Before the game
	// Outside of gamerunning since it will only ever run once.
	if (titleScreen) {
		int introChannel = Mix_PlayChannel(-1, introA, 0);
		if (introChannel == -1) {
			printf("Failed to play sound: %s\n", Mix_GetError());
		}
		cout << chessExpressASCII << endl;
		titleSequence(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	while (titleScreen) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				titleScreen = false;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_RETURN) {
					titleScreen = false;
					gameRunning = true;
					menu = true;
				}
			}
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				titleSequence(renderer, event.window.data1, event.window.data2);
			}
		}
	}
	
	// The main game loop
	// Here we switch between Menu, Chessstarted, and Checkmate.
	if (gameRunning) {
		cout << lethiweMwendwaASCII << endl;
		cout << "Librarys used:" << endl << "SDL2, SDL2_Mixer" << endl << endl;
	}
	while (gameRunning) {

		// Menu State: Player gets to input FEN
		// Ends once valid inputs are given
		if (menu) {
			menuSequence(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			cout << "-----------------------------" << endl;
			cout <<menuASCII<< endl << endl;
			int userSelect;
			bool selected = false;
			while (not selected) {
				cout << "-----------------------------" << endl;
				cout << "What do you want to do?" << endl << endl;
				cout << "Type \"1\" to Load Default Fen" << endl;
				cout << "Type \"2\" to Load User Fen" << endl;
				cout << "Type \"3\" to Quit Game" << endl;
				cout << "-----------------------------" << endl;
				cout << "Input: ";
				cin >> userSelect;
				if (userSelect == 1) {
					selected = true;
					ifstream file_in(defaultFenPath);
					if (file_in.is_open()) {
						file_in.getline(currentFen, MAX_FEN);
						file_in.close();

						cout << endl << "Your loaded Fen: " << currentFen <<endl << endl;
						selected = true;
					}
					else {
						cout << "Error: Unable to open file" << endl;
						cout << "Start again from the beginning." << endl;
						selected = false;
					}
				}
				else if (userSelect == 2) {
					cout << "Please input path for FEN notation (e.g, gamefiles/test1.txt or gamefiles/test2.txt" << endl << endl;
					const int MAX_SIZE = 100;
					char filePath[MAX_SIZE];

					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "File path: ";
					cin.getline(filePath, MAX_SIZE);

					ifstream file_in(filePath);
					if (file_in.is_open()) {
						file_in.getline(currentFen, MAX_FEN);
						file_in.close();

						cout << endl << "Your loaded Fen: " << currentFen << endl << endl;
						selected = true;
					}
					else {
						cout << "Error: Unable to open file" << endl;
						cout << "Start again from the beginning." << endl;
						selected = false;
					}
				}
				else if (userSelect == 3) {
					selected = true;
					menu = false;
					gameRunning = false;
					Mix_FreeChunk(dieA);
					Mix_FreeChunk(moveA);
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					SDL_Quit();
					return 0;
				}
				else {
					cout << "INVALID INPUT" << endl;
					selected = false;
				}
			}
			cout << "Press Enter in the main window to start the game :D" << endl << endl;

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
		
		// Chess State: Chess game is on going
		// Game goes on untill checkmate happens
		if (chessStarted) {
			initChessGame(renderer);
		}
		while(chessStarted){
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					chessStarted = false;
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

		// Checkmate State: Displays Game Over screen untill
		// Player Presses "Enter" to go back to the menu
		if (checkmate) {
			cout << "-----------------------------" << endl;
			cout << "Press Enter to go back to Menu" << endl;
			cout << "-----------------------------" << endl;
		}
		while (checkmate) {

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
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
						Board::destroyLeftPieces();
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

	}
	appDeconstructor(renderer, window);
	
	return 0;
}
