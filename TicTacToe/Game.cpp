#include "stdafx.h"
#include "Game.h"

// #include<stdlib.h>
// #include<time.h>

// Constructors
Game::Game(){
	box = new choice [9];
	for (int i = 0; i < 9; ++i) box[i] = NONE;
	player = X;
}


// Copy Constructor
Game::Game(const Game& G1)
{
	box = new choice [9];
	for (int i = 0; i < 9; ++i) box[i] = G1.box[i];
	player = G1.player;
}

// Destructor
Game::~Game()
{
	delete[] box; box = nullptr;
	player = NONE;
}

// Function to clear the board for the new game
void Game::ClearBoard()
{
	for (int i = 0; i < 9; ++i) box[i] = NONE;
	player = X;
}

// Function to check if a move is valid
bool Game::ValidMove(int move)
{
	if (box[move] == NONE) return true;
	else return false;
}

// Function to push a move to the board
int Game::PushMove(choice c, int move)
{
	if (move < 0) return -2; // return signifying out of bounds
	if (!ValidMove(move)) return -1; // return signifying failure
	box[move] = c;
	return (0);  // return signifying success
}

// Function to check if the board is full
bool Game::HouseFull()
{
	for (int i = 0; i < 9; ++i)
		if (box[i] == NONE) return false;

	return true;
}

// Function to check if the Game is over
choice Game::Winner()
{
	if (((box[0] == box[1]) && (box[1] == box[2]) && (box[0] == X)) ||
		((box[3] == box[4]) && (box[4] == box[5]) && (box[3] == X)) ||
		((box[6] == box[7]) && (box[7] == box[8]) && (box[6] == X)) ||		
		((box[0] == box[3]) && (box[3] == box[6]) && (box[6] == X)) ||
		((box[1] == box[4]) && (box[4] == box[7]) && (box[7] == X)) ||
		((box[2] == box[5]) && (box[5] == box[8]) && (box[8] == X)) ||
		((box[0] == box[4]) && (box[4] == box[8]) && (box[0] == X)) ||
		((box[2] == box[4]) && (box[4] == box[6]) && (box[2] == X))) {
		return X;
	}

	if (((box[0] == box[1]) && (box[1] == box[2]) && (box[0] == O)) ||
		((box[3] == box[4]) && (box[4] == box[5]) && (box[3] == O)) ||
		((box[6] == box[7]) && (box[7] == box[8]) && (box[6] == O)) ||
		((box[0] == box[3]) && (box[3] == box[6]) && (box[6] == O)) ||
		((box[1] == box[4]) && (box[4] == box[7]) && (box[7] == O)) ||
		((box[2] == box[5]) && (box[5] == box[8]) && (box[8] == O)) ||
		((box[0] == box[4]) && (box[4] == box[8]) && (box[0] == O)) ||
		((box[2] == box[4]) && (box[4] == box[6]) && (box[2] == O))) {
		return O;
	}

	else return NONE;
}

// Function to find the winning start and end position
int Game::FindWinStartEnd(int& a, int& b)
{	
	choice win = Winner();
	if (win == NONE) return -1;
	int row = 0;

	for (int i = 0; i < 3; ++i)
	{
		if ((box[i] == win) && (box[i] == box[i + 3]) && (box[i] == box[i + 6])){
			a = i;
			b = i + 6;
			return 0;
		}
		if ((box[row] == win) && (box[row] == box[row + 1]) && (box[row] == box[row + 2])){
			a = row;
			b = row + 2;
			return 0;
		}
		row = row + 3;
	}

	if ((box[0] == box[4]) && (box[4] == box[8]) && (box[0] == win)){
		a = 0; b = 8;
		return 0;
	}
	else if ((box[2] == box[4]) && (box[4] == box[6]) && (box[2] == win)){
		a = 2; b = 6;
		return 0;
	}
	else {
		return 1;
	}
}

// Function to count the number of steps left
int Game::NumberOfMoves()
{
	int steps(0);
	for (int i = 0; i < 9; ++i)
		if (box[i] == NONE) ++steps;

	return steps;
}

// Function to calculate the score for the given depth
int Game::Score(int depth)
{
	if (Winner() == X) return 10 - depth;
	if (Winner() == O) return depth - 10;
	return 0;
}

int Game::FindAllMoves(int* moves, int num_moves)
{
	int xx = 0;
	for (int i = 0; i < 9; ++i)
		if (box[i] == NONE){
			moves[xx] = i;
			++xx;
		}

	if (xx != num_moves) return -1;
	else return 0;
}

