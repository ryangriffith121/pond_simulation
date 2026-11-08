#pragma once

#include <string>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

class Fish {
private:

	std::string name;
	int x;
	int y;
	int direction;
	int speed;
	int size;
	std::vector<int> color;

	std::vector<sf::CircleShape> circles;
	std::vector<sf::CircleShape> polygons;

	const int body1Size = 1;
	const int body2Size = 2;
	const int body3Size = 3;
	const int eyeSize = size / 8;
	const int pupilSize = 1.5;
	const int bigFinSize = 10;
	const int smallFinSize = 12;

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