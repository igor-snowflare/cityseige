#include <iostream>
#include "config.hpp"
#include "elevation_colors.hpp"
#include "block.hpp"

Block::Block() {
	type = EMPTY;
}

void Block::setCoordinates(int x_pos, int y_pos, std::vector<float>& corners, int corners_x_size) {
	// Log the coordinates
	this->x_pos = x_pos;
	this->y_pos = y_pos;

	// Create rect for rendering
	draw_position.x = static_cast<float>(x_pos * block_size);
	draw_position.y = static_cast<float>(y_pos * block_size);
	draw_position.w = static_cast<float>(block_size);
	draw_position.h = static_cast<float>(block_size);

}

int Block::getPosX() { return x_pos; }
int Block::getPosY() { return y_pos; }

void Block::setElevation(float target_elevation) {
	elevation = target_elevation;
	getElevationColor();
}

float Block::getElevation() {
	return elevation;
}

void Block::addElevation(float target_elevation, float impact_factor) {
	float deviation = ((target_elevation - static_cast<float>(max_elevation/2)) / (max_elevation/2)) * impact_factor;
	elevation = elevation * (1 + deviation); 
	getElevationColor();
}

void Block::averageElevation(std::vector<Block>& blocks, int maxIndex, int x_size) {
	float aggregate_elevation = 0;
	float counted_neighbours = 0;

	int possible_movements[3] = {-1, 0, 1};

	for (int ix=0; ix < 3; ix++) {
		int neighbour_x = x_pos + possible_movements[ix];

		if (neighbour_x < 0 || neighbour_x > x_size - 1) {
			continue;
		}

		for (int iy=0; iy < 3; iy++) {
			int neighbour_y = y_pos + possible_movements[iy];

			if (neighbour_y < 0) {
				continue;
			}

			int target_index = (neighbour_y * x_size) + neighbour_x;

			if (target_index < maxIndex) {
				aggregate_elevation += blocks[target_index].getElevation();
				counted_neighbours += 1.0;
			}
		}
	}

	setElevation(aggregate_elevation/counted_neighbours);
}

void Block::getElevationColor() {
	float interpolation_level = elevation/static_cast<float>(max_elevation);

	elevation_color_red = low_color.red + (high_color.red - low_color.red) * interpolation_level;
	elevation_color_green = low_color.green + (high_color.green - low_color.green) * interpolation_level;
	elevation_color_blue = low_color.blue + (high_color.blue - low_color.blue) * interpolation_level;
}

void Block::convertToRiver() {
	type = RIVER;
}

BlockType Block::getType() { return type; }

void Block::render(SDL_Renderer* ren) {
	if (type == RIVER) {
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	} else {
		SDL_SetRenderDrawColor(ren, elevation_color_red, elevation_color_green, elevation_color_blue, 255);
	}
	
	SDL_RenderFillRect(ren, &draw_position);
}