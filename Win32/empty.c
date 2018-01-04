#include <windows.h>
#include "resource.h"

INT_PTR CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hDlgModeless;
	MSG msg;

	// Creating a modeless dialog box window
	hDlgModeless = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, MainDlgProc);

	ShowWindow(hDlgModeless, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (hDlgModeless == 0 || !IsDialogMessage(hDlgModeless, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}


INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
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





