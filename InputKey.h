#pragma once
class InputKey {
private:
	//���ꂼ��̃L�[�������Ă��鎞��
	int pressTimeUpKey;		//����L�[
	int pressTimeDownKey;	//�����L�[
	int pressTimeRightKey;	//�E���L�[
	int pressTimeLeftKey;	//�����L�[

public:
	InputKey();
	void update();
	int getPressTimeKey(int keyCode);
};