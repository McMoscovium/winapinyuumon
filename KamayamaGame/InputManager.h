#pragma once

#include<Windows.h>
#include<unordered_map>



class InputManager
{
public:
	//�L�[�̏�Ԃ�\���񋓌^
	enum class KeyState {
		KEY_UP,
		KEY_DOWN,
		KEY_PRESSED
	};

	InputManager();
	~InputManager();

	//�L�[�̏�Ԃ��X�V����
	void update();

	//�w�肵���L�[��������Ă��邩�m�F����
	bool isKeyPressed(int keyCode);

	//�L�[�̏�Ԃ��擾����
	KeyState getKeyState(int keyCode);

	POINT getMousePosition()const;

private:
	//�L�[�̏�Ԃ��i�[����}�b�v
	std::unordered_map<int, KeyState>keyStates;

	//�}�E�X�̌��݈ʒu
	POINT mousePosition;

	//�Ď�����L�[�̏�����
	void initializeKeys();
};

