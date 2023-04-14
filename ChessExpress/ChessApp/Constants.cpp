#include "Constants.h"

int SCREEN_WIDTH = 900;
int SCREEN_HEIGHT = 720;

int gameTileSize;
bool isDragging = false;
SDL_Rect mouseRect = {};
//visit this later
Piece* clickedPiece = new Pawn(NULL, NULL, NULL, NULL);

const char* pieceImagePaths[][2] = {
	{ "assets/P.bmp", "assets/bP.bmp" },
	{ "assets/K.bmp", "assets/bK.bmp" },
	{ "assets/Q.bmp", "assets/bQ.bmp" },
	{ "assets/B.bmp", "assets/bB.bmp" },
	{ "assets/R.bmp", "assets/bR.bmp" },
	{ "assets/N.bmp", "assets/bN.bmp" }
};

const char blackTurnPath[] = "assets/BLACK.bmp";
const char whiteTurnPath[] = "assets/WHITE.bmp";
SDL_Texture* blackTurnTexture = {};
SDL_Texture* whiteTurnTexture = {};

const char* numPaths[boardSize]{ 
	"assets/tile8.bmp",
	"assets/tile7.bmp",
	"assets/tile6.bmp",
	"assets/tile5.bmp",
	"assets/tile4.bmp",
	"assets/tile3.bmp",
	"assets/tile2.bmp",
	"assets/tilea1.bmp",

};
const char* letterPaths[boardSize]{
	"assets/tilea1.bmp",
	"assets/tileb.bmp",
	"assets/tilec.bmp",
	"assets/tiled.bmp",
	"assets/tilee.bmp",
	"assets/tilef.bmp",
	"assets/tileg.bmp",
	"assets/tileh.bmp",
};


SDL_Rect boardTiles[boardSize][boardSize];

SDL_Rect statusTile = {};

Piece* piecesOnBoard[boardSize][boardSize];

Piece* whiteKing = new King(NULL, NULL, NULL, NULL);

Piece* blackKing = new King(NULL, NULL, NULL, NULL);


SDL_Texture* letterTextures[boardSize];
SDL_Texture* numTextures[boardSize];

const char titleImagePath[] = "assets/ChessXpress.bmp";
const char pressEnterImagePath[] = "assets/pressEnter.bmp";

const char startingFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char currentFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char piecePlacement[64] = { 0 };
char playerTurn = '-';
char castlingAbility[5] = { 0 };
char enPassantTarget[3] = { 0 };
char halfmoveClock[3] = { 0 };
char fullmoveClock[7] = { 0 };


const char* chessExpressASCII = R"(                                                                          
                                                                           
  ,----..    ,---,                                                         
 /   /   \ ,--.' |                                                         
|   :     :|  |  :                                                         
.   |  ;. /:  :  :                .--.--.    .--.--.                       
.   ; /--` :  |  |,--.   ,---.   /  /    '  /  /    '                      
;   | ;    |  :  '   |  /     \ |  :  /`./ |  :  /`./                      
|   : |    |  |   /' : /    /  ||  :  ;_   |  :  ;_                        
.   | '___ '  :  | | |.    ' / | \  \    `. \  \    `.                     
'   ; : .'||  |  ' | :'   ;   /|  `----.   \ `----.   \                    
'   | '/  :|  :  :_:,''   |  / | /  /`--'  //  /`--'  /                    
|   :    / |  | ,'    |   :    |'--'.     /'--'.     /                     
 \   \ .'  `--''       \   \  /   `--'---'   `--'---'                      
  `---`                 `----'                                             
                       ,-.----.                                            
 ,--,     ,--,         \    /  \                                           
 |'. \   / .`|         |   :    \                                          
 ; \ `\ /' / ;   ,---,.|   |  .\ :  __  ,-.                                
 `. \  /  / .' ,'  .' |.   :  |: |,' ,'/ /|          .--.--.    .--.--.    
  \  \/  / ./,---.'   ,|   |   \ :'  | |' | ,---.   /  /    '  /  /    '   
   \  \.'  / |   |    ||   : .   /|  |   ,'/     \ |  :  /`./ |  :  /`./   
    \  ;  ;  :   :  .' ;   | |`-' '  :  / /    /  ||  :  ;_   |  :  ;_     
   / \  \  \ :   |.'   |   | ;    |  | ' .    ' / | \  \    `. \  \    `.  
  ;  /\  \  \`---'     :   ' |    ;  : | '   ;   /|  `----.   \ `----.   \ 
./__;  \  ;  \         :   : :    |  , ; '   |  / | /  /`--'  //  /`--'  / 
|   : / \  \  ;        |   | :     ---'  |   :    |'--'.     /'--'.     /  
;   |/   \  ' |        `---'.|            \   \  /   `--'---'   `--'---'   
`---'     `--`           `---`             `----'                          )";

const char* lethiweMwendwaASCII = R"(
                      _           _   _                                               
                     | |         | | | |                                              
   ___ _ __ ___  __ _| |_ ___  __| | | |__  _   _                                     
  / __| '__/ _ \/ _` | __/ _ \/ _` | | '_ \| | | |                                    
 | (__| | |  __/ (_| | ||  __/ (_| | | |_) | |_| |                                    
  \___|_|  \___|\__,_|\__\___|\__,_| |_.__/ \__, |                                    
                                             __/ |                                    
  _          _   _     _                __  |___/                     _               
 | |        | | | |   (_)              |  \/  |                      | |              
 | |     ___| |_| |__  ___      _____  | \  / |_      _____ _ __   __| |_      ____ _ 
 | |    / _ \ __| '_ \| \ \ /\ / / _ \ | |\/| \ \ /\ / / _ \ '_ \ / _` \ \ /\ / / _` |
 | |___|  __/ |_| | | | |\ V  V /  __/ | |  | |\ V  V /  __/ | | | (_| |\ V  V / (_| |
 |______\___|\__|_| |_|_| \_/\_/ \___| |_|  |_| \_/\_/ \___|_| |_|\__,_| \_/\_/ \__,_|
                                                                                      
)";

