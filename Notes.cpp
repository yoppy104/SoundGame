#include "Notes.h"
#include "DxLib.h"

Notes::Notes(int frame) :
	type_m(SINGLE),
	holdTime_m(1),
	appearFrame_m(frame),
	is_hold(false)
{
}

Notes::Notes(int hold_time, int frame):
	type_m(HOLD),
	holdTime_m(hold_time),
	appearFrame_m(frame),
	is_hold(false)
{
}

void Notes::drawNotes(int x, int y, int is_aside) {
	//todo : ���s���z�[���h�m�[�c�̕`�悪���������Ȃ�o�O���C��
	switch (type_m) {
	case SINGLE:
		switch (is_aside) {
		case 0:	//top
		case 1:	//bottom
			DrawOval(x, y, 15, 5, GetColor(0, 100, 200), true);
			break;
		case 2:	//right
		case 3: //left
			DrawOval(x, y, 5, 15, GetColor(0, 100, 200), true);
			break;
		}
		break;
	case HOLD:
		switch (is_aside)
		{
		case 0:		//top
			if (is_hold) {
				DrawBox(x - 15, 200, x + 15, y - holdTime_m * 10, GetColor(0, 255, 0), false);
				DrawOval(x, y - holdTime_m * 10, 15, 5, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x - 15, y, x + 15, y - holdTime_m * 10, GetColor(0, 255, 0), false);
				DrawOval(x, y, 15, 5, GetColor(0, 255, 0), true);
				DrawOval(x, y - holdTime_m * 10, 15, 5, GetColor(0, 255, 0), true);
			}
			break;
		case 1:		//bottom
			if (is_hold) {
				DrawBox(x - 15, 300, x + 15, y - holdTime_m * 10, GetColor(0, 255, 0), false);
				DrawOval(x, y - holdTime_m * 10, 15, 5, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x - 15, y, x + 15, y + holdTime_m * 10, GetColor(0, 255, 0), false);
				DrawOval(x, y, 15, 5, GetColor(0, 255, 0), true);
				DrawOval(x, y + holdTime_m * 10, 15, 5, GetColor(0, 255, 0), true);
			}
			break;
		case 2:		//right
			if (is_hold) {
				DrawBox(300, y-15, x - holdTime_m * 10, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x, y - holdTime_m * 10, 15, 5, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x, y - 15, x + holdTime_m * 10, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x, y, 5, 15, GetColor(0, 255, 0), true);
				DrawOval(x + holdTime_m * 10, y, 5, 15, GetColor(0, 255, 0), true);
			}
			break;
		case 3:		//left
			if (is_hold) {
				DrawBox(200, y - 15, x - holdTime_m * 10, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x, y - holdTime_m * 10, 15, 5, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x, y - 15, x - holdTime_m * 10, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x, y, 5, 15, GetColor(0, 255, 0), true);
				DrawOval(x - holdTime_m * 10, y, 5, 15, GetColor(0, 255, 0), true);
			}
			break;
		}
		break;
	}
}

int Notes::checkInput(int input_time, int frame) {
	//�P�\�t���[�����`
	int grace_time = 5;
	//�o��������͎擾�ꏊ�ɓ��B����܂ł̃t���[����
	int input_line_frame = 40;

	switch (type_m) {
	//�V���O���m�[�c�̏ꍇ
	case SINGLE:
		if (input_time == 1) {
			if (appearFrame_m + input_line_frame > frame - grace_time && appearFrame_m + input_line_frame < frame + grace_time) {
				return 0;
			}
			if (appearFrame_m + input_line_frame > frame - grace_time * 2){
				return 1;
			}
			if (appearFrame_m + input_line_frame > frame - grace_time * 3) {
				return 2;
			}
		}
		break;
	//�z�[���h�m�[�c�̏ꍇ
	case HOLD:
		if (input_time == 1) {
			if (appearFrame_m + input_line_frame > frame - grace_time && appearFrame_m + input_line_frame < frame + grace_time) {
				is_hold = true;
				return 0;
			}
			if (appearFrame_m + input_line_frame > frame - grace_time * 2) {
				is_hold = true;
				return 1;
			}
			if (appearFrame_m + input_line_frame > frame - grace_time * 3) {
				is_hold = true;
				return 2;
			}
		}
		else if (input_time != 0 & is_hold){
			if (input_time < holdTime_m + grace_time) {
				return 0;
			}
			else if (input_time < holdTime_m + grace_time * 2) {
				return 1;
			}
			else if (input_time < holdTime_m + grace_time * 3) {
				return 2;
			}
			else {
				return -1;
			}
		}
		else {
			is_hold = false;
		}
		break;
	default:
		return -1;
	}
	return -1;
}