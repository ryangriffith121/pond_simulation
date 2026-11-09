#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "fish.h"

class Pond {
private:

	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	std::vector<Fish> fishList = {};

public:

	Pond();
	Pond(int xCoordinate, int yCoordinate, int pondWidth, int pondHeight);

	void update(float deltaTime);
	void draw(float deltaTime);

	void addFish(int xCoordinate, int yCoordinate, const std::string fishName, int fishSize, std::vector<int> fishColor);
	void removeFish(int fishIndex);
	void printFishList();

	int getX();
	int getY();
	int getWidth();
	int getHeight();

};