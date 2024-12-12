#include "Game/Window.h"
#include "Game/Game.h"
#include "GameState/GameState.h"
#include <Windows.h>
#include "GameObject/GameObject.h"
#include <iostream>
#include "Game/InputManager.h"
#include "resource.h"



//�R���X�g���N�^
Window::Window(HINSTANCE hInstance, int nCmdShow, InputManager* inputManager,Game& game) :
	hInstance(hInstance), 
	msg({})
{
	//�E�B���h�E�쐬
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
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(100, 100, 100));  // ���F�œh��Ԃ�
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	::RegisterClassExW(&wc);//�E�B���h�E�N���X�̓o�^
}

//�E�B���h�E�쐬�B
void Window::create(Game& game) {
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	RECT rect = { 0, 0, width, height };//�N���C�A���g�̈�
	AdjustWindowRect(&rect, dwStyle, FALSE); // FALSE�̓��j���[�o�[���Ȃ��ꍇ

	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	hwnd = CreateWindowEx(
		0,
		className,
		L"�N�}�̊��R�̃z�[�������_�[�r�[�I",
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth, windowHeight,
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




bool Window::getClientRect(RECT* rect)const
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

void Window::render(const GameObjectManager& gameObjectManager)
{
	//HDC�B���m�ۂ���
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);//�E�B���h�E�̃f�o�C�X�R���e�L�X�g

	HDC hdcBackBuffer = CreateCompatibleDC(hdc);// �o�b�N�o�b�t�@�p�f�o�C�X�R���e�L�X�g
	HBITMAP hBackBuffer = CreateCompatibleBitmap(hdc, width, height);//�o�b�N�o�b�t�@�p�r�b�g�}�b�v
	
	HBITMAP oldhBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBackBuffer);//�o�b�N�o�b�t�@�pHDC�̓o�b�N�o�b�t�@�p�r�b�g�}�b�v��I������BoldBitmap�ɂ��Ƃ��o�b�N�o�b�t�@�pHDC���I�����Ă����I�u�W�F�N�g���i�[���Ă����i�I�u�W�F�N�g���[�N�̖h�~�̂��߁j


	// �o�b�N�o�b�t�@�𔖂��D�F�œh��Ԃ�
	HBRUSH hBrush = CreateSolidBrush(RGB(100, 100, 100)); // �����D�F (RGB)
	RECT rect;
	GetClientRect(hwnd, &rect);
	FillRect(hdcBackBuffer, &rect, hBrush);  // �o�b�N�o�b�t�@�ɓh��Ԃ�
	DeleteObject(hBrush);  // �u���V�����
	
	std::vector<std::reference_wrapper<GameObject>> objectOrder = gameObjectManager.getDrawOrder();//��ʉ����珇�ɕ`�悷��̂ŁA���̏������擾

	//�Q�[���I�u�W�F�N�g�������珇�Ƀo�b�N�o�b�t�@�ɕ`�悷��
	for (auto& object : objectOrder) {
		//i�Ԗڂ̃I�u�W�F�N�g��I��
		//visible=false�Ȃ玟�̃I�u�W�F�N�g��]
		GameObject& obj = object.get();
		if (!(obj.isVisible())) {
			continue;
		}
		obj.render(hdcBackBuffer);
	}
	//�o���オ�����o�b�N�o�b�t�@��{���̃f�o�C�X�R���e�L�X�g�ɕ`��
	if (
		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcBackBuffer, 0, 0, SRCCOPY)
		) {
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
	//���b�Z�[�W���Ȃ��Ȃ�܂Ń��b�Z�[�W������
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {//msg�Ƀ��b�Z�[�W���i�[
		if (msg.message == WM_QUIT) {
			return false;//���[�v�I��
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);//�E�B���h�E�v���V�[�W�������s
	}	
	return true;//���[�v���s
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE: {
		break;
	}
	case WM_CLOSE://�~�{�^���������ꂽ
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY://�E�B���h�E�j�����b�Z�[�W����M
		PostQuitMessage(0);//���b�Z�[�W���[�v�I��
		break;
	case WM_PAINT: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		Window* window = game->getWindow();
		window->render(game->getCurrentState()->getGameObjectManager());
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
	case WM_KEYDOWN: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManager���X�V
		InputManager& inputManager = userData->game->getInputManager();
		if (wParam == 0x4D) {
			inputManager.setKeyState(0x4D, InputManager::KeyState::KEY_PRESSED);
		}
		return 0;
	}
	case WM_KEYUP: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManager���X�V
		InputManager& inputManager = userData->game->getInputManager();
		if (wParam == 0x4D) {
			inputManager.setKeyState(0x4D, InputManager::KeyState::KEY_RELEASED);
		}
		return 0;
	}
	case WM_ERASEBKGND:
		return 1; // �w�i���������Ȃ�
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//�f�t�H���g�̏������Ăяo��
}

void Window::termination()
{
	delete userData;
}
