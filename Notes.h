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

public:
	//SINGLE用
	Notes(int frame);
	//HOLD用
	Notes(int hold_time, int frame);

	Type getType()        const { return type_m; }
	int  getHoldTime()    const { return holdTime_m; }
	int  getAppearFrame() const { return appearFrame_m; }

	void drawNotes(int x, int y);
};