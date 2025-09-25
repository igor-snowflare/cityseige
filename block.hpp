#pragma once
#include "config.hpp"
#include "game.hpp"

class Block {
public:
	void setCoordinates(int x_pos, int y_pos, std::vector<float>& corners);
	void render(SDL_Renderer* ren);

private:
	int x_pos;
	int y_pos;
	float elevation;
	int elevation_color_red;
	int elevation_color_green;
	int elevation_color_blue;
	SDL_FRect draw_position;
};
