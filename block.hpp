#pragma once
#include "config.hpp"
#include "block_types.hpp"
#include "game.hpp"

class Block {
public:
	Block();
	void setCoordinates(int x_pos, int y_pos, std::vector<float>& corners, int corners_x_size);
	int getPosX();
	int getPosY();
	BlockType getType();

	void setElevation(float target_elevation);
	float getElevation();
	void addElevation(float target_elevation, float impact_factor);
	void averageElevation(std::vector<Block>& blocks, int maxIndex, int x_size);

	void convertToRiver();

	void render(SDL_Renderer* ren);

private:
	BlockType type;
	int x_pos;
	int y_pos;
	float elevation;
	int elevation_color_red;
	int elevation_color_green;
	int elevation_color_blue;
	SDL_FRect draw_position;

	void getElevationColor();
};
