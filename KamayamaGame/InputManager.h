#pragma once

#include<Windows.h>
#include<unordered_map>
#include <memory>

class Window;
class GameObject;

class InputManager
{
public:
	//�L�[�̏�Ԃ�\���񋓌^
	enum class KeyState {
		KEY_UP,//�L�[�͉�����Ă��Ȃ��܂�
		KEY_DOWN,//�L�[�͉����ꂽ�܂�
		KEY_PRESSED,//�L�[�����傤�ǉ����ꂽ
		KEY_RELEASED//�L�[�����傤�Ǘ����ꂽ
	};

	InputManager();
	~InputManager();

	//�L�[�̏�Ԃ��X�V����
	void update();

	//�w�肵���L�[��������Ă��邩�m�F����
	bool isKeyPressed(int keyCode);
	//�w�肵���Q�[���I�u�W�F�N�g���N���b�N����Ă��邩�m�F����
	bool isClicked(const GameObject& object)const;
	//�w�肵���L�[�̏�Ԃ̃Q�b�^�[
	KeyState getKeyState(int keyCode)const;
	//�}�E�X�̍��W�̃Q�b�^�[
	POINT getMousePosition()const;
	//
	void setKeyState(int keyCode, KeyState keyState);
	//�}�E�X�J�[�\���̈ʒu��ύX����iWM_MOUSEMOVE�̎��ɌĂяo���j
	void setCursorPosition(POINT);

private:
	//1�t���[���O�̃L�[�̏��
	std::unordered_map<int, KeyState>oldKeyStates;

	//���݂̃L�[�̏�Ԃ��i�[����}�b�v
	std::unordered_map<int, KeyState>keyStates;

	//�}�E�X�̌��݈ʒu
	POINT mousePosition;

	//�Ď�����L�[�̏��������s��
	void initializeKeys();
};