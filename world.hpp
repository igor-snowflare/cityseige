#pragma once
#include <vector>
#include "config.hpp"
#include "block.cpp"

class World {
public:
	World(int x_size, int y_size);
	//&Block get_block(x, y);

private:
	std::vector<Block> blocks;
	int x_size;
	int y_size;
};
