#include <iostream>
#include "block.hpp"

void Block::setCoordinates(int x_pos, int y_pos) {
	this->x_pos = x_pos;
	this->y_pos = y_pos;

	std::cout << "Block coordinates updated to " << this->x_pos << ", " << this->y_pos << std::endl;
}