#include "Notes.h"
#include "DxLib.h"

Notes::Notes(int frame) :
	type_m(SINGLE),
	holdTime_m(1),
	appearFrame_m(frame),
	image(0)
{
	image = LoadGraph("image\\single_notes.png");
}

Notes::Notes(int hold_time, int frame):
	type_m(HOLD),
	holdTime_m(hold_time),
	appearFrame_m(frame),
	image(0)
{
	image = LoadGraph("image\\hold_notes.png");
}

void Notes::drawNotes(int x, int y, bool is_aside) {
	//DrawGraph(x, y, image, TRUE);
	//DrawFormatString(x, y, GetColor(0, 100, 200), "Å©");
	if (is_aside) {
		DrawOval(x, y, 15, 5, GetColor(0, 100, 200), true);
	}
	else {
		DrawOval(x, y, 5, 15, GetColor(0, 100, 200), true);
	}
}