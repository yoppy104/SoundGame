#include "DxLib.h"
#include "InputKey.h"

InputKey::InputKey() :
	pressTimeDownKey(0),
	pressTimeLeftKey(0),
	pressTimeRightKey(0),
	pressTimeUpKey(0)
{

}

void InputKey::update() {
	//����L�[�̓��͎��Ԃ��擾
	if (CheckHitKey(KEY_INPUT_UP)) {
		pressTimeUpKey++;
	}
	else {
		pressTimeUpKey = 0;
	}
	//�����L�[�̓��͎��Ԃ��擾
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		pressTimeDownKey++;
	}
	else {
		pressTimeDownKey = 0;
	}
	//�����L�[�̓��͎��Ԃ��擾
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		pressTimeLeftKey++;
	}
	else {
		pressTimeLeftKey = 0;
	}
	//�E���L�[�̓��͎��Ԃ��擾
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		pressTimeRightKey++;
	}
	else {
		pressTimeRightKey = 0;
	}
}

int InputKey::getPressTimeKey(int keyCode) {
	//KeyCode�ɉ������{�^���̉������Ԃ�ԋp����
	//KeyCode��DxLib�ɏ�������

	switch (keyCode) {
	case KEY_INPUT_UP:
		return pressTimeUpKey;
		break;
	case KEY_INPUT_DOWN:
		return pressTimeDownKey;
		break;
	case KEY_INPUT_RIGHT:
		return pressTimeRightKey;
		break;
	case KEY_INPUT_LEFT:
		return pressTimeLeftKey;
		break;
	}
}