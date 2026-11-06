#include "pond.h"

class Pond {
private:
	int x;
	int y;
	int width;
	int height;
	std::vector<Fish> fishList;

public:
	Pond() {}

	Pond(int xCoordinate, int yCoordinate, int pondWidth, int pondHeight) {
		x = xCoordinate;
		y = yCoordinate;
		width = pondWidth;
		height = pondHeight;
	}

	void addFish(std::string name) {
		Fish newFish = Fish{};
		
		fishList.push_back(newFish)

		std::cout << "Added Fish " << name << " from pond" << std::endl;
	};

	void removeFish(int fishIndex) {
		if (fishIndex >= 0 && fishIndex < fishList.size()) {
			fishList.erase(fishList.begin() + fishIndex);
		}

		std::cout << "Removed Fish " << fishIndex << " from pond" << std::endl;
	}

	void printFishList() {
		for (Fish fish : fishList) {
			std::cout << "Name: " << fish.getName() <<
						", X: " << fish.getX() <<
						", Y: " << fish.getY() <<
						", Direction:  " << fish.getDirection() <<
						", Size: " << fish.getSize() <<
						", Color" << fish.getColor() <<
						std::endl;
		}
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}
};