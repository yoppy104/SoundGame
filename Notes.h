#pragma once

enum Type {
	SINGLE,
	HOLD
};

class Notes {
private:
	Type type_m;

	//長押しの判定に使う数値。SINGLEの場合は1で初期化
	int holdTime_m;

	//開始フレームからノーツが画面上に出現するまでの基準フレーム数
	//実際にはBPMによる重みづけをする
	int appearFrame_m;

	//ノーツの画像
	int image;

	//ホールド用
	//ホールド中はノーツを消さない
	bool is_hold;

public:
	//SINGLE用
	Notes(int frame);
	//HOLD用
	Notes(int hold_time, int frame);

	Type getType()        const { return type_m; }
	int  getHoldTime()    const { return holdTime_m; }
	int  getAppearFrame() const { return appearFrame_m; }
	bool getIsHold()	  const { return is_hold; }

	void drawNotes(int x, int y, int is_aside);

	int checkInput(int input_time, int frame);
};