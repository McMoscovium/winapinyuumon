#pragma once

#include<Windows.h>
#include<unordered_map>

class Window;

class InputManager
{
public:
	//�L�[�̏�Ԃ�\���񋓌^
	enum class KeyState {
		KEY_UP,//�L�[�͉�����Ă��Ȃ�
		KEY_DOWN,//�L�[�͉����ꂽ�܂�
		KEY_PRESSED//�L�[�����傤�ǉ����ꂽ
	};

	InputManager();
	~InputManager();

	//�L�[�̏�Ԃ��X�V����
	void update();

	//�w�肵���L�[��������Ă��邩�m�F����
	bool isKeyPressed(int keyCode);

	//�L�[�̏�Ԃ��擾����
	KeyState getKeyState(int keyCode);

	//�}�E�X�̍��W���擾����
	POINT getMousePosition()const;

	void digestMessage(Window* window);

private:
	//�L�[�̏�Ԃ��i�[����}�b�v
	std::unordered_map<int, KeyState>keyStates;

	//�}�E�X�̌��݈ʒu
	POINT mousePosition;

	//�Ď�����L�[�̏��������s��
	void initializeKeys();
};

