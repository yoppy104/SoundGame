#include "Notes.h"
#include "DxLib.h"

Notes::Notes(int frame) :
	type_m(SINGLE),
	holdTime_m(1),
	appearFrame_m(frame),
	image(0),
	is_hold(false)
{
	image = LoadGraph("image\\single_notes.png");
}

Notes::Notes(int hold_time, int frame):
	type_m(HOLD),
	holdTime_m(hold_time),
	appearFrame_m(frame),
	image(0),
	is_hold(false)
{
	image = LoadGraph("image\\hold_notes.png");
}

void Notes::drawNotes(int x, int y, int is_aside) {
	//DrawGraph(x, y, image, TRUE);
	//DrawFormatString(x, y, GetColor(0, 100, 200), "Å©");
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
			DrawBox(x - 15, y, x + 15, y - holdTime_m * 10, GetColor(0, 255, 0), false);
			DrawOval(x, y, 15, 5, GetColor(0, 255, 0), false);
			DrawOval(x, y - holdTime_m * 10, 15, 5, GetColor(0, 255, 0), false);
			break;
		case 1:		//bottom
			break;
		case 2:		//right
			break;
		case 3:		//left
			break;
		}
		break;
	}
}

int Notes::checkInput(int input_time, int frame) {
	switch (type_m) {
	case SINGLE:
		if (input_time == 1) {

		}
		break;
	case HOLD:
		break;
	default:
		return -1;
	}
}