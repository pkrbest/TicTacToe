#ifndef _API_FUNCTIONS
#define _API_FUNCTIONS

#include "Game.h"

// declaration of the API Functions
void DrawGrid(HDC& hdc);
void DrawTicTacToe(HDC& hdc);
void DrawLine(HDC& hdc, int a, int b);
void Cross(HDC& hdc, int posX, int posY);
void Circle(HDC& hdc, int posX, int posY);
void Draw(choice c, HDC& hdc, int i);
int FindPosition(const LPARAM& lparam);
int GameOver(HWND& hwnd, Game& FirstGame);
bool LoadAndBlitBitmap(LPCWSTR szFilename, HDC hWinDC, int AppWidth, int AppHeight);




#endif