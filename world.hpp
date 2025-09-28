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
	
	Block* get_block(int x, int y);
	std::vector<Block*> neighbouringBlocks(int posX, int posY, int maxDistance);
	Block* getLowestNeighbour(int blockX, int blockY);
	void logRiver(Block* targetBlock);
	int worldSizeX();
	int worldSizeY();

private:
	std::vector<Block> blocks;
	std::vector<Block*> riverBlocks;
	int x_size;
	int y_size;
};
