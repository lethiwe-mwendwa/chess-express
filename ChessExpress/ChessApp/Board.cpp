#include "Board.h"
#include "Constants.h"
#include <iostream>
using namespace std;


Board::Board()
{
}

void Board::drawBoard(SDL_Renderer* renderer, float width, float height) {
	int tileWidthInc;
	int tileSize;
	int tileHeightInc;
	int widthCord;

	// This part checks the width and height of the screen
	if (height < width) {
		tileSize = round(height) / boardSize;
		tileHeightInc = 0 - round(tileSize * 8 - height) / 2;
		widthCord = round((width - height)) / 2;
		//if (tileSize * 8 < min(width, height) {}

	}
	else {
		tileSize = round(width) / boardSize;
		tileHeightInc = 0 - round(width - height) / 2;
		widthCord = round(width - tileSize * 8) / 2;

	}

	// SDL_SetRenderDrawColor(renderer, 5, 50, 70, 255);
	SDL_SetRenderDrawColor(renderer, 5, 50, 70, 255);
	SDL_RenderClear(renderer);

	for (int i = 0; i < boardSize; i++) {
		tileWidthInc = widthCord;
		for (int j = 0; j < boardSize; j++) {
			//i is the row, j is the column
			//draw square
			if (((i + j) % 2) == 0) {
				SDL_SetRenderDrawColor(renderer, 232, 226, 198, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 30, 129, 176, 255);
			}
			SDL_Rect tile = {};
			tile.x = tileWidthInc;
			tile.y = tileHeightInc;
			tile.h = tileSize;
			tile.w = tileSize;
			
			boardTiles[i][j] = tile;
			SDL_RenderFillRect(renderer, &tile);
			if (j == 0) {
				Board::chessNumDisplay(renderer, i);
			}
			else if (i == 7) {
				Board::chessLetterDisplay(renderer, j);
			}

			tileWidthInc += tileSize;
		}
		tileHeightInc += tileSize;

	}
	//cout << endl << " Tile*8: " << tileSize * 8 << " Width: " << width << " Height: " << height;

	gameTileSize = tileSize;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	// make a function from this.... like... rect resize or something? or rect size? for images.
	if (width > height) {
		statusTile.w = width * 0.4;
		statusTile.h = ((statusTile.w) * 16) / 75;
	}
	else {

		statusTile.h = height * 0.1;
		statusTile.w = ((statusTile.h) * 75) / 16;
	}

	statusTile.x = 0 + (width - statusTile.w) / 2;
	statusTile.y = 0 + (height - statusTile.h) / 2;
};

void Board::changeTurn(SDL_Renderer * renderer) {
	if (playerTurn == 'w') {
		playerTurn = 'b';
	}
	else {
		playerTurn = 'w';
	}
}

void Board::fenSplitter(char fen[]) {
	// fix with meaningful names later
	bool placementDone = false;
	bool turnDone = false;
	bool castlingDone = false;
	bool enPassantDone = false;
	bool halfmoveDone = false;
	int counter = 0;

	for (int i = 0; i < strlen(fen); i++) {

		if (not placementDone) {
			if (fen[i] == ' ') {
				placementDone = true;
				counter = 0;
			}
			else {
				piecePlacement[counter] = fen[i];
				counter += 1;
			}

			
		}
		else if (not turnDone) {
			if (fen[i] == ' ') {
				turnDone = true;
			}
			else {
				playerTurn = fen[i];
			}

		}
		else if (not castlingDone) {
			if (fen[i] == ' ') {
				castlingDone = true;
				counter = 0;
			}
			else {
				castlingAbility[counter] = fen[i];
				counter += 1;
			}
		}
		else if (not enPassantDone) {
			if (fen[i] == ' ') {
				enPassantDone = true;
				counter = 0;
			}
			else {
				enPassantTarget[counter] = fen[i];
				counter += 1;
			}
		}
		else if (not halfmoveDone) {
			if (fen[i] == ' ') {
				halfmoveDone = true;
				counter = 0;
			}
			else {
				halfmoveClock[counter] = fen[i];
				counter += 1;
			}
		}
		else{
			fullmoveClock[counter] = fen[i];
			counter += 1;
		}
	}

}

