#include <windows.h>
#include <stdio.h>
#include "resource.h"


INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) 
{
	MSG msg;
	BOOL bRet;
	HWND hWndDlg;


	hWndDlg = CreateDialogA(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	if (hWndDlg != NULL)
	{
		ShowWindow(hWndDlg, SW_SHOW);
	}
	else
	{
		MessageBox(NULL, "CreateDialog returned NULL", "Warning!",
			MB_OK | MB_ICONINFORMATION);
	}

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


// Dialog box procedure
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	BOOL fError;
	int iLine;
	char buffer[1024];

	switch (msg)
	{
	case WM_INITDIALOG:
		// Initialize the controls 
		SetDlgItemInt(hDlg, IDC_EDIT1, 0, FALSE);

		// Set the input focus
		if (GetDlgCtrlID((HWND)wParam) != ID_INCREM)
		{
			SetFocus(GetDlgItem(hDlg, ID_INCREM));
			return FALSE;
		}
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DestroyWindow(hDlg);
			return (INT_PTR)TRUE;
			break;
		case ID_INCREM:
			//MessageBox(hDlg, "It works man?\n", "A cool Mbox", MB_OK);
			
			iLine = GetDlgItemInt(hDlg, IDC_EDIT1, &fError, FALSE);

			SetDlgItemInt(hDlg, IDC_EDIT1, iLine+1, FALSE);

			return (INT_PTR)TRUE;
			break;
		case ID_VALUE:
			iLine = GetDlgItemInt(hDlg, IDC_EDIT1, &fError, FALSE);
			sprintf(buffer, "Value: %d", iLine);

			MessageBox(hDlg, buffer, "EditBox Value", MB_OK);

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
