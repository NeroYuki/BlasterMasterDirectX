#pragma once
class Camera
{
private:
	float x, y;
	int w, h;
public:
	void update();
	void transform(float x, float y);
};

