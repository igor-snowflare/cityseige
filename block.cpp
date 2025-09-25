#include <iostream>
#include "config.hpp"
#include "block.hpp"

void Block::setCoordinates(int x_pos, int y_pos, std::vector<float>& corners) {
	// Log the coordinates
	this->x_pos = x_pos;
	this->y_pos = y_pos;

	// Create rect for rendering
	draw_position.x = static_cast<float>(x_pos * block_size);
	draw_position.y = static_cast<float>(y_pos * block_size);
	draw_position.w = static_cast<float>(block_size);
	draw_position.h = static_cast<float>(block_size);

	// Calculate corner positions
	int left = x_pos;
	int right = x_pos + 1;
	int top = y_pos;
	int bot = y_pos + 1;

	// Get corner values
	float top_left = corners[(left * top) + left];
	float top_right = corners[(right * top) + right];
	float bot_left = corners[(left * bot) + left];
	float bot_right = corners[(right * bot) + right];

	// Calculate elevation based on corners and determine rendering color
	elevation = (top_left + top_right + bot_left + bot_right) / 4;
	elevation_color_red = static_cast<int>((elevation / max_elevation) * 255);
	elevation_color_green = static_cast<int>((elevation / max_elevation) * 255);
	elevation_color_blue = static_cast<int>((elevation / max_elevation) * 255);

	/*
	std::cout << "Block coordinates updated to " << this->x_pos << ", " << this->y_pos << " with elevation of " << elevation << " and color " << elevation_color_red << std::endl;
	std::cout << "I wil render at:" << std::endl;
	std::cout << draw_position.x << ", " << draw_position.y << std::endl;
	std::cout << "I wil render with size:" << std::endl;
	std::cout << draw_position.w << ", " << draw_position.h << std::endl;
	*/

}

void Block::render(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, elevation_color_red, elevation_color_green, elevation_color_blue, 255);
	SDL_RenderFillRect(ren, &draw_position);
}