#pragma once

#include <string>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

class Fish {
private:

	std::string name = "";
	int x = 0;
	int y = 0;
	float direction = 0;
	int speed = 0;
	int size = 0;
	std::vector<int> color = {255, 0, 0};

	std::vector<sf::CircleShape> circles = {};
	std::vector<sf::CircleShape> polygons = {};

	static constexpr float body1Size = 1.f;
	static constexpr float body2Size = 2.f;
	static constexpr float body3Size = 3.f;
	static constexpr float eyeSize = 8.f;
	static constexpr float pupilSize = 1.5f;
	static constexpr float bigFinSize = 10.f;
	static constexpr float smallFinSize = 12.f;

public:

	Fish();
	Fish(int xCoordinate, int yCoordinate, std::string fishName, int fishSize, std::vector<int> fishColor);

	void update(float deltaTime);
	void draw(float deltaTime);

	int getX();
	int getY();
	float getDirection();
	int getSpeed();
	int getSize();
	std::vector<int> getColor();
	std::string getName();

};