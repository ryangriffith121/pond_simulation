#include "pond.h"

Pond::Pond() {}

Pond::Pond(int xCoordinate, int yCoordinate, int pondWidth, int pondHeight) {
	x = xCoordinate;
	y = yCoordinate;
	width = pondWidth;
	height = pondHeight;
}

void Pond::update(float deltaTime) {
	const sf::FloatRect bounds(
		{ static_cast<float>(x), static_cast<float>(y) },
		{ static_cast<float>(width), static_cast<float>(height) });

	for (Fish& fish : fishList) {
		fish.update(deltaTime, bounds);
	}
}

void Pond::draw(float deltaTime, sf::RenderWindow& surface) {
	for (Fish& fish : fishList) {
		fish.draw(deltaTime, surface);
	}
}

void Pond::addFish(int xCoordinate, int yCoordinate, const std::string fishName, int fishSize, std::vector<int> fishColor) {
	Fish newFish = Fish{xCoordinate, yCoordinate, fishName, fishSize, fishColor};

	fishList.push_back(newFish);

	std::cout << "Added fish '" << fishName << "' to pond" << std::endl;
}

void Pond::removeFish(int fishIndex) {
	if (fishIndex < 0 || fishIndex >= static_cast<int>(fishList.size())) {
		std::cout << "No fish at index " << fishIndex << " to remove" << std::endl;
		return;
	}

	fishList.erase(fishList.begin() + fishIndex);

	std::cout << "Removed Fish " << fishIndex << " from pond" << std::endl;
}

void Pond::printFishList() {
	for (const Fish& fish : fishList) {
		std::cout << "Name: " << fish.getName() <<
					", X: " << fish.getX() <<
					", Y: " << fish.getY() <<
					", Direction:  " << fish.getDirection() <<
					", Size: " << fish.getSize() <<
					", Color: " << fish.getColor()[0] << ", " << fish.getColor()[1] << ", " << fish.getColor()[2] <<
					std::endl;
	}
}

int Pond::getX() {
	return x;
}

int Pond::getY() {
	return y;
}

int Pond::getWidth() {
	return width;
}

int Pond::getHeight() {
	return height;
}