char Board::getChessCord(int row, int column)
{
	return NULL;
}

void Board::translateChessCord(char chessCord[])
{
}

void Board::pieceDisplay(SDL_Renderer* renderer, Piece* selectedPiece)
{
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (piecesOnBoard[i][j] && (selectedPiece != piecesOnBoard[i][j])) {
				piecesOnBoard[i][j]->drawPiece(renderer, boardTiles[i][j]);
				
			}
		}
	}
}

void Board::initBoardTextures(SDL_Renderer * renderer){

	for (int i = 0; i < boardSize; i++) {

		SDL_Surface* numSurface = SDL_LoadBMP(numPaths[i]);
		SDL_Surface* letterSurface = SDL_LoadBMP(letterPaths[i]);

		if (NULL == numSurface or NULL == letterSurface) {
			cout << "SDL error bozo" << SDL_GetError();
		}

		numTextures[i] = SDL_CreateTextureFromSurface(renderer, numSurface);
		letterTextures[i] = SDL_CreateTextureFromSurface(renderer, letterSurface);
		SDL_FreeSurface(numSurface);
		SDL_FreeSurface(letterSurface);
	}

	SDL_Surface* wTurnSurface = SDL_LoadBMP(whiteTurnPath);
	SDL_Surface* bTurnSurface = SDL_LoadBMP(blackTurnPath);

	
	SDL_Surface* wCheckSurface = SDL_LoadBMP(whiteCheckPath);
	SDL_Surface* bCheckSurface = SDL_LoadBMP(blackCheckPath);

	SDL_Surface* wCheckMateSurface = SDL_LoadBMP(whiteCheckMatePath);
	SDL_Surface* bCheckMateSurface = SDL_LoadBMP(blackCheckMatePath);

	if (NULL == wTurnSurface or NULL == bTurnSurface or NULL == wCheckSurface or 
		NULL == bCheckSurface or NULL == wCheckMateSurface or NULL == bCheckMateSurface) {
		cout << "SDL error bozo" << SDL_GetError();
	}

	whiteTurnTexture = SDL_CreateTextureFromSurface(renderer, wTurnSurface);
	blackTurnTexture = SDL_CreateTextureFromSurface(renderer, bTurnSurface);
	whiteCheckTexture = SDL_CreateTextureFromSurface(renderer, wCheckSurface);
	blackCheckTexture = SDL_CreateTextureFromSurface(renderer, bCheckSurface);
	whiteCheckMateTexture = SDL_CreateTextureFromSurface(renderer, wCheckMateSurface);
	blackCheckMateTexture = SDL_CreateTextureFromSurface(renderer, bCheckMateSurface);

	SDL_FreeSurface(wTurnSurface);
	SDL_FreeSurface(bTurnSurface);
	SDL_FreeSurface(wCheckSurface);
	SDL_FreeSurface(bCheckSurface);
	SDL_FreeSurface(wCheckMateSurface);
	SDL_FreeSurface(bCheckMateSurface);
	
	
}

void Board::chessNumDisplay(SDL_Renderer* renderer, int row){
	//int invertedRow = abs( boardSize - row - 1);
	//cout << numPaths[row] << endl;
	SDL_Texture* numTexture = numTextures[row];
	SDL_RenderCopy(renderer, numTexture, NULL, &boardTiles[row][0]);
}

void Board::chessLetterDisplay(SDL_Renderer* renderer, int column){
	SDL_Texture* letterTexture = letterTextures[column];
	SDL_RenderCopy(renderer, letterTexture, NULL, &boardTiles[7][column]);
}

