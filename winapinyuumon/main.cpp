#include<Windows.h>
#include<Vfw.h>
#include<windowsx.h>
#include"resource.h"
#include"game.h"
#include<iostream>
#include<sstream>
#include<string>
//#pragma comment(lib,"msimg32.lib")



static HBITMAP
	hTitlePicture,
	hStartButton,
	hStartButtonPointed,
	hStatusButton,
	hStatusButtonPointed,
	hGachaButton,
	hGachaButtonPointed,
	hQuitButton,
	hQuitButtonPointed,
	hBusan,
	hFieldPicture,
	hHitterBusan;
static HBITMAP
hBitmapWindow;
//������Ă���{�^���̎�ށDphase�ɂ���ĕς��
static int PointedButton = -1;

const POSITION TitleBusanPicturePos = { 32,48 };
const POSITION TitleStartButtonPos = { 240,352 };
const POSITION TitleStatusButtonPos = { 576,352 };
const POSITION TitleGachaButtonPos = { 240,528 };
const POSITION TitleQuitButtonPos = { 576,528 };
static std::string phase = "title";

//�E�B���h�E�v���V�[�W���֐��̐錾
LRESULT CALLBACK TitleWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK GameWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

//���̑��֐��̐錾
bool IsCursorOnRect(POSITION ButtonPosition, SIZE ButtonSize, int CursorX, int CursorY);
SIZE GetBitmapSize(HBITMAP hBitmap);
void DrawIntWithDrawTextExW(HDC hdc, int value, int x, int y);

