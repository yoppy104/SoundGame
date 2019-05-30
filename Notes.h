#pragma once

enum Type {
	SINGLE,
	HOLD
};

class Notes {
private:
	Type type_m;

	//�������̔���Ɏg�����l�BSINGLE�̏ꍇ��1�ŏ�����
	int holdTime_m;

	//�J�n�t���[������m�[�c����ʏ�ɏo������܂ł̊�t���[����
	//���ۂɂ�BPM�ɂ��d�݂Â�������
	int appearFrame_m;

	//�m�[�c�̉摜
	int image;

public:
	//SINGLE�p
	Notes(int frame);
	//HOLD�p
	Notes(int hold_time, int frame);

	Type getType()        const { return type_m; }
	int  getHoldTime()    const { return holdTime_m; }
	int  getAppearFrame() const { return appearFrame_m; }

	void drawNotes(int x, int y);
};