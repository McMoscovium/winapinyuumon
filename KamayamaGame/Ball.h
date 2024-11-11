#pragma once
class Ball
{
private:
	//打球の速さ
	int speed;
	//センターが０、レフトポールが+45、ライトポールが-45
	int angle;
	//高さ
	int height;
public:
	void setSpeed(int s);
	void setAngle(int a);
};

