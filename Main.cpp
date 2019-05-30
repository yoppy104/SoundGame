#include "DxLib.h"
#include "Notes.h"
#include <memory>
#include <vector>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	const int CENTER = 250;

	std::vector<Notes> right_side_notes;
	std::vector<Notes> left_side_notes;
	std::vector<Notes> top_side_notes;
	std::vector<Notes> bottom_side_notes;

	int current_frame = 0;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		current_frame++;
		for (auto itr = right_side_notes.begin(); itr != right_side_notes.end(); itr++) {
			if (itr->getAppearFrame() < current_frame) {
				itr->drawNotes(CENTER - (current_frame - itr->getAppearFrame()) * 10, CENTER);
			}
		}
		for (auto itr = left_side_notes.begin(); itr != left_side_notes.end(); itr++) {
			if (itr->getAppearFrame() < current_frame) {
				itr->drawNotes(CENTER - (current_frame - itr->getAppearFrame()) * 10, CENTER);
			}
		}
		for (auto itr = top_side_notes.begin(); itr != top_side_notes.end(); itr++) {
			if (itr->getAppearFrame() < current_frame) {
				itr->drawNotes(CENTER - (current_frame - itr->getAppearFrame()) * 10, CENTER);
			}
		}
		for (auto itr = bottom_side_notes.begin(); itr != bottom_side_notes.end(); itr++) {
			if (itr->getAppearFrame() < current_frame) {
				itr->drawNotes(CENTER - (current_frame - itr->getAppearFrame()) * 10, CENTER);
			}
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}