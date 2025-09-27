#pragma once
#include <vector>
#include "config.hpp"
#include "block.cpp"

class World {
public:
	World(int x_size, int y_size);
	void generate_terrain(int scale_ratio, int reduction_ratio, bool normalize, float impact_factor);
	void smooth_edges(int scale_ratio);
	void render_world(SDL_Renderer* ren);
	//&Block get_block(x, y);

private:
	std::vector<Block> blocks;
	int x_size;
	int y_size;
};
