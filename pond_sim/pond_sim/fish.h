#pragma once

#include <string>

class Fish {
private:

	std::string name;
	int x;
	int y;
	int direction;
	int speed;
	int size;
	int color[3];

public:

	Fish();
	Fish(int xCoordinate, int yCoordinate, std::string fishName, int fishSize, int& fishColor);

	void update();
	void draw();

	int getX();
	int getY();
	int getDirection();
	int getSpeed();
	int getSize();
	int getColor();
	std::string getName();

};