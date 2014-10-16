#include "stdafx.h"
#include "API Functions.h"
#include "Game.h"

extern Game FirstGame;

// Function to draw Grid for the
// Game of Tic Tac Toe
void DrawGrid(HDC& hdc)
{
	HPEN hPenOld;

	// draw  a TicTacToe Grid
	HPEN hPenRed;
	COLORREF qLineColor;
	qLineColor = RGB(0, 0, 250);
	hPenRed = CreatePen(PS_SOLID, 5, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hPenRed);

	MoveToEx(hdc, 110, 10, NULL);
	LineTo(hdc, 110, 310);

	MoveToEx(hdc, 10, 110, NULL);
	LineTo(hdc, 310, 110);

	MoveToEx(hdc, 10, 210, NULL);
	LineTo(hdc, 310, 210);

	MoveToEx(hdc, 210, 10, NULL);
	LineTo(hdc, 210, 310);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPenRed);
}

// Function to draw the end line from box a to box b
void DrawLine(HDC& hdc, int a, int b)
{
	HPEN hPenOld;

	// draw  an end line
	HPEN hPenRed;
	COLORREF qLineColor;
	qLineColor = RGB(0, 250, 260);
	hPenRed = CreatePen(PS_SOLID, 3, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hPenRed);

	int start1, end1, start2, end2;

	switch (a)
	{
	case 0:
		if (b == 2){
			start1 = 20;
			end1 = 60;
			start2 = 210 + 90;
			end2 = 60;
		}
		else if (b == 6){
			start1 = 60;
			end1 = 20;
			start2 = 60;
			end2 = 210 + 90;
		}
		else {
			start1 = 20;
			end1 = 20;
			start2 = 210 + 90;
			end2 = 210 + 90;
		}
		break;
	case 1:
		start1 = 110 + 50;
		end1 = 20;
		start2 = 110 + 50;
		end2 = 210 + 90;
		break;
	case 2:
		if (b == 6){
			start1 = 210 + 90;
			end1 = 20;
			start2 = 20;
			end2 = 210 + 90;
		} 
		else
		{
			start1 = 210 + 50;
			end1 = 20;
			start2 = 210 + 50;
			end2 = 210 + 90;
		}
		break;
	case 3:
		start1 = 20;
		end1 = 110 + 50;
		start2 = 210 + 90;
		end2 = 110 + 50;
		break;
	case 5:
		start1 = 210 + 90;
		end1 = 110 + 50;
		start2 = 20;
		end2 = 110 + 50;
		break;
	case 6:
		if (b == 0){
			start1 = 60;
			end1 = 210 + 90;
			start2 = 60;
			end2 = 20;
		}
		else if (b == 8)
		{
			start1 = 20;
			end1 = 210 + 50;
			start2 = 210 + 90;
			end2 = 210 + 50;
		}
		else {
			start1 = 20;
			end1 = 210 + 90;
			start2 = 210 + 90;
			end2 = 20;
		}
		break;
	case 7:
		start1 = 110 + 50;
		end1 = 210 + 90;
		start2 = 110 + 50;
		end2 = 20;
		break;
	case 8:
		if (b == 0){
			start1 = 210 + 90;
			end1 = 210 + 90;
			start2 = 20;
			end2 = 20;
		}
		else {
			start1 = 210 + 50;
			end1 = 210 + 90;
			start2 = 210 + 50;
			end2 = 20;
		}
		break;
	default:
		start1 = 0;
		end1 = 0;
		start2 = 0;
		end2 = 0;
		break;
	}

	MoveToEx(hdc, start1, end1, NULL);
	LineTo(hdc, start2, end2);


	SelectObject(hdc, hPenOld);
	DeleteObject(hPenRed);
}

// Function to draw the Tic Tac Toe in the board
void DrawTicTacToe(HDC& hdc)
{
	for (int i = 0; i < 9; ++i)
	{
		switch (FirstGame.box[i]){
		case X:
			Draw(X, hdc, i);
			break;
		case O:
			Draw(O, hdc, i);
			break;
		default:
			break;
		}		
	}

	if (FirstGame.Winner() != NONE){
		int a, b;
		int status = FirstGame.FindWinStartEnd(a, b);
		if (status != 0){
			::MessageBox(NULL, _T("Error finding the win"), _T("ERROR"), MB_OK);
		}
		DrawLine(hdc, a, b);
	}
}

// Function to draw the cross in the specified box
void Cross(HDC& hdc, int posX, int posY)
{
	int startxx = posX + 20;
	int startyy = posY + 20;

	int endxx = posX + 80;
	int endyy = posY + 80;

	HPEN hPenOld;

	HPEN hPenRed;
	COLORREF qLineColor;
	qLineColor = RGB(0, 0, 0);
	hPenRed = CreatePen(PS_SOLID, 5, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hPenRed);

	MoveToEx(hdc, startxx, startyy, NULL);
	LineTo(hdc, endxx, endyy);

	MoveToEx(hdc, endxx, startyy, NULL);
	LineTo(hdc, startxx, endyy);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPenRed);
}


