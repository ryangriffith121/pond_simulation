
#include "fish.h"

Fish::Fish() {};
Fish::Fish(int xCoordinate, int yCoordinate, std::string fishName, int fishSize, std::vector<int> fishColor) {
	x = xCoordinate;
	y = yCoordinate;
	name = fishName;
	size = fishSize;
	color = fishColor;
};

void Fish::update(float deltaTime) {

	circles = {};
	polygons = {};
}

void Fish::draw(float deltaTime) {
	sf::CircleShape eye1(eyeSize);
	sf::CircleShape pupil1(eyeSize / pupilSize);

	sf::CircleShape eye2(eyeSize);
	sf::CircleShape pupil2(eyeSize / pupilSize);

	eye1.setScale({ 1.f, 0.6 });
	pupil1.setScale({ 1.f, 0.6 });
	eye2.setScale({ 1.f, 0.6 });
	pupil1.setScale({ 1.f, 0.6 });

	sf::CircleShape body1(size / body1Size);
	sf::CircleShape body2(size / body2Size);
	sf::CircleShape body3(size / body3Size);

	sf::CircleShape bigFin1(bigFinSize);
	sf::CircleShape bigFin2(bigFinSize);
	sf::CircleShape bigSmall1(smallFinSize);
	sf::CircleShape bigSmall2(smallFinSize);

	bigFin1.setScale({ 1.f, 0.75 });
	bigFin2.setScale({ 1.f, 0.75 });
	bigSmall1.setScale({ 1.f, 0.6 });
	bigSmall2.setScale({ 1.f, 0.6 });

	circles.push_back(body1);
	circles.push_back(body2);
	circles.push_back(body3);
	circles.push_back(eye1);
	circles.push_back(eye2);
	circles.push_back(pupil1);
	circles.push_back(pupil2);
}

int Fish::getX() {
	return x;
}

int Fish::getY() {
	return y;
}

int Fish::getDirection() {
	return direction;
}

int Fish::getSpeed() {
	return speed;
}

int Fish::getSize() {
	return size;
}

std::vector<int> Fish::getColor() {
	return color;
}

std::string Fish::getName() {
	return name;
}
