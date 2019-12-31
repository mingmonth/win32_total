// 계산기.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "계산기.h"
#include "Windowsx.h"
#include "stdio.h"
#include <string>
#include <iostream>

using namespace std;

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

BOOL lastValueCheck(string s) {
	BOOL bRet = false;
	return bRet;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static string s;
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
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1:	// 0
			//printf("0");
			//s += "0";
			s.append("0");
			break;
		case IDC_BUTTON2:	// C:clear
			printf("C");
			s.clear();
			break;
		case IDC_BUTTON3:	// Enter
			printf("Enter");
			// calc
			break;
		case IDC_BUTTON4:	// 1
			s.append("1");
			break;
		case IDC_BUTTON5:	// 2
			s.append("2");
			break;
		case IDC_BUTTON6:	// 3
			s.append("3");
			break;
		case IDC_BUTTON7:	// 4
			s.append("4");
			break;
		case IDC_BUTTON8:	// 5
			s.append("5");
			break;
		case IDC_BUTTON9:	// 6
			s.append("6");
			break;
		case IDC_BUTTON10:	// +		
			// 빈 문자열인지 검사
			lastValueCheck(s);
			if (!s.empty()) {
				// 마지막 입력 값 검사
				if (!strcmp(&s[s.length() - 1], "+") || !strcmp(&s[s.length() - 1], "-") || !strcmp(&s[s.length() - 1], "*") || !strcmp(&s[s.length() - 1], "/")) {
					// 기존 연산자 삭제하고 추가
					s.erase(s.length() - 1, 1);
					s.append("+");
				}
				else {
					s.append("+");
				}
			}			
			
			break;
		case IDC_BUTTON11:	// 7
			s.append("7");
			break;
		case IDC_BUTTON12:	// 8
			s.append("8");
			break;
		case IDC_BUTTON13:	// 9
			s.append("9");
			break;
		case IDC_BUTTON14:	// Back
			printf("Back");
			break;
		case IDC_BUTTON15:	// /
			if (!s.empty()) {
				if (!strcmp(&s[s.length() - 1], "+") || !strcmp(&s[s.length() - 1], "-") || !strcmp(&s[s.length() - 1], "*") || !strcmp(&s[s.length() - 1], "/")) {
					// 기존 연산자 삭제하고 추가
					s.erase(s.length() - 1, 1);
					s.append("/");
				}
				else {
					s.append("/");
				}
			}
			
			break;
		case IDC_BUTTON16:	// *
			if (!s.empty()) {
				if (!strcmp(&s[s.length() - 1], "+") || !strcmp(&s[s.length() - 1], "-") || !strcmp(&s[s.length() - 1], "*") || !strcmp(&s[s.length() - 1], "/")) {
					// 기존 연산자 삭제하고 추가
					s.erase(s.length() - 1, 1);
					s.append("*");
				}
				else {
					s.append("*");
				}
			}			
			break;
		case IDC_BUTTON17:	// -
			if (!s.empty()) {
				if (!strcmp(&s[s.length() - 1], "+") || !strcmp(&s[s.length() - 1], "-") || !strcmp(&s[s.length() - 1], "*") || !strcmp(&s[s.length() - 1], "/")) {
					// 기존 연산자 삭제하고 추가
					s.erase(s.length() - 1, 1);
					s.append("-");
				}
				else {
					s.append("-");
				}
			}			
			break;
		}
		cout << s << endl;
        break;
	case WM_CLOSE:
		FreeConsole();
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		break;
    }

    return (INT_PTR)FALSE;
}
