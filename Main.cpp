#include "DxLib.h"
#include "Notes.h"
#include "InputKey.h"
#include <memory>
#include <vector>
#include <string>

//memo : フレーム数を利用した設計ではうまくいかなかった
//todo : オブジェクト同士の接触判定を利用した設計に変更するか
//　　　 フレーム指定の新たなやり方を模索する櫃ようあり

constexpr int CENTER = 250;

using Frame = unsigned long long;

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
	bottom_side_notes.push_back(std::make_unique<Notes>(Notes(5, 120)));
	bottom_side_notes.push_back(std::make_unique<Notes>(Notes(200)));
	right_side_notes.push_back(std::make_unique<Notes>(Notes(60)));
	left_side_notes.push_back(std::make_unique<Notes>(Notes(60)));
	left_side_notes.push_back(std::make_unique<Notes>(Notes(20, 150)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(10, 20)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(180)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(250)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(255)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(260)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(265)));
	right_side_notes.push_back(std::make_unique<Notes>(Notes(300)));
	bottom_side_notes.push_back(std::make_unique<Notes>(Notes(330)));
	left_side_notes.push_back(std::make_unique<Notes>(Notes(380)));

	int sound_tap = LoadSoundMem("タンバリン（単打）.mp3");

	//現在フレーム
	Frame current_frame = 0;

	//ノーツを描画する時の中間変数
	int point_value = 0;

	//入力系を管理するクラス
	std::unique_ptr<InputKey> inputer(new InputKey());

	//判定を入れておく文字列
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

		//判定を表示する。
		DrawFormatString(400, 30, GetColor(255, 255, 255), judge_output_str.c_str());

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
				point_value = 500 - (current_frame - itr->get()->getAppearFrame()) * 2;
				itr->get()->drawNotes(point_value, CENTER, 2);
			}
			else {
				break;
			}
		}
		for (auto itr = left_side_notes.begin(); itr != left_side_notes.end(); itr++) {
			if (itr->get()->getAppearFrame() < current_frame) {
				point_value = (current_frame - itr->get()->getAppearFrame()) * 2;
				itr->get()->drawNotes(point_value, CENTER, 3);
			}
			else {
				break;
			}
		}
		for (auto itr = top_side_notes.begin(); itr != top_side_notes.end(); itr++) {
			if (itr->get()->getAppearFrame() < current_frame) {
				point_value = (current_frame - itr->get()->getAppearFrame()) * 2;
				itr->get()->drawNotes(CENTER, point_value, 0);
			}
			else {
				break;
			}
		}
		for (auto itr = bottom_side_notes.begin(); itr != bottom_side_notes.end(); itr++) {
			if (itr->get()->getAppearFrame() < current_frame) {
				point_value = 500 - (current_frame - itr->get()->getAppearFrame()) * 2;
				itr->get()->drawNotes(CENTER, point_value, 1);
			}
			else {
				break;
			}
		}
		//右側ノーツ入力系
		if (!right_side_notes.empty()) {
			//押してるかどうかの判定を取得する
			int checkHit = right_side_notes.begin()->get()->checkInput(inputer->getPressTimeKey(KEY_INPUT_RIGHT), current_frame);
			//-1は押されていないの意味
			if (checkHit != -1) {
				//ホールドされていないノーツで押されたものは削除する
				if (!right_side_notes.begin()->get()->getIsHold()) {
					right_side_notes.erase(right_side_notes.begin());
				}
				//判定に応じた処理
				switch (checkHit)
				{
				case 0:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Perfect";
					break;
				case 1:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Great";
					break;
				case 2:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Good";
					break;
				case -2:
					right_side_notes.erase(right_side_notes.begin());
					break;
				default:
					break;
				}
			}
		}
		//左側ノーツ入力系
		if (!left_side_notes.empty()) {
			int checkHit = left_side_notes.begin()->get()->checkInput(inputer->getPressTimeKey(KEY_INPUT_LEFT), current_frame);
			if (checkHit != -1) {
				if (!left_side_notes.begin()->get()->getIsHold()) {
					left_side_notes.erase(left_side_notes.begin());
				}
				switch (checkHit)
				{
				case 0:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Perfect";
					break;
				case 1:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Great";
					break;
				case 2:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Good";
					break;
				case -2:
					left_side_notes.erase(left_side_notes.begin());
					break;
				default:
					break;
				}
			}
		}
		//上側ノーツ入力系
		if (!top_side_notes.empty()) {
			int checkHit = top_side_notes.begin()->get()->checkInput(inputer->getPressTimeKey(KEY_INPUT_UP), current_frame);
			if (checkHit != -1) {
				if (!top_side_notes.begin()->get()->getIsHold()) {
					top_side_notes.erase(top_side_notes.begin());
				}
				switch (checkHit)
				{
				case 0:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Perfect";
					break;
				case 1:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Great";
					break;
				case 2:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Good";
					break;
				case -2:
					top_side_notes.erase(top_side_notes.begin());
					break;
				default:
					break;
				}
			}
		}
		//下側ノーツ入力系
		if (!bottom_side_notes.empty()) {
			int checkHit = bottom_side_notes.begin()->get()->checkInput(inputer->getPressTimeKey(KEY_INPUT_DOWN), current_frame);
			if (checkHit != -1) {
				if (!bottom_side_notes.begin()->get()->getIsHold()) {
					bottom_side_notes.erase(bottom_side_notes.begin());
				}
				switch (checkHit)
				{
				case 0:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Perfect";
					break;
				case 1:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Great";
					break;
				case 2:
					PlaySoundMem(sound_tap, DX_PLAYTYPE_BACK);
					judge_output_str = "Good";
					break;
				case -2:
					bottom_side_notes.erase(bottom_side_notes.begin());
					break;
				default:
					break;
				}
			}
		}

		//ノーツが中央に到達していたら、非表示にする。
		if (!right_side_notes.empty()) {
			auto first_notes = right_side_notes.begin()->get();
			if (!first_notes->getIsHold() && first_notes->getAppearFrame() + 120 < current_frame) {
				right_side_notes.erase(right_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		if (!left_side_notes.empty()) {
			auto first_notes = left_side_notes.begin()->get();
			if (!first_notes->getIsHold() && first_notes->getAppearFrame() + 120 < current_frame) {
				left_side_notes.erase(left_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		if (!top_side_notes.empty()) {
			auto first_notes = top_side_notes.begin()->get();
			if (!first_notes->getIsHold() && first_notes->getAppearFrame() + 120 < current_frame) {
				top_side_notes.erase(top_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		if (!bottom_side_notes.empty()) {
			auto first_notes = bottom_side_notes.begin()->get();
			if (!first_notes->getIsHold() && first_notes->getAppearFrame() + 120 < current_frame) {
				bottom_side_notes.erase(bottom_side_notes.begin());
				judge_output_str = "miss";
			}
		}
		
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}