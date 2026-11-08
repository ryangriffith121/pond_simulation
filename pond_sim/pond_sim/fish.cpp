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

}

void Fish::draw(float deltaTime) {

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
