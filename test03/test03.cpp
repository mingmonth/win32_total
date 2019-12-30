// test03.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "test03.h"
#include "Windowsx.h"
#include "Commctrl.h"
#include "stdio.h"

#define MAX_LOADSTRING 100

INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);

void init() {
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	init();
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HWND hList;	
	char *strMenu[] = {"�׸�1", "�׸�2", "�׸�3", "�׸�4"};
	LVCOLUMN lvColumn;
	LVITEM lvItem;
	char string[100];
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		break;
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST1);
		lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;
		for (int i = 0; i < 4; i++) {
			lvColumn.cx = strlen(strMenu[i]) * 10;
			lvColumn.pszText = strMenu[i];
			ListView_InsertColumn(hList, i, &lvColumn);
		}
        return (INT_PTR)TRUE;

    case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1) {
			lvItem.iItem = ListView_GetItemCount(hList);
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_TEXT;
			sprintf(string, "%d", lvItem.iItem);
			printf("%d\n", lvItem.iItem);
			lvItem.pszText = string;
			ListView_InsertItem(hList, &lvItem);
			return (INT_PTR)TRUE;
		}
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
			FreeConsole();
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
