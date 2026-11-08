#pragma once

#include <string>
#include <vector>
#include <cmath>

class Fish {
private:

	std::string name;
	int x;
	int y;
	int direction;
	int speed;
	int size;
	std::vector<int> color;

public:

	Fish();
	Fish(int xCoordinate, int yCoordinate, std::string fishName, int fishSize, std::vector<int> fishColor);

	void update(float deltaTime);
	void draw(float deltaTime);

	int getX();
	int getY();
	int getDirection();
	int getSpeed();
	int getSize();
	std::vector<int> getColor();
	std::string getName();

};