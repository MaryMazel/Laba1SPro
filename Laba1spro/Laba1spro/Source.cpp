#include <windows.h> // підключення бібліотеки з функціями API
#include "resource.h"

// Глобальні змінні:
HINSTANCE hInst; //Дескриптор програми
LPCTSTR szWindowClass = "Mazel Maksimenkov";
LPCTSTR szTitle = "Mazel Maksimenkov";
char buff[50];
// Попередній опис функцій

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	// Реєстрація класу вікна
	MyRegisterClass(hInstance);
	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
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
	wcex.style = CS_VREDRAW | CS_DBLCLKS | CS_NOCLOSE; //стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; //віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; //дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_QUESTION); //визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS); //визначення курсору
	wcex.hbrBackground = GetSysColorBrush(WHITE_BRUSH); //установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //визначення меню
	wcex.lpszClassName = szWindowClass; //ім’я класу
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex); //реєстрація класу вікна
}
// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, // ім’я класу вікна
		szTitle, // назва програми
		WS_CAPTION | WS_BORDER | WS_MINIMIZE | WS_SYSMENU | WS_MINIMIZEBOX, // стиль вікна
		GetSystemMetrics(SM_CXSCREEN) / 2 - 110, // положення по Х
		GetSystemMetrics(SM_CYSCREEN) / 2 - 75, // положення по Y
		220, // розмір по Х
		150, // розмір по Y
		NULL, // дескриптор батьківського вікна
		NULL, // дескриптор меню вікна
		hInstance, // дескриптор програми
		NULL); // параметри створення.
	if (!hWnd) //Якщо вікно не творилось, функція повертає FALSE

	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); //Показати вікно
	UpdateWindow(hWnd); //Оновити вікно
	return TRUE;
}

int CALLBACK DlgProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //ініціалізація функціоналу керування діалоговим вікном
		return TRUE;

		//цикл обробки натискання елементів на формі діалогового вікна
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна
			PostQuitMessage(0);
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна
		}

		break;
	}
	return FALSE;
}

int CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //ініціалізація функціоналу керування діалоговим вікном
		return TRUE;

		//цикл обробки натискання елементів на формі діалогового вікна
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна
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
		EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна

		break;
	}
	return FALSE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	switch (message)
	{
	case WM_CREATE: //Повідомлення приходить при створенні вікна
			break;
	case WM_PAINT: //Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); //Почати графічний вивід
		GetClientRect(hWnd, &rt); //Область вікна для малювання
		DrawText(hdc, "Radioactive", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); //Закінчити графічний вивід
		break;
	case WM_DESTROY: //Завершення роботи
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
			DialogBox(hInst, 				//дескриптор додатка, що містить клас вікна
				MAKEINTRESOURCE(IDD_DIALOG1),	//власне клас вікна
				hWnd, 				//дескриптор батьківського вікна
				DlgProc				//процедура діалогового вікна
			);
			break;

		case IDNO:
			DialogBox(hInst, 				//дескриптор додатка, що містить клас вікна
				MAKEINTRESOURCE(IDD_DIALOG2),	//власне клас вікна
				hWnd, 				//дескриптор батьківського вікна
				DlgProc1				//процедура діалогового вікна
			);
			break;
		}

		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}