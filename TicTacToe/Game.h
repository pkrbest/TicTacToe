#ifndef _GAME_H_TICTACTOE
#define _GAME_H_TICTACTOE

enum choice {NONE, X, O};

class Game{
public:
	choice* box;
	choice player;

	// Constructors
	Game::Game();
	Game::Game(const Game& G1);

	// Destructor
	Game::~Game();
	
	// Functions
	void ClearBoard();
	int PushMove(choice c, int move);
	bool ValidMove(int move);
	choice Winner();
	int FindWinStartEnd(int& a, int& b);
	int Score(int depth);
	bool HouseFull();
	int NumberOfMoves();
	int FindAllMoves(int* moves, int num_moves);
	void FlipPlayer();
	int FindMaxScoreIndex(int* scores, int num_moves);
	int FindMinScoreIndex(int* scores, int num_moves);

	int Minimax(int depth, int& move);
	void PlayFirstMove();
	choice PlayNextMove();
	void StartAndEndIndexOfWinner(choice c, int& start, int& end);
};

#endif