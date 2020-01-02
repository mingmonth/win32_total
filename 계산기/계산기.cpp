// 계산기.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "계산기.h"
#include "Windowsx.h"
#include "Commctrl.h"
#include "stdio.h"
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
	// 빈 문자열인지 검사
	if (!s.empty()) {		
		// 문자열이 3보다 커야 마지막 입력 값을 검사 하도록 처리
		if (s.length() > 3) {
			// 마지막 입력 값 검사, 뒤에 공백을 같이 넣어줘야 함.
			if (!strcmp(&s[s.length() - 2], "+ ") || !strcmp(&s[s.length() - 2], "- ") || !strcmp(&s[s.length() - 2], "* ") || !strcmp(&s[s.length() - 2], "/ ")) {
				// 기존 연산자 삭제하고 추가
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

void backSpace(string &s) {
	// 빈 문자열인지 검사
	if (!s.empty()) {
		// 문자열이 3보다 커야 마지막 입력 값을 검사 하도록 처리
		if (s.length() > 3) {
			// 마지막 입력 값 검사, 뒤에 공백을 같이 넣어줘야 함.
			if (!strcmp(&s[s.length() - 2], "+ ") || !strcmp(&s[s.length() - 2], "- ") || !strcmp(&s[s.length() - 2], "* ") || !strcmp(&s[s.length() - 2], "/ ")) {
				// 기존 연산자 삭제
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
	int a, b, result;
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static string s;
	char contents[100];
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
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
			printf("Enter\n");
			stringstream ss;
			ss.str(s);
			string tok;
			while (ss >> tok) {
				//cout << tok << endl;
				if (tok == "(") {
					opStack.push({0, tok});
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

			cout << numStack.top() << endl;
			ostringstream os;
			os << numStack.top();
			SetDlgItemText(hDlg, IDC_STATIC, os.str().c_str());
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
		InvalidateRect(hDlg, NULL, TRUE);		
		break;
	}		
	case WM_CLOSE:
		FreeConsole();
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);
		SetDlgItemText(hDlg, IDC_EDIT1, s.c_str());
		EndPaint(hDlg, &ps);
		break;
    }
	
    return (INT_PTR)FALSE;
}
