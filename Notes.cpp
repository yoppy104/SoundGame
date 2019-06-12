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
		//ホールドノーツを伸ばす描画距離
		int long_draw = holdTime_m * 2;
		switch (is_aside)
		{
		case 0:		//top
			if (is_hold) {
				DrawBox(x - 15, 200, x + 15, y - long_draw, GetColor(0, 255, 0), false);
				DrawOval(x, y - long_draw, 15, 5, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x - 15, y, x + 15, y - long_draw, GetColor(0, 255, 0), false);
				DrawOval(x, y, 15, 5, GetColor(0, 255, 0), true);
				DrawOval(x, y - long_draw, 15, 5, GetColor(0, 255, 0), true);
			}
			break;
		case 1:		//bottom
			if (is_hold) {
				DrawBox(x - 15, 300, x + 15, y + long_draw, GetColor(0, 255, 0), false);
				DrawOval(x, y + long_draw, 15, 5, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x - 15, y, x + 15, y + long_draw, GetColor(0, 255, 0), false);
				DrawOval(x, y, 15, 5, GetColor(0, 255, 0), true);
				DrawOval(x, y + long_draw, 15, 5, GetColor(0, 255, 0), true);
			}
			break;
		case 2:		//right
			if (is_hold) {
				DrawBox(300, y-15, x + long_draw, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x, y - long_draw, 5, 15, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x, y - 15, x + long_draw, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x, y, 5, 15, GetColor(0, 255, 0), true);
				DrawOval(x + long_draw, y, 5, 15, GetColor(0, 255, 0), true);
			}
			break;
		case 3:		//left
			if (is_hold) {
				DrawBox(200, y - 15, x - long_draw, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x - long_draw, y, 5, 15, GetColor(0, 255, 0), true);
			}
			else {
				DrawBox(x, y - 15, x - long_draw, y + 15, GetColor(0, 255, 0), false);
				DrawOval(x, y, 5, 15, GetColor(0, 255, 0), true);
				DrawOval(x - long_draw, y, 5, 15, GetColor(0, 255, 0), true);
			}
			break;
		}
		break;
	}
}

int Notes::checkInput(int input_time, int frame) {
	//猶予フレームを定義
	int grace_time = 5;
	//出現から入力取得場所に到達するまでのフレーム数
	int input_line_frame = 100;

	switch (type_m) {
	//シングルノーツの場合
	case SINGLE:
		if (input_time == 1) {
			if (appearFrame_m + input_line_frame - grace_time < frame && appearFrame_m + input_line_frame + grace_time > frame) {
				return 0;
			}
			else if (appearFrame_m + input_line_frame - grace_time * 2 < frame && appearFrame_m + input_line_frame > frame){
				return 1;
			}
			else if (appearFrame_m + input_line_frame - grace_time * 3 < frame && appearFrame_m + input_line_frame > frame) {
				return 2;
			}
		}
		break;
	//ホールドノーツの場合
	case HOLD:
		if (input_time == 1) {
			if (appearFrame_m + input_line_frame - grace_time > frame && appearFrame_m + input_line_frame + grace_time < frame) {
				is_hold = true;
				return 0;
			}
			else if (appearFrame_m + input_line_frame - grace_time * 2 < frame && appearFrame_m + input_line_frame > frame) {
				is_hold = true;
				return 1;
			}
			else if (appearFrame_m + input_line_frame - grace_time * 3 < frame && appearFrame_m + input_line_frame > frame) {
				is_hold = true;
				return 2;
			}
		}
		else if (is_hold & input_time != 0){
			if (input_time < holdTime_m + 2) {
				return 0;
			}
			else if (input_time < holdTime_m + 3) {
				return 1;
			}
			else if (input_time < holdTime_m + 4) {
				return 2;
			}
			else {
				return -2;
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