#include "pond.h"

class Pond {
private:
	int x;
	int y;
	int width;
	int height;

public:
	Pond() {}

	Pond(int xCoordinate, int yCoordinate, int pondWidth, int pondHeight) {
		x = xCoordinate;
		y = yCoordinate;
		width = pondWidth;
		height = pondHeight;
	}

	void addFish() {
		
	};

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