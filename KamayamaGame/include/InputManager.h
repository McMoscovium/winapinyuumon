#pragma once

#include<Windows.h>
#include<unordered_map>

class Window;
class GameObject;
class PictureObject;

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

	//�L�[�̏�Ԃ��擾����
	KeyState getKeyState(int keyCode)const;

	//�}�E�X�̍��W���擾����
	POINT getMousePosition()const;

	void setKeyState(int keyCode, KeyState keyState);

	//�}�E�X�J�[�\���̈ʒu��ύX����iWM_MOUSEMOVE�̎��ɌĂяo���j
	void setCursorPosition(POINT);
	//
	bool isClicked(const PictureObject& gameObject)const;

private:
	//1�t���[���O�̃L�[�̏��
	std::unordered_map<int, KeyState>oldKeyStates;

	//�L�[�̏�Ԃ��i�[����}�b�v
	std::unordered_map<int, KeyState>keyStates;

	//�}�E�X�̌��݈ʒu
	POINT mousePosition;

	//�Ď�����L�[�̏��������s��
	void initializeKeys();


};

