#pragma once
class InputKey {
private:
	//それぞれのキーを押している時間
	int pressTimeUpKey;		//上矢印キー
	int pressTimeDownKey;	//下矢印キー
	int pressTimeRightKey;	//右矢印キー
	int pressTimeLeftKey;	//左矢印キー

public:
	InputKey();
	void update();
	int getPressTimeKey(int keyCode);
};