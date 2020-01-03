// ����.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "����.h"
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
	int prior;		// ������ �켱����
	string op;		// ������
};

stack<double> numStack;	// ���� ����
stack<oper> opStack;	// ������ ����

#define MAX_LOADSTRING 100

INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);
HHOOK hhk;	// �������� ����
HHOOK hHook{ NULL };

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

void inputOperatorInString(string &s, string op) {
	// �� ���ڿ����� �˻�
	if (!s.empty()) {		
		// ���ڿ��� 3���� Ŀ�� ������ �Է� ���� �˻� �ϵ��� ó��
		if (s.length() > 3) {
			// ������ �Է� �� �˻�, �ڿ� ������ ���� �־���� ��.
			if (!strcmp(&s[s.length() - 2], "+ ") || !strcmp(&s[s.length() - 2], "- ") || !strcmp(&s[s.length() - 2], "* ") || !strcmp(&s[s.length() - 2], "/ ")) {
				// ���� ������ �����ϰ� �߰�
				s.erase(s.length() - 3, 3);
				s.append(" " + op + " ");
			} else {
				s.append(" " + op + " ");
			}
		} else {
			s.append(" " + op + " ");
		}				
	}	
}

void checkString(string &s) {
	// �� ���ڿ����� �˻�
	if (!s.empty()) {
		// ���ڿ��� 3���� Ŀ�� ������ �Է� ���� �˻� �ϵ��� ó��
		if (s.length() > 3) {
			// ������ �Է� �� �˻�, �ڿ� ������ ���� �־���� ��.
			if (!strcmp(&s[s.length() - 2], "+ ") || !strcmp(&s[s.length() - 2], "- ") || !strcmp(&s[s.length() - 2], "* ") || !strcmp(&s[s.length() - 2], "/ ")) {
				// ���� ������ �����ϰ� �߰�
				s.erase(s.length() - 3, 3);				
			}			
		}		
	}	
}

void backSpace(string &s) {
	// �� ���ڿ����� �˻�
	if (!s.empty()) {
		// ���ڿ��� 3���� Ŀ�� ������ �Է� ���� �˻� �ϵ��� ó��
		if (s.length() > 3) {
			// ������ �Է� �� �˻�, �ڿ� ������ ���� �־���� ��.
			if (!strcmp(&s[s.length() - 2], "+ ") || !strcmp(&s[s.length() - 2], "- ") || !strcmp(&s[s.length() - 2], "* ") || !strcmp(&s[s.length() - 2], "/ ")) {
				// ���� ������ ����
				s.erase(s.length() - 3, 3);
			}
			else {
				s.erase(s.length() - 1, 1);
			}
		}
		else {
			s.erase(s.length() - 1, 1);
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

LRESULT CALLBACK KeybdProc(int code, WPARAM wParam, LPARAM lParam) {
	/*if (code < 0) {
		return CallNextHookEx(hhk, code, wParam, lParam);		
	}
	//printf("%d %c\n", (char)wParam, (char)wParam);	
	switch (wParam) {
	case 65:
		printf("%d %c\n", (char)wParam, (char)wParam);
		break;
	}
	return CallNextHookEx(hhk, code, wParam, lParam);*/

	if (wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;

		BYTE lpKeyState[256];
		GetKeyboardState(lpKeyState);
		/*lpKeyState[Keys::ShiftKey] = 0;
		lpKeyState[Keys::Capital] = 0;
		if (shift_active()) {
			lpKeyState[Keys::ShiftKey] = 0x80;
		}
		if (capital_active()) {
			lpKeyState[Keys::Capital] = 0x01;
		}*/
		if (wVirtKey == VK_RETURN) {
			printf("Enter KEY!!!\n");
			return TRUE;
		}

		char result;
		ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
		printf("d : %d\n", result);
		printf("x : %x\n", result);
		printf("c : %c\n", result);		
		switch (result) {
		case '1':
			printf("1\n");
			break;
		case '2':
			printf("2\n");
			break;
		case '3':
			printf("3\n");
			break;
		case '4':
			printf("4\n");
			break;
		case '5':
			printf("5\n");
			break;
		case '6':
			printf("6\n");
			break;
		case '7':
			printf("7\n");
			break;
		case '8':
			printf("8\n");
			break;
		case '9':
			printf("9\n");
			break;
		case '0':
			printf("0\n");
			break;		
		case '+':
			printf("+\n");
			break;
		case '-':
			printf("-\n");
			break;
		case '*':
			printf("*\n");
			break;
		case '/':
			printf("/\n");
			break;
		case '.':
			printf(".\n");
			break;
		}
		std::cout << result << std::endl;
	}

	return CallNextHookEx(hHook, code, wParam, lParam);
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static string s;
	char contents[100];
    UNREFERENCED_PARAMETER(lParam);
	//static HWND hEnterButton;
    switch (message)
    {	
	/*case WM_CHAR:
		printf("ABC");
		printf("%c\n", (char)wParam);
		break;*/
    case WM_INITDIALOG:
		//hhk = SetWindowsHookEx(WH_KEYBOARD, KeybdProc, NULL, GetCurrentThreadId());
		hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeybdProc, NULL, 0);
		if (hHook == NULL) {
			std::cout << "Keyboard hook failed!" << std::endl;
		}		
		//hEnterButton = GetDlgItem(hDlg, IDC_BUTTON3);
		//SetFocus(hEnterButton);
        return (INT_PTR)TRUE;

	case WM_COMMAND: {		
		string op;
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
			SetDlgItemText(hDlg, IDC_STATIC, NULL);
			break;
		case IDC_BUTTON3:	// Enter
		{
			checkString(s);
			printf("Enter\n");
			stringstream ss;
			if (!s.empty()) {
				ss.str(s);
				string tok;
				while (ss >> tok) {
					//cout << tok << endl;
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
						int prior;	// ������ �켱����
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
				// 1.50
				// 1.5
				char result[100] = { 0, };
				if (fraction > 0) {
					sprintf(result, "%.2f", numStack.top());
				}
				else {
					sprintf(result, "%.f", numStack.top());
				}
				

				//cout << numStack.top() << endl;
				//ostringstream os;
				//os << numStack.top();
				SetDlgItemText(hDlg, IDC_STATIC, result);
			}			
			break;
		}			
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
			inputOperatorInString(s, "+");			
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
			backSpace(s);
			break;
		case IDC_BUTTON15:	// /
			inputOperatorInString(s, "/");			
			break;
		case IDC_BUTTON16:	// *
			inputOperatorInString(s, "*");			
			break;
		case IDC_BUTTON17:	// -
			inputOperatorInString(s, "-");			
			break;
		}		
		cout << s << endl;	
		InvalidateRect(hDlg, NULL, FALSE);
		break;
	}		
	case WM_CLOSE:
		FreeConsole();
		UnhookWindowsHookEx(hhk);
		EndDialog(hDlg, LOWORD(wParam));
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
