#include "Window.h"
#include "Game.h"
#include "GameState.h"
#include <Windows.h>
#include "GameObject.h"




//�R���X�g���N�^
Window::Window(HINSTANCE hInstance, int nCmdShow, Game* game) :hInstance(hInstance), msg({}) {
	registerClass();
	create(game);
	registerUserData(game);
}

//�f�X�g���N�^
Window::~Window() {
	DestroyWindow(hwnd);//�E�B���h�E�̔j��
}

//�E�B���h�E�N���X�̓o�^
void Window::registerClass() {
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;//�E�B���h�E�v���V�[�W���̐ݒ�
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	::RegisterClass(&wc);//�E�B���h�E�N���X�̓o�^
}

//�E�B���h�E�쐬�B
void Window::create(Game* game) {
	hwnd = CreateWindowEx(
		0, className, L"Sample Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL
	);
}

void Window::registerUserData(Game* game)
{
	UserData* userData = new UserData(game, this);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)userData);
}

void Window::getClientRect(RECT* rect) const
{
	GetClientRect(hwnd, rect);
}


void Window::renderGameObject(const GameObject* gameObject,HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);//�X�v���C�g�V�[�g�ɕR�t����HDC
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, gameObject->getSpriteImage());
	//���ߐF���l������HDC�̑I������f�o�C�X�ɕ`��
	TransparentBlt(hdc,
		gameObject->getPositionX(), gameObject->getPositionY(),
		gameObject->getWidth(), gameObject->getHeight(),
		hdcMem,
		gameObject->originOfCurrentFrame(), 0,
		gameObject->getWidth(), gameObject->getHeight(),
		RGB(255, 0, 255));
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);//HDC���
}

//�E�B���h�E��\��
void Window::show() const{
	ShowWindow(hwnd, SW_SHOW);
}

void Window::render(const GameState* currentState)
{
	//HDC�B���m�ۂ���
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);//�E�B���h�E�̃f�o�C�X�R���e�L�X�g

	HDC hdcBackBuffer = CreateCompatibleDC(hdc);// �o�b�N�o�b�t�@�p�f�o�C�X�R���e�L�X�g
	HBITMAP hBackBuffer = CreateCompatibleBitmap(hdc, width, height);//�o�b�N�o�b�t�@�p�r�b�g�}�b�v
	
	HBITMAP oldhBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBackBuffer);//�o�b�N�o�b�t�@�pHDC�̓o�b�N�o�b�t�@�p�r�b�g�}�b�v��I������BoldBitmap�ɂ��Ƃ��o�b�N�o�b�t�@�pHDC���I�����Ă����I�u�W�F�N�g���i�[���Ă����i�I�u�W�F�N�g���[�N�̖h�~�̂��߁j

	
	std::vector<std::string> objectOrder = currentState->getObjectOrder();//��ʉ����珇�ɕ`�悷��̂ŁA���̏������擾

	//�Q�[���I�u�W�F�N�g�������珇�Ƀo�b�N�o�b�t�@�ɕ`�悷��
	for (int i = 0; i < currentState->numberOfObjects(); i++) {
		//i�Ԗڂ̃I�u�W�F�N�g��`��
		const GameObject* drawnObject = currentState->getGameObject(objectOrder.at(i));
		renderGameObject(drawnObject,hdcBackBuffer);
	}
	//�o���オ�����o�b�N�o�b�t�@��{���̃f�o�C�X�R���e�L�X�g�ɕ`��
	RECT clientRect;
	getClientRect(&clientRect);
	BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBackBuffer, 0, 0, SRCCOPY);//�`��

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

bool Window::update(Game* game)
{
	if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {//msg�Ƀ��b�Z�[�W���i�[
		TranslateMessage(&msg);
		DispatchMessageW(&msg);//�E�B���h�E�v���V�[�W�������s
	}
	if (msg.message == WM_DESTROY) {
		return 0;
	}
	return 1;
}


//�E�B���h�E�ɓn�����[�U�[��`�̍\���́B�E�B���h�E�v���V�[�W�����ŊO���̃f�[�^���g�����Ɏg��


//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);//�A�v���I��
		return 0;
	case WM_PAINT:
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		Window* window = userData->window;
		window->render(game->getCurrentState());
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//�f�t�H���g�̏������Ăяo��
}