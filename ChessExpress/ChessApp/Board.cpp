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

			tileWidthInc += tileSize;
		}
		tileHeightInc += tileSize;

	}
	//cout << endl << " Tile*8: " << tileSize * 8 << " Width: " << width << " Height: " << height;

	gameTileSize = tileSize;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
};

/*
void Board::drawBoard2(SDL_Renderer* renderer, float width, float height, Piece* selectedPiece) {
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

			tileWidthInc += tileSize;
			if (piecesOnBoard[i][j]) {
				if (selectedPiece) {
					if (not(selectedPiece == piecesOnBoard[i][j])) {
						piecesOnBoard[i][j]->drawPeice2(renderer, i,j);
					}
				}
				else {
					piecesOnBoard[i][j]->drawPeice2(renderer, i,j);
				}
			}
		}
		tileHeightInc += tileSize;

	}
	//cout << endl << " Tile*8: " << tileSize * 8 << " Width: " << width << " Height: " << height;

	gameTileSize = tileSize;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
};
*/

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

void Board::pieceDisplay(SDL_Renderer* renderer, Piece* selectedPiece)
{
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (piecesOnBoard[i][j] && (selectedPiece != piecesOnBoard[i][j])) {
				piecesOnBoard[i][j]->drawPeice2(renderer, boardTiles[i][j]);
				
			}
		}
	}
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
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | ROOK);
				//Piece blackRook = { renderer, BLACK | ROOK , currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &blackRook;

				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, BLACK | ROOK, currentRow, currentColumn);



			}
				break;

			case('n'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | KNIGHT);
				//Piece blackKnight = { renderer, BLACK | KNIGHT, currentRow, currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &blackKnight;

				//cout << "piecesOnBoard one: " << piecesOnBoard[currentRow][currentColumn]->pieceType << endl;

				//cout << "blackKnight one: " << blackKnight.pieceType << endl;

				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, BLACK | KNIGHT, currentRow, currentColumn);
			}
				break;
			case('b'):
				
			{	
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | BISHOP);
				//Piece blackBishop = { renderer, BLACK + BISHOP, currentRow,currentColumn }; 
				//piecesOnBoard[currentRow][currentColumn] = &blackBishop;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, BLACK + BISHOP, currentRow, currentColumn);
			}
				break;
			case('q'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | QUEEN);
				//Piece blackQueen = { renderer, BLACK + QUEEN, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &blackQueen;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, BLACK + QUEEN, currentRow, currentColumn);
			}
				break;
			case('k'): 
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | KING);
				//Piece blackKing = { renderer, BLACK + KING, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &blackKing;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, BLACK + KING, currentRow, currentColumn);
			}
				break;
			case('p'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | PAWN);
				//Piece blackPawn = { renderer, BLACK + PAWN, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &blackPawn;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, BLACK + PAWN, currentRow, currentColumn);
			}
				break;
			case('R'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | ROOK);
				//Piece whiteRook = { renderer, WHITE + ROOK, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &whiteRook;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, WHITE + ROOK, currentRow, currentColumn);
			}
				break;
			case('N'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | KNIGHT);
				//Piece whiteKnight = { renderer, WHITE + KNIGHT, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &whiteKnight;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, WHITE + KNIGHT, currentRow, currentColumn);
			}
				break;
			case('B'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | BISHOP);
				//Piece whiteBishop = { renderer, WHITE + BISHOP, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &whiteBishop;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, WHITE + BISHOP, currentRow, currentColumn);
			}
				break;
			case('Q'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | QUEEN);
				//Piece whiteQueen = { renderer, WHITE + QUEEN, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &whiteQueen;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, WHITE + QUEEN, currentRow, currentColumn);
			}
				break;
			case('K'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | KING);
				//Piece whiteKing = { renderer, WHITE + KING, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &whiteKing;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, WHITE + KING, currentRow, currentColumn);
			}
				break;
			case('P'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | PAWN);
				//Piece whitePawn = { renderer, WHITE + PAWN, currentRow,currentColumn };
				//piecesOnBoard[currentRow][currentColumn] = &whitePawn;
				piecesOnBoard[currentRow][currentColumn] = new Piece(renderer, WHITE + PAWN, currentRow, currentColumn);
			}
				break;
			}
			currentColumn += 1;
		}
		
	}

}



//bool Board::castleAbility()