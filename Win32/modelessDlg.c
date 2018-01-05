#include <windows.h>
#include "resource.h"
#include "wrapper.h"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hWnd = NULL;
HWND hWndDlg = NULL;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) 
{
	MSG msg;
	BOOL bRet;

	hWnd = windowCreate(hPrevInstance, hInstance, nCmdShow, "Main Window", MainWndProc, COLOR_WINDOW + 1);

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// Handle the error and possibly exit
		}
		else if (!IsWindow(hWndDlg) || !IsDialogMessage(hWndDlg, &msg))
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
		// This ensures that the application does not display two dialog boxes at the same time
		if (!IsWindow(hWndDlg))
		{
			// Creating a modeless dialog box window
			hWndDlg = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);

			if (hWndDlg != NULL)
			{
				ShowWindow(hWndDlg, SW_SHOW);
			}
			else
			{
				MessageBox(hWnd, "CreateDialog returned NULL", "Warning!",
					MB_OK | MB_ICONINFORMATION);
			}
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


// Dialog box procedure
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT rc, rcDlg, rcOwner;

	switch (msg)
	{
	case WM_INITDIALOG:
		// Initialize the controls 
		// TODO ...

		// Center a dialog box on the screen ...
		// Get the owner window and dialog box rectangles. 
		if ((hWnd = GetParent(hDlg)) == NULL)
		{
			hWnd = GetDesktopWindow();
		}

		GetWindowRect(hWnd, &rcOwner);
		GetWindowRect(hDlg, &rcDlg);
		CopyRect(&rc, &rcOwner);

		// Offset the owner and dialog box rectangles so that right and bottom 
		// values represent the width and height, and then offset the owner again 
		// to discard space taken up by the dialog box. 
		OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
		OffsetRect(&rc, -rc.left, -rc.top);
		OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

		// The new position is the sum of half the remaining space and the owner's 
		// original position. 
		SetWindowPos(hDlg,
			HWND_TOP,
			rcOwner.left + (rc.right / 2),
			rcOwner.top + (rc.bottom / 2),
			0, 0,          // Ignores size arguments. 
			SWP_NOSIZE);

		// Set the input focus
		if (GetDlgCtrlID((HWND)wParam) != ID_NY_KNAPP)
		{
			SetFocus(GetDlgItem(hDlg, ID_NY_KNAPP));
			return FALSE;
		}
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DestroyWindow(hDlg);
			hWndDlg = NULL;
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
