#pragma once

#include "fish.h"

class Pond {
private:
	int x;
	int y;
	int width;
	int height;

public:
	Pond();
	Pond(int xCoordinate, int yCoordinate, int pondWidth, int pondHeight);
	void addFish();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};