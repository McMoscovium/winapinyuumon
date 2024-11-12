#include "Window.h"
#include "Game.h"
#include "GameState.h"
#include <Windows.h>
#include "GameObject.h"
#include <iostream>
#include "InputManager.h"

const UINT fps = 60;


//�R���X�g���N�^
Window::Window(HINSTANCE hInstance, int nCmdShow, InputManager* inputManager,Game& game) :hInstance(hInstance), msg({}) {
	registerClass();
	create(game);
	registerUserData(&game);
}

//�f�X�g���N�^
Window::~Window() {
	DestroyWindow(hwnd);//�E�B���h�E�̔j��
}

RECT Window::getClientRect()
{
	RECT rect;
	GetClientRect(hwnd, &rect);
	return rect;
}

//�E�B���h�E�N���X�̓o�^
void Window::registerClass() {
	WNDCLASSEX wc = {};
	wc.lpfnWndProc = WindowProc;//�E�B���h�E�v���V�[�W���̐ݒ�
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	wc.hIcon = (HICON)LoadImage(
		NULL, L".\\assets\\�A�C�R��.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));  // ���F�œh��Ԃ�
	wc.lpszMenuName = NULL;
	wc.hIconSm = (HICON)LoadImage(
		NULL, L".\\assets\\�V�X�e���A�C�R��.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	::RegisterClassExW(&wc);//�E�B���h�E�N���X�̓o�^
}

//�E�B���h�E�쐬�B
void Window::create(Game& game) {
	hwnd = CreateWindowEx(
		0,
		className,
		L"Sample Window",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
}

void Window::registerUserData(Game* game)
{
	userData = new UserData(game);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)userData);
}

RECT Window::getClientRect() const
{
	RECT rect;
	if (GetClientRect(hwnd, &rect)) {
		return rect;
	}
	return { 0,0,0,0 };
}


void Window::renderGameObject(const GameObject& gameObject,HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);//�X�v���C�g�V�[�g�ɕR�t����HDC
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, gameObject.getSpriteImage());
	//���ߐF���l������HDC�̑I������f�o�C�X�ɕ`��
	if (TransparentBlt(
		hdc,
		gameObject.getPositionX(),
		gameObject.getPositionY(),
		gameObject.getWidthOnWindow(),
		gameObject.getHeightOnWindow(),
		hdcMem,
		gameObject.originOfCurrentFrame(),
		0,
		gameObject.getWidth(),
		gameObject.getHeight(),
		RGB(255, 0, 255))
		) {
		//�`�悹������
	}
	else {
		//�`�掸�s
		OutputDebugString(L"���z��ʂɕ`�掸�s\n");
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);//HDC���
}

bool Window::getClientRect(RECT* rect)
{
	if (GetClientRect(hwnd, rect)) {
		return true;
	}
	return false;
}

//�E�B���h�E��\��
void Window::show() const{
	ShowWindow(hwnd, SW_SHOW);
}

