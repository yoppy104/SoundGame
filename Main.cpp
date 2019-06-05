#include "DxLib.h"
#include "Notes.h"
#include <memory>
#include <vector>

const int CENTER = 250;



// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetGraphMode(500, 500, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	std::vector<std::unique_ptr<Notes>> right_side_notes;
	std::vector<std::unique_ptr<Notes>> left_side_notes;
	std::vector<std::unique_ptr<Notes>> top_side_notes;
	std::vector<std::unique_ptr<Notes>> bottom_side_notes;

	bottom_side_notes.push_back(std::make_unique<Notes>(Notes(100)));
	right_side_notes.push_back(std::make_unique<Notes>(Notes(60)));
	left_side_notes.push_back(std::make_unique<Notes>(Notes(90)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(60)));


	int current_frame = 0;

	int point_value = 0;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		current_frame++;
		for (auto itr = right_side_notes.begin(); itr != right_side_notes.end(); itr++) {
			if (itr->get()->getAppearFrame() < current_frame) {
				point_value = 500 - (current_frame - itr->get()->getAppearFrame()) * 10;
				itr->get()->drawNotes(point_value, CENTER, false);
			}
			else {
				break;
			}
		}
		for (auto itr = left_side_notes.begin(); itr != left_side_notes.end(); itr++) {
			if (itr->get()->getAppearFrame() < current_frame) {
				point_value = (current_frame - itr->get()->getAppearFrame()) * 10;
				itr->get()->drawNotes(point_value, CENTER, false);
			}
			else {
				break;
			}
		}
		for (auto itr = top_side_notes.begin(); itr != top_side_notes.end(); itr++) {
			if (itr->get()->getAppearFrame() < current_frame) {
				point_value = (current_frame - itr->get()->getAppearFrame()) * 10;
				itr->get()->drawNotes(CENTER, point_value);
			}
			else {
				break;
			}
		}
		for (auto itr = bottom_side_notes.begin(); itr != bottom_side_notes.end(); itr++) {
			if (itr->get()->getAppearFrame() < current_frame) {
				point_value = 500 - (current_frame - itr->get()->getAppearFrame()) * 10;
				itr->get()->drawNotes(CENTER, point_value);
			}
			else {
				break;
			}
		}

		if (!right_side_notes.empty()) {
			if (right_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				right_side_notes.erase(right_side_notes.begin());
			}
		}
		if (!left_side_notes.empty()) {
			if (left_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				left_side_notes.erase(left_side_notes.begin());
			}
		}
		if (!top_side_notes.empty()) {
			if (top_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				top_side_notes.erase(top_side_notes.begin());
			}
		}
		if (!bottom_side_notes.empty()) {
			if (bottom_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				bottom_side_notes.erase(bottom_side_notes.begin());
			}
		}
		
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}