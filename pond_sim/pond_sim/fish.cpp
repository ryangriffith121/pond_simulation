
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
	sf::CircleShape eye1(size / eyeSize);
	sf::CircleShape pupil1((size / eyeSize) / pupilSize);

	sf::CircleShape eye2(size / eyeSize);
	sf::CircleShape pupil2((size / eyeSize) / pupilSize);

	eye1.setScale({ 1.f, 0.6f });
	pupil1.setScale({ 1.f, 0.6f });
	eye2.setScale({ 1.f, 0.6f });
	pupil1.setScale({ 1.f, 0.6f });

	eye1.setRotation(sf::degrees(30.f));
	pupil1.setRotation(sf::degrees(30.f));
	eye2.setRotation(sf::degrees(-30.f));
	pupil2.setRotation(sf::degrees(-30.f));

	sf::CircleShape body1(size / body1Size);
	sf::CircleShape body2(size / body2Size);
	sf::CircleShape body3(size / body3Size);

	sf::CircleShape bigFin1(bigFinSize);
	sf::CircleShape bigFin2(bigFinSize);
	sf::CircleShape smallFin1(smallFinSize);
	sf::CircleShape smallFin2(smallFinSize);

	bigFin1.setScale({ 1.f, 0.75f });
	bigFin2.setScale({ 1.f, 0.75f });
	smallFin1.setScale({ 1.f, 0.6f });
	smallFin2.setScale({ 1.f, 0.6f });

	bigFin1.setRotation(sf::degrees(40.f));
	bigFin2.setRotation(sf::degrees(-40.f));
	smallFin1.setRotation(sf::degrees(50.f));
	smallFin2.setRotation(sf::degrees(-50.f));

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

float Fish::getDirection() {
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