// Function to draw the cross in the specified box
void Circle(HDC& hdc, int posX, int posY)
{
	int startxx = posX + 20;
	int startyy = posY + 20;

	int endxx = posX + 80;
	int endyy = posY + 80;

	HPEN hPenOld;

	HPEN hPenRed;
	COLORREF qLineColor;
	qLineColor = RGB(225, 0, 0);
	hPenRed = CreatePen(PS_SOLID, 5, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hPenRed);

	Ellipse(hdc, startxx, startyy, endxx, endyy);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPenRed);
}

void Draw(choice c, HDC& hdc, int i)
{
	int posx, posy;
	switch (i){
	case 0:
		posx = 10;
		posy = 10;
		break;
	case 1:
		posx = 110;
		posy = 10;
		break;
	case 2:
		posx = 210;
		posy = 10;
		break;
	case 3:
		posx = 10;
		posy = 110;
		break;
	case 4:
		posx = 110;
		posy = 110;
		break;
	case 5:
		posx = 210;
		posy = 110;
		break;
	case 6:
		posx = 10;
		posy = 210;
		break;
	case 7:
		posx = 110;
		posy = 210;
		break;
	case 8:
		posx = 210;
		posy = 210;
		break;
	default:
		break;
	}

	switch (c)
	{
	case X:
		Cross(hdc, posx, posy);
		break;
	case O:
		Circle(hdc, posx, posy);
		break;
	default:
		break;
	}
}

// Function to find the position of the mouse click
int FindPosition(const LPARAM& lParam)
{
	int iPosX = LOWORD(lParam);
	int iPosY = HIWORD(lParam);

	int xx = 10;
	int posx(-1);
	int posy(-1);

	for (int i = 0; i < 3; ++i){
		if ((iPosX >= xx) && (iPosX < (xx + 100) )){
			posx = i;
			break;
		}
		xx += 100;
	}

	xx = 10;
	for (int i = 0; i < 3; ++i){
		if ((iPosY >= xx) && (iPosY < (xx + 100))){
			posy = i;
			break;
		}
		xx += 100;
	}

	if (posx > -1 && posy > -1)
		return(posy * 3 + posx);
	else
		return -111;
}

// Function to check if a winner is determined
// returns 0 if no winner
// returns 1 if the player is the winner
// returns -1 if the computer is the winner
// returns 2 if the game is a tie
int GameOver(HWND& hwnd, Game& FirstGame)
{
	if (FirstGame.Winner() == O)
	{
		// Player is the winner
		::MessageBox(hwnd, _T("Congratulations. You win!\nStart a new game?"), _T("Game Over"), MB_OK | MB_ICONEXCLAMATION);
		return 1;
	}
	else if (FirstGame.Winner() == X)
	{
		// The computer is the winner
		::MessageBox(hwnd, _T("Muhahaha! I win!\nStart a new game?"), _T("Game Over"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	else if (FirstGame.HouseFull())
	{
		// Game is a tie
		::MessageBox(hwnd, _T("Its a tie this time.\nStart a new game?"), _T("Game Over"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	else
	{
		// No one has won yet
		return(0);
	}
}


// Function to load a bitmap
bool LoadAndBlitBitmap(LPCWSTR szFilename, HDC hWinDC, int AppWidth, int AppHeight)
{
	// Load the file
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)::LoadImage(NULL, szFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// Verify if the bitmap was loaded
	if (hBitmap == NULL) {
		::MessageBox(NULL, _T("LoadImage Failed."), _T("ERROR"), MB_OK);
		return false;
	}

	// Create a device context that is compatible with the windows
	HDC hLocalDC;
	hLocalDC = ::CreateCompatibleDC(hWinDC);
	// Verify that the device context was successfully created
	if (hLocalDC == NULL) {
		::MessageBox(NULL, _T("CreateCompatibleDC Failed."), _T("ERROR"), MB_OK);
		return false;
	}

	// Select the loaded bitmap with the device context
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hLocalDC, hBitmap);
	if (hOldBitmap == NULL) {
		::MessageBox(NULL, _T("SelectObject Failed."), _T("ERROR"), MB_OK);
		return false;
	}

	// Blit the device context that holds the bitmap to window's device context
	BOOL qRetBlit = ::BitBlt(hWinDC, 0, 0, AppWidth, AppHeight, hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit){
		::MessageBox(NULL, _T("Blit Failed."), _T("ERROR"), MB_OK);
		return false;
	}

	//initialize and deallocate resources
	::SelectObject(hLocalDC, hOldBitmap);
	::DeleteDC(hLocalDC);
	::DeleteObject(hBitmap);
	return true;
}
