#include "DxLib.h"
#include "Notes.h"
#include "InputKey.h"
#include <memory>
#include <vector>
#include <string>

//memo : �t���[�����𗘗p�����݌v�ł͂��܂������Ȃ�����
//todo : �I�u�W�F�N�g���m�̐ڐG����𗘗p�����݌v�ɕύX���邩
//�@�@�@ �t���[���w��̐V���Ȃ�����͍�����C�悤����

constexpr int CENTER = 250;

using Frame = unsigned long long;

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

	int sound_tap = LoadSoundMem("�^���o�����i�P�Łj.mp3");

	//���݃t���[��
	Frame current_frame = 0;

	//�m�[�c��`�悷�鎞�̒��ԕϐ�
	int point_value = 0;

	//���͌n���Ǘ�����N���X
	std::unique_ptr<InputKey> inputer(new InputKey());

	//��������Ă���������
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

		//�����\������B
		DrawFormatString(400, 30, GetColor(255, 255, 255), judge_output_str.c_str());

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
		//�E���m�[�c���͌n
		if (!right_side_notes.empty()) {
			//�����Ă邩�ǂ����̔�����擾����
			int checkHit = right_side_notes.begin()->get()->checkInput(inputer->getPressTimeKey(KEY_INPUT_RIGHT), current_frame);
			//-1�͉�����Ă��Ȃ��̈Ӗ�
			if (checkHit != -1) {
				//�z�[���h����Ă��Ȃ��m�[�c�ŉ����ꂽ���͍̂폜����
				if (!right_side_notes.begin()->get()->getIsHold()) {
					right_side_notes.erase(right_side_notes.begin());
				}
				//����ɉ���������
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
		//�����m�[�c���͌n
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
		//�㑤�m�[�c���͌n
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
		//�����m�[�c���͌n
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

		//�m�[�c�������ɓ��B���Ă�����A��\���ɂ���B
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
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}