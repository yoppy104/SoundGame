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

void Notes::drawNotes(int x, int y) {
	DrawGraph(x, y, image, TRUE);
}