void Window::render(const IGameState* currentState)
{
	if (currentState == nullptr) {
		return;
	}
	//HDC�B���m�ۂ���
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);//�E�B���h�E�̃f�o�C�X�R���e�L�X�g

	HDC hdcBackBuffer = CreateCompatibleDC(hdc);// �o�b�N�o�b�t�@�p�f�o�C�X�R���e�L�X�g
	HBITMAP hBackBuffer = CreateCompatibleBitmap(hdc, width, height);//�o�b�N�o�b�t�@�p�r�b�g�}�b�v
	
	HBITMAP oldhBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBackBuffer);//�o�b�N�o�b�t�@�pHDC�̓o�b�N�o�b�t�@�p�r�b�g�}�b�v��I������BoldBitmap�ɂ��Ƃ��o�b�N�o�b�t�@�pHDC���I�����Ă����I�u�W�F�N�g���i�[���Ă����i�I�u�W�F�N�g���[�N�̖h�~�̂��߁j

		
	std::vector<std::wstring> objectOrder = currentState->getObjectOrder();//��ʉ����珇�ɕ`�悷��̂ŁA���̏������擾

	//�Q�[���I�u�W�F�N�g�������珇�Ƀo�b�N�o�b�t�@�ɕ`�悷��
	for (int i = 0; i < currentState->numberOfObjects(); i++) {
		//i�Ԗڂ̃I�u�W�F�N�g��I��
		const GameObject& drawnObject = currentState->getConstGameObject(objectOrder.at(i));
		//visible=false�Ȃ玟�̃I�u�W�F�N�g��
		if (!drawnObject.isVisible()) {
			continue;
		}
		renderGameObject(drawnObject,hdcBackBuffer);
	}
	//�o���オ�����o�b�N�o�b�t�@��{���̃f�o�C�X�R���e�L�X�g�ɕ`��
	RECT clientRect;
	getClientRect(&clientRect);
	if (BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBackBuffer, 0, 0, SRCCOPY)) {
		//�`�搬��
	}
	else {
		OutputDebugString(L"���z��ʂ�`�掸�s\n");
	}

	//HDC�B���������
	SelectObject(hdcBackBuffer, oldhBitmap);
	DeleteObject(hBackBuffer);
	DeleteDC(hdcBackBuffer);

	EndPaint(hwnd, &ps);//���̂Ƃ���hdc��������
}

HDC Window::getDC() const
{
	return ::GetDC(hwnd);
}

UINT Window::getFps() const
{
	return fps;
}

bool Window::update(Game* game)
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {//msg�Ƀ��b�Z�[�W���i�[
		if (msg.message == WM_QUIT) {
			return false;//���[�v�I��
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);//�E�B���h�E�v���V�[�W�������s
		return true;
	}
	else {//���b�Z�[�W���Ȃ��ꍇ
		return true;//���[�v���s
	}
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE: {
		SetTimer(hwnd, 1, 1000 / ::fps, NULL);
		break;
	}
	case WM_CLOSE://�~�{�^���������ꂽ
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY://�E�B���h�E�j�����b�Z�[�W����M
		PostQuitMessage(0);//���b�Z�[�W���[�v�I��
		break;
	case WM_TIMER: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		InputManager& inputManager = game->getInputManager();
		inputManager.update();
		game->update();

		InvalidateRect(hwnd, NULL, FALSE);  //�E�B���h�E�S�̂𖳌������A�V�X�e����WM_PAINT���|�X�g������
		return 0;
	}
	case WM_PAINT: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		Window* window = game->getWindow();
		window->render(game->getCurrentState());
		return 0;
	}
	case WM_MOUSEMOVE: {
		// �}�E�X�̍��W���N���C�A���g�̈��Ŏ擾
		int mouseX = LOWORD(lParam);  // �}�E�X��X���W
		int mouseY = HIWORD(lParam);  // �}�E�X��Y���W

		//InputManager���X�V
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		InputManager& inputManager = userData->game->getInputManager();
		POINT cursor = { LOWORD(lParam),HIWORD(lParam) };
		inputManager.setCursorPosition(cursor);

		// �}�E�X���W���E�B���h�E�̃^�C�g���ɕ\��
		std::wstring title = L"Mouse Position: (" + std::to_wstring(mouseX) + L", " + std::to_wstring(mouseY) + L")";
		SetWindowTextW(hwnd, title.c_str());
		return 0;
	}
	case WM_LBUTTONDOWN: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManager���X�V
		InputManager& inputManager = userData->game->getInputManager();
		inputManager.setKeyState(VK_LBUTTON, InputManager::KeyState::KEY_PRESSED);
		return 0;
	}
	case WM_LBUTTONUP: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManager���X�V
		InputManager& inputManager = userData->game->getInputManager();
		inputManager.setKeyState(VK_LBUTTON, InputManager::KeyState::KEY_RELEASED);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//�f�t�H���g�̏������Ăяo��
}

void Window::termination()
{
	delete userData;
}
