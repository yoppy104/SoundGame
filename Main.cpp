#include "DxLib.h"
#include "Notes.h"
#include <memory>
#include <vector>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}