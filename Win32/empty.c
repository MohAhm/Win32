#include <windows.h>
#include "resource.h"

INT_PTR CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) 
{
	HWND hWndDlg;
	MSG msg;

	// Creating a modeless dialog box window
	hWndDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
	if (hWndDlg == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hWndDlg, nCmdShow);
	UpdateWindow(hWndDlg);

	/* (the message processing loop that all windows applications must have) */
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


INT_PTR CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
					break;
				case IDCANCEL:
					DestroyWindow(hDlg);
					return (INT_PTR)TRUE;
					break;
				case ID_NY_KNAPP:
					MessageBox(NULL, "It works man?\n", "A cool Mbox", 0);
					return (INT_PTR)TRUE;
					break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
			break;
		default:
			return(DefWindowProc(hDlg, msg, wParam, lParam));
	}

	return (INT_PTR)FALSE;
}