// Function to flip the player of the game
void Game::FlipPlayer()
{
	switch (player)
	{
	case X:
		player = O;
		break;
	case O:
		player = X;
		break;
	default:
		player = NONE;
		break;
	}
}

// Function for the Minimax algorthm for the game
int Game::Minimax(int depth, int& SelectedMove)
{
	// Check to see if the winner is determined already
	if (HouseFull() || (Winner() != NONE)) return Score(depth);
	++depth;

	int num_moves = NumberOfMoves();
	int *scores, *moves;
	
	scores = new int[num_moves];
	moves = new int[num_moves];

	int status = FindAllMoves(moves, num_moves);
	if (status != 0){
		::MessageBox(NULL, _T("Minimax Function cannot find all moves correctly"), _T("Error"), MB_OK | MB_ICONERROR);
		return (-11111);
	}

	for (int i = 0; i < num_moves; ++i)
	{
		Game NewGame(*this);

		// Push the new move to the new game
		status = NewGame.PushMove(NewGame.player, moves[i]);
		if (status != 0){
			::MessageBox(NULL, _T("Minimax Function cannot push the moves correctly"), _T("Error"), MB_OK | MB_ICONERROR);
			return (-11111);
		}
		// Use the Minimax algorithm again to find the score

		// Change the player for the new game
		NewGame.FlipPlayer();

		wchar_t code1[50];

		int temp_c;
		scores[i] = NewGame.Minimax(depth, temp_c);
	}

	int index, minmax_score;
	// Find Max or Min Score based on the player
	if (player == X) index = FindMaxScoreIndex(scores, num_moves);
	if (player == O) index = FindMinScoreIndex(scores, num_moves);

	SelectedMove = moves[index];
	minmax_score = scores[index];
	
	delete[] scores;
	delete[] moves;

	return (minmax_score);
}


int Game::FindMaxScoreIndex(int* scores, int num_moves)
{
	int tmp_max(-1111);
	int index;

	for (int i = 0; i < num_moves; ++i)
		if (scores[i] > tmp_max){
		tmp_max = scores[i];
		index = i;
		}

	return index;
}

int Game::FindMinScoreIndex(int* scores, int num_moves)
{
	int tmp_min(11111);
	int index;

	for (int i = 0; i < num_moves; ++i)
		if (scores[i] < tmp_min){
		tmp_min = scores[i];
		index = i;
		}

	return index;
}

// A function to automatically play the first move
void Game::PlayFirstMove()
{
	/*
	player = X;

	// Generate a Random Number between 1 - 5
	int randNum;
	srand((int)(time(NULL)));

	//srand(time(NULL));
	randNum = rand() % 5 + 1;

	int move;
	switch (randNum)
	{
	case 1:
		move = 0;
		break;
	case 2:
		move = 2;
		break;
	case 3:
		move = 4;
		break;
	case 4:
		move = 6;
		break;
	case 5:
		move = 8;
		break;
	default:
		move = 4;
		break;
	}

	PushMove(player, move);
	FlipPlayer();
	*/
}

// Function to play the next move
choice Game::PlayNextMove()
{

	if (player == O) FlipPlayer();
	if (Winner() == O){
		::MessageBox(NULL, _T("Winner = O"), _T(""), MB_OK);
		return O;
	}
	if (HouseFull()){
		::MessageBox(NULL, _T("Housefull"), _T(""), MB_OK);
		return O;
		return NONE;
	}

	int move;
	int score = Minimax(0, move);
	if (score == -11111){
			::MessageBox(NULL, _T("Minimax Function is not executing correctly"), _T("Error"), MB_OK | MB_ICONERROR);
			return (NONE);
	}

	PushMove(player, move);
	FlipPlayer();
	if (Winner() == X) return X;
	if (HouseFull()) return NONE;
}

// Function to get the start and end index of 
// the winner
void Game::StartAndEndIndexOfWinner(choice c, int& start, int& end)
{ 
	int num_row(0);
	for (int i = 0; i < 3; ++i){
		if ((box[num_row] == c) && (box[num_row + 1] == c) && (box[num_row + 2] == c))
		{
			start = num_row; end = num_row + 2;
			return;
		}
		if ((box[i] == c) && (box[i + 3] == c) && (box[i + 6] == c))
		{
			start = i; end = i + 2;
			return;
		}
		num_row += 3;
	}
	
	if ((box[0] == box[4]) && (box[4] == box[8]) && (box[8] == c)){
		start = 0; end = 8;
		return;
	}
	if ((box[2] == box[4]) && (box[4] == box[6]) && (box[6] == c)){
		start = 0; end = 6;
		return;
	}
}

