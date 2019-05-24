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

public:
	//SINGLE�p
	Notes();
	//HOLD�p
	Notes(int hold_time);

	Type getType()        const { return type_m; }
	int  getHoldTime()    const { return holdTime_m; }
	int  getAppearFrame() const { return appearFrame_m; }
};