// test03.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HWND hList;
	char *strMenu[] = { "순번", "C  ", "C++", "Win32" };
	LVCOLUMN lvColumn;
	LVITEM lvItem;
	char string[100];
	static int nIndex = -1;
	switch (message)
	{
	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == NM_CLICK) {
			// 아이템 인덱스 알아내기
			nIndex = ListView_GetNextItem(hList, -1, LVNI_SELECTED);
			// 서브 아이템 데이터 가져오기
			ListView_GetItemText(hList, nIndex, 1, string, 10);
			// 에디트 컨트롤에 내용 설정
			SetDlgItemText(hDlg, IDC_EDIT1, string);
			ListView_GetItemText(hList, nIndex, 2, string, 10);
			SetDlgItemText(hDlg, IDC_EDIT2, string);
			ListView_GetItemText(hList, nIndex, 3, string, 10);
			SetDlgItemText(hDlg, IDC_EDIT3, string);			
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		break;
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST1);
		// 리스트 뷰 스타일 설정
		ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;
		for (int i = 0; i < 4; i++) {
			lvColumn.cx = strlen(strMenu[i]) * 15;
			lvColumn.pszText = strMenu[i];
			ListView_InsertColumn(hList, i, &lvColumn);
		}
        return (INT_PTR)TRUE;

    case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1) {	// 입력
			lvItem.iItem = ListView_GetItemCount(hList);
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_TEXT;
			sprintf(string, "%d", lvItem.iItem);
			printf("%d\n", lvItem.iItem);
			lvItem.pszText = string;
			// 아이템 생성 및 삽입
			ListView_InsertItem(hList, &lvItem);

			// 에디트 컨트롤에 값 string 으로 가져오기
			GetDlgItemText(hDlg, IDC_EDIT1, string, 10);
			// 서브 아이템에 데이터 저장
			ListView_SetItemText(hList, lvItem.iItem, 1, string);
			GetDlgItemText(hDlg, IDC_EDIT2, string, 10);
			ListView_SetItemText(hList, lvItem.iItem, 2, string);
			GetDlgItemText(hDlg, IDC_EDIT3, string, 10);
			ListView_SetItemText(hList, lvItem.iItem, 3, string);

			// 에디트 컨트롤 내용 클리어
			SetDlgItemText(hDlg, IDC_EDIT1, NULL);
			SetDlgItemText(hDlg, IDC_EDIT2, NULL);
			SetDlgItemText(hDlg, IDC_EDIT3, NULL);

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
