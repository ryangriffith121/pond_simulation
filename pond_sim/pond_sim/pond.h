#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "fish.h"

class Pond {
private:

	int x;
	int y;
	int width;
	int height;
	std::vector<Fish> fishList;

public:

	Pond();
	Pond(int xCoordinate, int yCoordinate, int pondWidth, int pondHeight);

	void update();
	void draw();

	void addFish();
	void removeFish(int fishIndex);
	void printFishList();

	int getX();
	int getY();
	int getWidth();
	int getHeight();

};