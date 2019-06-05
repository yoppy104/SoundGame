#include "DxLib.h"
#include "Notes.h"
#include "InputKey.h"
#include <memory>
#include <vector>
#include <string>

const int CENTER = 250;

void drawCirclePlayerInputLine() {
	//�����ꏊ��`��
	DrawOval(250, 200, 15, 5, GetColor(255, 255, 255), false);
	DrawOval(250, 300, 15, 5, GetColor(255, 255, 255), false);
	DrawOval(200, 250, 5, 15, GetColor(255, 255, 255), false);
	DrawOval(300, 250, 5, 15, GetColor(255, 255, 255), false);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetGraphMode(500, 500, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�m�[�c�̏W���̂̃��X�g
	std::vector<std::unique_ptr<Notes>> right_side_notes;
	std::vector<std::unique_ptr<Notes>> left_side_notes;
	std::vector<std::unique_ptr<Notes>> top_side_notes;
	std::vector<std::unique_ptr<Notes>> bottom_side_notes;

	//�m�[�c�Q�̍\��
	bottom_side_notes.push_back(std::make_unique<Notes>(Notes(100)));
	right_side_notes.push_back(std::make_unique<Notes>(Notes(60)));
	left_side_notes.push_back(std::make_unique<Notes>(Notes(90)));
	top_side_notes.push_back(std::make_unique<Notes>(Notes(60)));

	//���݃t���[��
	int current_frame = 0;

	//�m�[�c��`�悷�鎞�̒��ԕϐ�
	int point_value = 0;

	//���͌n���Ǘ�����N���X
	std::unique_ptr<InputKey> inputer(new InputKey());

	std::string judge_output_str = "";

	//���C�����[�v
	//�G���[���͂������ɂ͋����I��
	//Esc�����͂��ꂽ�狭���I��
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		current_frame++;

		//�m�[�c�̔�����̕`��
		drawCirclePlayerInputLine();
		
		//���̓N���X���X�V����
		inputer->update();

		DrawFormatString(450, 30, GetColor(255, 255, 255), judge_output_str.c_str());

		//���͂��Ă�����A���͎��̕`��
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

		//�m�[�c��`��
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

		//�m�[�c�������ɓ��B���Ă�����A��\���ɂ���B
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
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}