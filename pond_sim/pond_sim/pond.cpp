#include "pond.h"

Pond::Pond() {}

Pond::Pond(int xCoordinate, int yCoordinate, int pondWidth, int pondHeight) {
	x = xCoordinate;
	y = yCoordinate;
	width = pondWidth;
	height = pondHeight;
}

void Pond::addFish(const std::string& name) {
	Fish newFish = Fish{};
	
	fishList.push_back(newFish);

	std::cout << "Added Fish " << name << " from pond" << std::endl;
}

void Pond::removeFish(int fishIndex) {
	if (fishIndex >= 0 && fishIndex < fishList.size()) {
		fishList.erase(fishList.begin() + fishIndex);
	}

	std::cout << "Removed Fish " << fishIndex << " from pond" << std::endl;
}

void Pond::printFishList() {
	for (Fish fish : fishList) {
		std::cout << "Name: " << fish.getName() <<
					", X: " << fish.getX() <<
					", Y: " << fish.getY() <<
					", Direction:  " << fish.getDirection() <<
					", Size: " << fish.getSize() <<
					", Color: " << fish.getColor() <<
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
