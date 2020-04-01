#include <windows.h> // ���������� �������� � ��������� API
#include "resource.h"

// �������� ����:
HINSTANCE hInst; //���������� ��������
LPCTSTR szWindowClass = "Mazel Maksimenkov";
LPCTSTR szTitle = "Mazel Maksimenkov";
char buff[50];
// ��������� ���� �������

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	// ��������� ����� ����
	MyRegisterClass(hInstance);
	// ��������� ���� ��������
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// ���� ������� ����������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_DBLCLKS | CS_NOCLOSE; //����� ����
	wcex.lpfnWndProc = (WNDPROC)WndProc; //������ ���������
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; //���������� ��������
	wcex.hIcon = LoadIcon(NULL, IDI_QUESTION); //���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS); //���������� �������
	wcex.hbrBackground = GetSysColorBrush(WHITE_BRUSH); //��������� ����
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //���������� ����
	wcex.lpszClassName = szWindowClass; //��� �����
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex); //��������� ����� ����
}
// FUNCTION: InitInstance (HANDLE, int)
// ������� ���� �������� � ������ ���������� �������� � ����� hInst
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //������ ���������� ������� � ����� hInst
	hWnd = CreateWindow(szWindowClass, // ��� ����� ����
		szTitle, // ����� ��������
		WS_CAPTION | WS_BORDER | WS_MINIMIZE | WS_SYSMENU | WS_MINIMIZEBOX, // ����� ����
		GetSystemMetrics(SM_CXSCREEN) / 2 - 110, // ��������� �� �
		GetSystemMetrics(SM_CYSCREEN) / 2 - 75, // ��������� �� Y
		220, // ����� �� �
		150, // ����� �� Y
		NULL, // ���������� ������������ ����
		NULL, // ���������� ���� ����
		hInstance, // ���������� ��������
		NULL); // ��������� ���������.
	if (!hWnd) //���� ���� �� ���������, ������� ������� FALSE

	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); //�������� ����
	UpdateWindow(hWnd); //������� ����
	return TRUE;
}

int CALLBACK DlgProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //����������� ����������� ��������� ��������� �����
		return TRUE;

		//���� ������� ���������� �������� �� ���� ���������� ����
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
			PostQuitMessage(0);
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
		}

		break;
	}
	return FALSE;
}

int CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //����������� ����������� ��������� ��������� �����
		return TRUE;

		//���� ������� ���������� �������� �� ���� ���������� ����
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
		}

		if (LOWORD(wParam) == IDCLOSE)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}

		if (LOWORD(wParam) == IDIGNORE)
		{
			MessageBox(hDlg, "LAB1", "SystemProgramming", MB_OK);
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����

		break;
	}
	return FALSE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// ³����� ���������. ������ � �������� �� �����������, �� ��������� � �������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	switch (message)
	{
	case WM_CREATE: //����������� ��������� ��� �������� ����
			break;
	case WM_PAINT: //������������ ����
		hdc = BeginPaint(hWnd, &ps); //������ ��������� ����
		GetClientRect(hWnd, &rt); //������� ���� ��� ���������
		DrawText(hdc, "Radioactive", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); //�������� ��������� ����
		break;
	case WM_DESTROY: //���������� ������
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_CHANGE_CURSOR:
			SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1)));
			break;

		case ID_CHANGE_ICON:
			SetClassLong(hWnd, GCL_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
			break;

		case ID_CHANGE_BACKGROUND:
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(GRAY_BRUSH));
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_CHANGE_TITLE:
			LoadString(hInst, IDS_STRING104, buff, 50);
			SetWindowText(hWnd, buff);
			break;

		case ID_ABOUT:
			DialogBox(hInst, 				//���������� �������, �� ������ ���� ����
				MAKEINTRESOURCE(IDD_DIALOG1),	//������ ���� ����
				hWnd, 				//���������� ������������ ����
				DlgProc				//��������� ���������� ����
			);
			break;

		case IDNO:
			DialogBox(hInst, 				//���������� �������, �� ������ ���� ����
				MAKEINTRESOURCE(IDD_DIALOG2),	//������ ���� ����
				hWnd, 				//���������� ������������ ����
				DlgProc1				//��������� ���������� ����
			);
			break;
		}

		break;
	default:
		//������� ����������, �� �� �������� ������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}