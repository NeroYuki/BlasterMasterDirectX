#pragma once
class CharsetShow {
public:
	int x, y;
	int state;
	CharsetShow(int x, int y, int state) { this->x = x; this->y = y, this->state = state; };
};