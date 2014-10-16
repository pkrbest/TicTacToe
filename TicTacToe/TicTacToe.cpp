// TicTacToe.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TicTacToe.h"
#include "Game.h"
#include "API Functions.h"

#define MAX_LOADSTRING 100

bool NewGame(false);
HBITMAP bitmap;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
Game FirstGame;                                 // The Tic Tac Toe Game
int AppWidth = 340;
int AppHeight = 380;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32LESSON1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32LESSON1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32LESSON1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	int x = (ScreenX / 2) - (AppWidth / 2);
	int y = (ScreenY / 2) - (AppHeight / 2);
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 
		x, y, AppWidth, AppHeight, NULL, NULL, hInstance, NULL);
	//SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	   
	   
	   //szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      // CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int msgID;

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		// Set the cursor to busy
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		ShowCursor(true);

		int box = FindPosition(lParam);
		if (box == -111) break; // Incorrect placement (outside the board)
		int status = FirstGame.PushMove(O, box);
		if (status == -1)
		{
			::MessageBox(hWnd, _T("Incorrect placement"), _T("ERROR"), MB_OK | MB_ICONERROR);
			ShowCursor(false);
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			break;
		}
		else
		{
			InvalidateRect(hWnd, 0, TRUE);
			int game_status = GameOver(hWnd, FirstGame);
			if (game_status != 0)
			{
				// If the game is over, clear the board and begin new board
				NewGame = true;
				FirstGame.ClearBoard();
				InvalidateRect(hWnd, 0, TRUE);
				ShowCursor(false);
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				break;
			}
			else 
			{
				choice c = FirstGame.PlayNextMove();
				InvalidateRect(hWnd, 0, TRUE);
				game_status = GameOver(hWnd, FirstGame);
				if (game_status != 0)
				{
					// If the game is over, clear the board and begin new board
					NewGame = true;
					FirstGame.ClearBoard();
					InvalidateRect(hWnd, 0, TRUE);
					ShowCursor(false);
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					break;
				}
			}
		}
		ShowCursor(false);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		break;
	}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			msgID = ::MessageBox(hWnd, _T("Are you sure you want to exit?"), _T("Exit?"), MB_OKCANCEL);
			if (msgID == IDOK){
				DestroyWindow(hWnd);
			}
			break;
		case IDM_NEW:
			msgID = ::MessageBox(hWnd, _T("Begin a new Game?"), _T("New Game?"), MB_YESNO);
			if (msgID == IDYES){
				NewGame = true;
				FirstGame.ClearBoard();
				InvalidateRect(hWnd, 0, TRUE);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		if (NewGame){
			DrawGrid(hdc);
		//	FirstGame.PlayFirstMove();
			DrawTicTacToe(hdc);
		}
		else
		{
			//LoadAndBlitBitmap(_T("Icon/TicTacToeMain.bmp"), hdc, AppWidth, AppHeight);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
