#include "DxLib.h"
#include "Notes.h"
#include "InputKey.h"
#include <memory>
#include <vector>
#include <string>

const int CENTER = 250;

void drawCirclePlayerInputLine() {
	//判定基準場所を描画
	DrawOval(250, 200, 15, 5, GetColor(255, 255, 255), false);
	DrawOval(250, 300, 15, 5, GetColor(255, 255, 255), false);
	DrawOval(200, 250, 5, 15, GetColor(255, 255, 255), false);
	DrawOval(300, 250, 5, 15, GetColor(255, 255, 255), false);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetGraphMode(500, 500, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//ノーツの集合体のリスト
	std::vector<std::unique_ptr<Notes>> right_side_notes;
	std::vector<std::unique_ptr<Notes>> left_side_notes;
	std::vector<std::unique_ptr<Notes>> top_side_notes;
	std::vector<std::unique_ptr<Notes>> bottom_side_notes;

	//ノーツ群の構成
	bottom_side_notes.push_back(std::make_unique<Notes>(Notes(100)));
	right_side_notes.push_back(std::make_unique<Notes>(Notes(60)));
	left_side_notes.push_back(std::make_unique<Notes>(Notes(90)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(60)));

	//現在フレーム
	int current_frame = 0;

	//ノーツを描画する時の中間変数
	int point_value = 0;

	//入力系を管理するクラス
	std::unique_ptr<InputKey> inputer(new InputKey());

	std::string judge_output_str = "";

	//メインループ
	//エラーをはいた時には強制終了
	//Escが入力されたら強制終了
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		current_frame++;

		//ノーツの判定個所の描画
		drawCirclePlayerInputLine();
		
		//入力クラスを更新する
		inputer->update();

		DrawFormatString(450, 30, GetColor(255, 255, 255), judge_output_str.c_str());

		//入力していたら、入力時の描画
		if (inputer->getPressTimeKey(KEY_INPUT_RIGHT)) {
			DrawOval(300, 250, 8, 18, GetColor(255, 255, 255), false);
		}
		if (inputer->getPressTimeKey(KEY_INPUT_LEFT)) {
			DrawOval(200, 250, 8, 18, GetColor(255, 255, 255), false);
		}
		if (inputer->getPressTimeKey(KEY_INPUT_UP)) {
			DrawOval(250, 200, 18, 8, GetColor(255, 255, 255), false);
		}
		if (inputer->getPressTimeKey(KEY_INPUT_DOWN)) {
			DrawOval(250, 300, 18, 8, GetColor(255, 255, 255), false);
		}

		//ノーツを描画
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

		//ノーツが中央に到達していたら、非表示にする。
		if (!right_side_notes.empty()) {
			if (right_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				right_side_notes.erase(right_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		if (!left_side_notes.empty()) {
			if (left_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				left_side_notes.erase(left_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		if (!top_side_notes.empty()) {
			if (top_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				top_side_notes.erase(top_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		if (!bottom_side_notes.empty()) {
			if (bottom_side_notes.begin()->get()->getAppearFrame() + 25 == current_frame) {
				bottom_side_notes.erase(bottom_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}