//�O���[�o���ϐ�
static int X, Y;
static SIZE TitleBusanSize, TitleButtonSize, HitterBusanSize;


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nCmdShow) {

	const TCHAR CLASSNAME[] = L"�N�}�̊��R�̃z�[�������_�[�r�[�I";

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = TitleWndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = (HICON)LoadImage(
		NULL, L"..\\resources\\�A�C�R��.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASSNAME;
	wc.hIconSm = (HICON)LoadImage(
		NULL, L"..\\resources\\�V�X�e���A�C�R��.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"RegisterClassEx�֐��@���s", L"", MB_OK);
		return 0;
	}

	StateInfo* pState = new (std::nothrow) StateInfo;

	if (pState == NULL) {
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT,
		CLASSNAME,
		CLASSNAME,
		//�E�B���h�E�X�^�C���I�v�V����
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		//�T�C�Y
		0,
		0,
		1152,
		720,
		//�e�E�B���h�E
		NULL,
		//���j���[
		NULL,
		GetModuleHandle(NULL),
		//�ǉ��f�[�^
		NULL
	);

	if (!hWnd) {
		MessageBox(NULL, L"CreateWindowEx�֐��@���s", L"", MB_OK);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//�ϐ�����
	static HDC hdc;
	static HDC hdcMem;
	//�摜�̓ǂݍ��݁C�T�C�Y�̎擾
	
	
	

	//��`�̍��W���i�[����\����
	struct rect {
		int x;
		int y;
	};
	//�J�[�\���̑傫���̏�����
	static rect cursorSize = { 10,20 };

	//���b�Z�\�W�L���[
	MSG msg;
	msg.message = NULL;

	//���b�Z�[�W���[�v
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


	//�o�^����
	if (!UnregisterClassW(wc.lpszClassName, GetModuleHandle(NULL))) {
		MessageBoxW(NULL, L"�o�^�������s", L"err", MB_OK);
	}

	return 0;
}


//phase��"title"�̂Ƃ��̃^�C�g���E�B���h�E�v���V�[�W��
LRESULT CALLBACK TitleWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	static HWND hMCI;
	static HDC hdc, hdcMem;
	hdc = GetDC(hWnd);
	static PAINTSTRUCT ps;

	
	//�N���C�A���g�̈�̃f�[�^
	RECT rc;
	GetClientRect(hWnd, &rc);

	//������Ă���{�^���̎�ށDphase�ɂ���ĕς��
	static int PointedButton = -1;
	
	
	switch (msg){
	case WM_CREATE:
		hTitlePicture = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�^�C�g�����.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hStartButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�͂��߂�.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		::TitleButtonSize = GetBitmapSize(hStartButton);
		hStartButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�͂��߂�pointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hStatusButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�X�e�[�^�X.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hStatusButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�X�e�[�^�Xpointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hGachaButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�K�`��.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hGachaButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�K�`��pointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hQuitButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�����.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hQuitButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�����pointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hBusan = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�N�}�̊��R.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		TitleBusanSize = GetBitmapSize(hBusan);
		hFieldPicture = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�t�B�[���h.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hHitterBusan = static_cast<HBITMAP>(LoadImageW(NULL, L"..\\resources\\�Ŏ�.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		HitterBusanSize = GetBitmapSize(hHitterBusan);

		//���y�̍Đ�
		if (hMCI = MCIWndCreate(hWnd, ((LPCREATESTRUCT)lp)->hInstance, WS_CHILD, L"..\\resources\\bgm1.wav")) {
			MCIWndPlay(hMCI);
		}
		else {
			MessageBox(hWnd, L"���y�Đ����s", L"", MB_OK);//@ERROR
		}
		
		break;
	
	case WM_MOUSEMOVE:
		X = LOWORD(lp);
		Y = HIWORD(lp);

		break;

	case WM_PAINT:
		PointedButton = -1;
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc);
		
		//�w�i�̕`��
		SelectObject(hdcMem, hTitlePicture);
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
		//���R�̕`��
		SelectObject(hdcMem, hBusan);
		TransparentBlt(hdc, TitleBusanPicturePos.x, TitleBusanPicturePos.y, TitleBusanSize.cx, TitleBusanSize.cy, hdcMem, 0, 0, TitleBusanSize.cx, TitleBusanSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hStartButton);
		TransparentBlt(hdc, TitleStartButtonPos.x, TitleStartButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hStatusButton);
		TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hGachaButton);
		TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hQuitButton);
		TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		DeleteDC(hdcMem);
		DeleteDC(hdc);
		break;

	case WM_LBUTTONDOWN:
		X = LOWORD(lp);
		Y = HIWORD(lp);
		if (IsCursorOnRect(TitleStartButtonPos, TitleButtonSize, X, Y)) {
			//�X�^�[�g�{�^���������ꂽ
			PointedButton = 1;

			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStartButtonPointed);
			TransparentBlt(hdc, TitleStartButtonPos.x, TitleStartButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (IsCursorOnRect(TitleStatusButtonPos, TitleButtonSize, X, Y)) {
			//�X�e�[�^�X�{�^���������ꂽ
			PointedButton = 2;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStatusButtonPointed);
			TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (IsCursorOnRect(TitleGachaButtonPos, TitleButtonSize, X, Y)) {
			//�K�`���{�^���������ꂽ
			PointedButton = 3;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hGachaButtonPointed);
			TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (IsCursorOnRect(TitleQuitButtonPos, TitleButtonSize, X, Y)) {
			//�����{�^���������ꂽ
			PointedButton = 4;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hQuitButtonPointed);
			TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		break;

	case WM_LBUTTONUP:
		X = LOWORD(lp);
		Y = HIWORD(lp);
		if (PointedButton = 1 &&
			IsCursorOnRect(TitleStartButtonPos, TitleButtonSize, X, Y)) {
			//�X�^�[�g�{�^���������ꂽ��ԂŁC�X�^�[�g�{�^���̏�ō��{�^���������ꂽ
			PointedButton = -1;
			phase = "game";
			SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)GameWndProc);
			SendMessage(hWnd, WM_CREATE, 0, 0);
			SendMessage(hWnd, WM_PAINT, 0, 0);
		}
		else if (PointedButton = 2 &&
			IsCursorOnRect(TitleStatusButtonPos, TitleButtonSize, X, Y)) {
			//�X�e�[�^�X�{�^���������ꂽ��ԂŁC�X�e�[�^�X�{�^���̏�ō��{�^���������ꂽ
			PointedButton = -1;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStatusButton);
			TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (PointedButton = 3 &&
			IsCursorOnRect(TitleGachaButtonPos, TitleButtonSize, X, Y)) {
			//�K�`���{�^���������ꂽ��ԂŁC�K�`���{�^���̏�ō��{�^���������ꂽ
			PointedButton = -1;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hGachaButton);
			TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (PointedButton = 4 &&
			IsCursorOnRect(TitleQuitButtonPos, TitleButtonSize, X, Y)) {
			//�����{�^���������ꂽ��ԂŁC�����{�^���̏�ō��{�^���������ꂽ
			PointedButton = -1;

			SendMessage(hWnd, WM_CLOSE, NULL, NULL);

			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hQuitButton);
			TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else {
			//�����ꂽ�{�^���̂����Ń{�^����������Ȃ�����
			PointedButton = -1;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStartButton);
			TransparentBlt(hdc, TitleStartButtonPos.x, TitleStartButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			SelectObject(hdcMem, hStatusButton);
			TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			SelectObject(hdcMem, hGachaButton);
			TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			SelectObject(hdcMem, hQuitButton);
			TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		break;

	

	case WM_COMMAND:
		switch (wp)
		{
		case ID_END:
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			return 0;
		default:
			break;
		}
		return 0;

	case WM_CLOSE:
		if (IDYES == MessageBoxW(hWnd, L"�{���ɕ��܂����H", L"�m�F", MB_YESNO | MB_ICONQUESTION)) {
			//���鏈��
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	
	return DefWindowProc(hWnd, msg, wp, lp);
}

//phase��"game"�̂Ƃ��̃E�B���h�E�v���V�[�W��
LRESULT CALLBACK GameWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	static HDC hdc, hdcMem, hdcMemWindow;
	hdc = GetDC(hWnd);
	static PAINTSTRUCT ps;
	
	//�N���C�A���g�̈�̃f�[�^
	RECT rc;
	GetClientRect(hWnd, &rc);

	switch (msg) {
	case WM_CREATE:
		hFieldPicture = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\�t�B�[���h.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hHitterBusan = static_cast<HBITMAP>(LoadImageW(NULL, L"..\\resources\\�Ŏ�.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		HitterBusanSize = GetBitmapSize(hHitterBusan);
		break;

	case WM_MOUSEMOVE:
		X = LOWORD(lp);
		Y = HIWORD(lp);
		//�������f�o�C�X�R���e�L�X�g�̎擾
		hdcMem = CreateCompatibleDC(hdc);
		hdcMemWindow = CreateCompatibleDC(hdc);
		//���z�E�B���h�E���쐬
		hBitmapWindow = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		//���z�E�B���h�E��I��
		SelectObject(hdcMemWindow, hBitmapWindow);
		//�t�B�[���h�̕`��
		SelectObject(hdcMem, hFieldPicture);
		BitBlt(hdcMemWindow, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hHitterBusan);
		TransparentBlt(hdcMemWindow, X - HitterBusanSize.cx, Y - HitterBusanSize.cy / 2, HitterBusanSize.cx, HitterBusanSize.cy, hdcMem, 0, 0, HitterBusanSize.cx, HitterBusanSize.cy, RGB(0xFF, 0x00, 0xFF));

		//�ꊇ�ŕ`��
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMemWindow, 0, 0, SRCCOPY);
		DeleteObject(hBitmapWindow);
		DeleteDC(hdcMemWindow);
		DeleteDC(hdcMem);
		DeleteDC(hdc);
		break;

	case WM_PAINT:
	{
		//�������f�o�C�X�R���e�L�X�g�̎擾
		hdcMem = CreateCompatibleDC(hdc);
		hdcMemWindow = CreateCompatibleDC(hdc);
		//���z�E�B���h�E���쐬
		hBitmapWindow = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		//���z�E�B���h�E��I��
		SelectObject(hdcMemWindow, hBitmapWindow);
		//�t�B�[���h�̕`��
		SelectObject(hdcMem, hFieldPicture);
		BitBlt(hdcMemWindow, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hHitterBusan);
		TransparentBlt(hdcMemWindow, X - HitterBusanSize.cx, Y - HitterBusanSize.cy / 2, HitterBusanSize.cx, HitterBusanSize.cy, hdcMem, 0, 0, HitterBusanSize.cx, HitterBusanSize.cy, RGB(0xFF, 0x00, 0xFF));

		//�ꊇ�ŕ`��
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMemWindow, 0, 0, SRCCOPY);
		DeleteObject(hBitmapWindow);
		DeleteDC(hdcMemWindow);
		DeleteDC(hdcMem);
		DeleteDC(hdc);
		break;
	}
	case WM_LBUTTONDOWN:
		
		break;

	case WM_LBUTTONUP:
		
		break;


	case WM_CLOSE:
		if (IDYES == MessageBoxW(hWnd, L"�{���ɕ��܂����H", L"�m�F", MB_YESNO | MB_ICONQUESTION)) {
			//���鏈��
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}



bool IsCursorOnRect(POSITION ButtonPosition, SIZE ButtonSize, int CursorX, int CursorY) {
	/*
	�J�[�\���̍��W�������`�ɓ����Ă��邩���ʂ���֐�
	rx:�����`��x���W
	ry:�����`��y���W
	sx:�����`�̕�
	sy:�����`�̍���
	cx:�J�[�\����x���W
	cy:�J�[�\����y���W
	*/
    int rx = ButtonPosition.x;
    int ry = ButtonPosition.y;
    int sx = ButtonSize.cx;
    int sy = ButtonSize.cy;
    int cx = CursorX;
    int cy = CursorY;

	if (rx <= cx && cx <= rx + sx &&
		ry <= cy && cy <= ry + sy) {
		return true;
	}
	else {
		return false;
	}
}

SIZE GetBitmapSize(HBITMAP hBitmap)
{
	BITMAP bmp;
	SIZE size = { 0 };

	if (GetObject(hBitmap, sizeof(BITMAP), &bmp))
	{
		size.cx = bmp.bmWidth;
		size.cy = bmp.bmHeight;
	}

	return size;
}

void DrawIntWithDrawTextExW(HDC hdc, int value, int x, int y)
{
	// int�^�𕶎���ɕϊ�
	std::wstring text;
	text = std::to_wstring(value); // int�^��wstring�^�ɕϊ�

	// DrawTextExW���g���ăe�L�X�g��`��
	RECT rc = { x, y, 0, 0 }; // �`��̈�̍�����W(x, y)
	DrawTextExW(hdc, const_cast<LPWSTR>(text.c_str()), -1, &rc, DT_LEFT, nullptr);
}