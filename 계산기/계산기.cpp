// 계산기.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "계산기.h"
#include "Windowsx.h"
#include "Commctrl.h"
#include "stdio.h"
#include "math.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

struct oper {
	int prior;		// 연산자 우선순위
	string op;		// 연산자
};

stack<double> numStack;	// 숫자 스택
stack<oper> opStack;	// 연산자 스택

#define MAX_LOADSTRING 100

INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);
HHOOK hHook { NULL };
static string s;
HWND g_hDlg;

void init() {
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);
}

void close(HWND hDlg, WPARAM wParam) {
	FreeConsole();
	UnhookWindowsHookEx(hHook);
	EndDialog(hDlg, LOWORD(wParam));
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

// nFlag (addOperator: 0, checkString: 1, backSpace: 2, point: 3)
void makeString(string &s, int nFlag, string op) {
	// 빈 문자열인지 검사
	if (!s.empty()) {
		// 문자열이 3보다 커야 마지막 입력 값을 검사 하도록 처리
		if (s.length() > 3) {
			// 마지막 입력 값 검사, 뒤에 공백을 같이 넣어줘야 함.
			if (!strcmp(&s[s.length() - 2], "+ ") || !strcmp(&s[s.length() - 2], "- ") || !strcmp(&s[s.length() - 2], "* ") || !strcmp(&s[s.length() - 2], "/ ")) {
				// 기존 연산자 삭제
				s.erase(s.length() - 3, 3);
				if (nFlag == 0) {	// 연산자 추가
					s.append(" " + op + " ");
				}
			}
			else if (!strcmp(&s[s.length() - 1], ".")) {
				printf("소수점이 이미 찍혀있습니다!");
				if (nFlag == 2) {	// 문자열 하나 지우기
					s.erase(s.length() - 1, 1);
				}
			} else {
				if (nFlag == 0) {	// 연산자 추가
					s.append(" " + op + " ");
				} else if (nFlag == 2) {	// 문자열 하나 지우기
					s.erase(s.length() - 1, 1);
				} else if (nFlag == 3) {
					s.append(op);
				}
			}
		}
		else {
			if (!strcmp(&s[s.length() - 1], ".")) {
				printf("소수점이 이미 찍혀있습니다!");
				if (nFlag == 2) {	// 문자열 하나 지우기
					s.erase(s.length() - 1, 1);
				}
			} else if (nFlag == 0) {	// 연산자 추가
				s.append(" " + op + " ");
			} else if (nFlag == 2) {	// 문자열 하나 지우기
				s.erase(s.length() - 1, 1);
			}
			else if (nFlag == 3) {
				s.append(op);
			}
		}
	}
}

void calculate() {
	double a, b, result;
	b = numStack.top();
	numStack.pop();
	a = numStack.top();
	numStack.pop();
	string oper = opStack.top().op;
	opStack.pop();

	if (oper == "*") {
		result = a * b;
	}
	else if (oper == "/") {
		result = a / b;
	}
	else if (oper == "+") {
		result = a + b;
	}
	else if (oper == "-") {
		result = a - b;
	}
	numStack.push(result);
}

void enterAction(char *result) {
	makeString(s, 1, "");
	printf("Enter\n");
	stringstream ss;
	if (!s.empty()) {
		ss.str(s);
		string tok;
		while (ss >> tok) {
			if (tok == "(") {
				opStack.push({ 0, tok });
			}
			else if (tok == ")") {
				while (opStack.top().op != "(") {
					calculate();
				}
				opStack.pop();
			}
			else if (tok == "*" || tok == "/" || tok == "+" || tok == "-") {
				int prior;	// 연산자 우선순위
				if (tok == "*") {
					prior = 2;
				}
				else if (tok == "/") {
					prior = 2;
				}
				else if (tok == "+") {
					prior = 1;
				}
				else if (tok == "-") {
					prior = 1;
				}

				while (!opStack.empty() && prior <= opStack.top().prior) {
					calculate();
				}
				opStack.push({ prior, tok });
			}
			else {
				numStack.push(stod(tok));
			}
		}

		while (!opStack.empty()) {
			calculate();
		}

		printf("result: %f\n", numStack.top());
		double integer, fraction;
		fraction = modf(numStack.top(), &integer);
		printf("%f = %f + %f\n", numStack.top(), integer, fraction);
		if (fraction > 0) {
			sprintf(result, "%.2f", numStack.top());
		}
		else {
			sprintf(result, "%.f", numStack.top());
		}
	}
}

LRESULT CALLBACK KeybdProc(int code, WPARAM wParam, LPARAM lParam) {	
	if (wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;

		BYTE lpKeyState[256];
		GetKeyboardState(lpKeyState);
		if (wVirtKey == VK_RETURN) {
			printf("Enter KEY!!!\n");
			char result[100] = { 0, };
			enterAction(result);
			SetDlgItemText(g_hDlg, IDC_STATIC, result);
			return TRUE;
		}
		else if(wVirtKey == VK_BACK) {
			printf("BACK KEY!!!\n");
			makeString(s, 2, "");
			InvalidateRect(g_hDlg, NULL, FALSE);
			return TRUE;
		}
		else if (wVirtKey == VK_ESCAPE) {
			printf("ESC KEY!!!\n");
			close(g_hDlg, wParam);
			return TRUE;
		}

		char result;
		ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
		printf("d: %d, x: %x, c: %c\n", result, result, result);
		switch (result) {
		case '1': printf("1\n"); s.append("1"); break;
		case '2': printf("2\n"); s.append("2"); break;
		case '3': printf("3\n"); s.append("3"); break;
		case '4': printf("4\n"); s.append("4"); break;
		case '5': printf("5\n"); s.append("5"); break;
		case '6': printf("6\n"); s.append("6"); break;
		case '7': printf("7\n"); s.append("7"); break;
		case '8': printf("8\n"); s.append("8"); break;
		case '9': printf("9\n"); s.append("9"); break;
		case '0': printf("0\n"); s.append("0"); break;
		case '+': printf("+\n"); makeString(s, 0, "+"); break;
		case '-': printf("-\n"); makeString(s, 0, "-"); break;
		case '*': printf("*\n"); makeString(s, 0, "*"); break;
		case '/': printf("/\n"); makeString(s, 0, "/"); break;
		case '.': printf(".\n"); makeString(s, 3, "."); break;
		case '(': printf("(\n"); s.append(" ( "); break;
		case ')': printf(")\n"); s.append(" ) "); break;
		case 'c':
			printf("c\n");
			s.clear();
			SetDlgItemText(g_hDlg, IDC_STATIC, NULL);
		break;
		}

		cout << s << endl;
		InvalidateRect(g_hDlg, NULL, FALSE);
		//std::cout << result << std::endl;
	}

	return CallNextHookEx(hHook, code, wParam, lParam);
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);	
    switch (message)
    {
    case WM_INITDIALOG:
		g_hDlg = hDlg;
		hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeybdProc, NULL, 0);
		if (hHook == NULL) {
			std::cout << "Keyboard hook failed!" << std::endl;
		}
        return (INT_PTR)TRUE;

	case WM_COMMAND: {
		string op;

		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: s.append("0"); break;	// 0
		case IDC_BUTTON2:	// C:clear
			printf("C");
			s.clear();
			SetDlgItemText(hDlg, IDC_STATIC, NULL);
			break;
		case IDC_BUTTON3:	// Enter
		{
			char result[100] = { 0, };
			enterAction(result);
			SetDlgItemText(hDlg, IDC_STATIC, result);
			break;
		}
		case IDC_BUTTON4: s.append("1"); break;	// 1
		case IDC_BUTTON5: s.append("2"); break;	// 2
		case IDC_BUTTON6: s.append("3"); break;	// 3
		case IDC_BUTTON7: s.append("4"); break;	// 4
		case IDC_BUTTON8: s.append("5"); break;	// 5
		case IDC_BUTTON9: s.append("6"); break;	// 6
		case IDC_BUTTON10: makeString(s, 0, "+"); break; // +
		case IDC_BUTTON11: s.append("7"); break;	// 7
		case IDC_BUTTON12: s.append("8"); break;	// 8
		case IDC_BUTTON13: s.append("9"); break;	// 9
		case IDC_BUTTON14:	// Back
			printf("Back");
			makeString(s, 2, "");
			break;
		case IDC_BUTTON15: makeString(s, 0, "/"); break;	// /
		case IDC_BUTTON16: makeString(s, 0, "*"); break;	// *
		case IDC_BUTTON17: makeString(s, 0, "-"); break;	// -
		}
		cout << s << endl;
		InvalidateRect(hDlg, NULL, FALSE);
		break;
	}
	case WM_CLOSE:
		close(hDlg, wParam);
		return (INT_PTR)TRUE;
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);
		SetDlgItemText(hDlg, IDC_EDIT1, s.c_str());
		/*RECT rc = {10, 10, 173, 120};// x, y, width, height
		UINT format = DT_LEFT | DT_TOP | DT_EDITCONTROL | DT_WORDBREAK;
		DrawText(hdc, s.c_str(), -1, &rc, format | DT_CALCRECT);
		DrawText(hdc, s.c_str(), -1, &rc, format);*/
		EndPaint(hDlg, &ps);
		break;
    }
	
    return (INT_PTR)FALSE;
}
