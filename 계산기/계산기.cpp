// ����.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "����.h"
#include "Windowsx.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

struct oper {
	int prior;		// ������ �켱����
	string op;	// ������
};

stack<int> numStack;	// ���� ����
stack<oper> opStack;	// ������ ����

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

int calcProcessing(string s) {
	int nRet = 0;
	int startIndex = 0;
	while (true) {
		int fIndex = s.find("*", startIndex);
		if (fIndex == -1) {			
			string part = s.substr(startIndex);
			if (part == "") {
				break;
			}			
			cout << part << endl;
			cout << "last part" << endl;
			printf("+ �����ڰ� �� �̻� �����ϴ�.\n");
			break;
		} else {
			int count = fIndex - startIndex;
			string part = s.substr(startIndex, count);

			cout << part << endl;
			startIndex = fIndex + 1;
		}
	}
	return nRet;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static string s;
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
					numStack.push(stoi(tok));
				}
			}

			while (!opStack.empty()) {
				calculate();
			}

			cout << numStack.top() << endl;

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
			if (!s.empty()) {
				s.erase(s.length() - 1, 1);
			}
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
		break;
	}		
	case WM_CLOSE:
		FreeConsole();
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		break;
    }

    return (INT_PTR)FALSE;
}
