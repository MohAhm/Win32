#include <windows.h>
#include "resource.h"
#include "wrapper.h"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hDlgModeless = NULL;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) 
{
	HWND hWnd;
	MSG msg;

	hWnd = windowCreate(hPrevInstance, hInstance, nCmdShow, "Main Window", MainWndProc, COLOR_WINDOW + 1);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!IsDialogMessage(hDlgModeless, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}


LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		// Creating a modeless dialog box window
		hDlgModeless = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);

		if (hDlgModeless != NULL)
		{
			ShowWindow(hDlgModeless, SW_SHOW);
		}
		else
		{
			MessageBox(hWnd, "CreateDialog returned NULL", "Warning!",
				MB_OK | MB_ICONINFORMATION);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}

	return 0;
}


INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
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
	}

	return (INT_PTR)FALSE;
}