void Board::fenSetup(SDL_Renderer* renderer, char fen[])
{

	// For the first part of the 
	int currentRow = 0;
	int currentColumn = 0;
	for (int i = 0; i < strlen(fen); i++) {

		if (isdigit(fen[i])) {
			currentColumn = currentColumn + atoi(&fen[i]);
		}
		else if (fen[i] == '/') {
			currentRow += 1;
			currentColumn = 0;
		}
		else if (fen[i] == ' ') {
			return;
		} 
		else {
			switch (fen[i]) {
			case('r'):
			{

				piecesOnBoard[currentRow][currentColumn] = new Rook(renderer, BLACK | ROOK, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();

			}
				break;

			case('n'):
			{
				piecesOnBoard[currentRow][currentColumn] = new Knight(renderer, BLACK | KNIGHT, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('b'):
				
			{	
				piecesOnBoard[currentRow][currentColumn] = new Bishop(renderer, BLACK + BISHOP, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('q'):
			{				
				piecesOnBoard[currentRow][currentColumn] = new Queen(renderer, BLACK + QUEEN, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('k'): 
			{
				piecesOnBoard[currentRow][currentColumn] = new King(renderer, BLACK + KING, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
				blackKing = dynamic_cast<King*>(piecesOnBoard[currentRow][currentColumn]);
				

			}
				break;
			case('p'):
			{
				piecesOnBoard[currentRow][currentColumn] = new Pawn(renderer, BLACK + PAWN, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('R'):
			{
				piecesOnBoard[currentRow][currentColumn] = new Rook(renderer, WHITE + ROOK, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('N'):
			{
				piecesOnBoard[currentRow][currentColumn] = new Knight(renderer, WHITE + KNIGHT, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('B'):
			{
				piecesOnBoard[currentRow][currentColumn] = new Bishop(renderer, WHITE + BISHOP, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('Q'):
			{
				piecesOnBoard[currentRow][currentColumn] = new Queen(renderer, WHITE + QUEEN, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			case('K'):
			{
				piecesOnBoard[currentRow][currentColumn] = new King(renderer, WHITE + KING, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
				whiteKing = dynamic_cast<King*>( piecesOnBoard[currentRow][currentColumn]);
			}
				break;
			case('P'):
			{
				piecesOnBoard[currentRow][currentColumn] = new Pawn(renderer, WHITE + PAWN, currentRow, currentColumn);
				piecesOnBoard[currentRow][currentColumn]->getAttackTiles();
			}
				break;
			}
			currentColumn += 1;
		}
		
	}

}

void Board::refreshAllAttackZones() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (piecesOnBoard[i][j]) {
				piecesOnBoard[i][j]->getAttackTiles();
			}
		}
	}
}

void Board::toFen(){
	int charCount = 0;
	
	for (int i = 0; i < 64; i++) {
		if (piecePlacement[i]) {
			piecePlacement[i] = '\0';
		}
		
	}

	// Traverse the board and build FEN string
	for (int i = 0; i < boardSize; i++) {
		int emptyCount = 0;
		for (int j = 0; j < boardSize; j++) {
			Piece* piece = piecesOnBoard[i][j];
			if (piece) {
				if (emptyCount > 0) {
					piecePlacement[charCount++] += static_cast<char>(emptyCount + '0');
					emptyCount = 0;
				}
				piecePlacement[charCount++] += piece->toFEN();
				
			}
			else {
				emptyCount++;
			}
		}
		if (emptyCount > 0) {
			piecePlacement[charCount++] += static_cast<char>(emptyCount + '0');
		}
		if (i < boardSize - 1) {
			piecePlacement[charCount++] += '/';
		}
	}
}

bool Board::noPiecesCanUncheck(){
	int turn;
	if (playerTurn == 'w') {
		turn = WHITE;
	}
	else {
		turn = BLACK;
	}
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {

			//for every piece, check every spot
			if (piecesOnBoard[i][j]) {

				for (int k = 0; k < boardSize; k++) {
					for (int l = 0; l < boardSize; l++) {
						if ((piecesOnBoard[i][j]->pieceType & COLOUR_MASK) == turn and
							piecesOnBoard[i][j]->moveUnchecks(k, l)) {
							return false;
						}

					}
				}

			}


	
		}
	}
	
	return true;

}

//bool Board::castleAbility()