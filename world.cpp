#include <iostream>
#include <cstdlib>
#include "config.hpp"
#include "world.hpp"

World::World(int x_size, int y_size) : x_size(x_size), y_size(y_size), blocks(x_size * y_size) {
	// Create a temporary corners vector for randomly generating elevation
	std::vector<float> corners((x_size + 1) * (y_size + 1));

	for (int y=0; y < y_size + 1; y++) {
		for (int x=0; x < x_size +1; x++) {
			corners[(y * x_size) + x] = static_cast<float>(rand() % max_elevation); // Probably mistake and needs to be y * x_size
		}
	}

	// Need to set coordinates for each
	for (int y_pos=0; y_pos < y_size; y_pos++) {
		for (int x_pos=0; x_pos < x_size; x_pos++) {
			blocks[(y_pos * x_size) + x_pos].setCoordinates(x_pos, y_pos, corners, x_size);
		}
	}

	std::cout << "World generated!" << std::endl;
}

void World::generate_terrain(int scale_ratio, int reduction_ratio, bool normalize, float impact_factor) {
	// Generate the terrain grid
	int terrain_x_size = x_size / scale_ratio;
	int terrain_y_size = y_size / scale_ratio;

	int terrain_corners_length = (terrain_x_size + 1) * (terrain_y_size + 1);
	std::vector<float> terrain_corners(terrain_corners_length); 

	for (int i=0; i < terrain_corners_length; i++) {
		terrain_corners[i] = static_cast<float>(rand() % (max_elevation / reduction_ratio));
	}

	// Apply the big elevation patches
	for (int x=0; x < terrain_x_size; x++) {
		for (int y=0; y < terrain_y_size; y++) {
			int left_x = x;
			int right_x = x + 1;
			int top_y = y;
			int bot_y = y + 1;

			float top_left = terrain_corners[((terrain_x_size + 1) * top_y) + left_x];
			float top_right = terrain_corners[((terrain_x_size + 1) * top_y) + right_x];
			float bot_left = terrain_corners[((terrain_x_size + 1) * bot_y) + left_x];
			float bot_right = terrain_corners[((terrain_x_size + 1) * bot_y) + right_x];

			float terrain_block_average = (top_left + top_right + bot_left + bot_right) / 4;

			// Determine which blocks are affected
			int block_x_positions[scale_ratio];
			int block_y_positions[scale_ratio];

			for (int g=0; g < scale_ratio; g++) {
				block_x_positions[g] = (x * scale_ratio) + g;
				block_y_positions[g] = (y * scale_ratio) + g;
			}

			for (int bx=0; bx < scale_ratio; bx++) {
				for (int by=0; by < scale_ratio; by++) {
					int target_index = (block_y_positions[by] * x_size) + block_x_positions[bx];

					if (target_index < x_size * y_size) {
						if (normalize) {
							blocks[target_index].addElevation(terrain_block_average, impact_factor);
						} else {
							blocks[target_index].setElevation(terrain_block_average);
						}
						
						//std::cout << "Adjusted elevation for block at coordinates " << block_x_positions[bx] << ", " << block_y_positions[by] << std::endl;
					}
				}
			}

		}
	}
}

void World::smooth_edges(int scale_ratio) {
	// Recreate the terrain grid
	int terrain_x_size = x_size / scale_ratio;
	int terrain_y_size = y_size / scale_ratio;

	for (int x=0; x < terrain_x_size; x++) {
		for (int y=0; y < terrain_y_size; y++) {
			// For every block determine minimum and maxiumum coordinates
			int x_extremes[2] = {x * scale_ratio, (x * scale_ratio) + (scale_ratio - 1)};
			int y_extremes[2] = {y * scale_ratio, (y * scale_ratio) + (scale_ratio - 1)};

			// Handle edges on X axis extremes
			for (int xx=0; xx < 2; xx++) {
				for (int g=0; g < scale_ratio; g++) {
					int curr_y = (y * scale_ratio) + g;
					int target_index = (curr_y * x_size) + x_extremes[xx];

					if (target_index < x_size * y_size) {
						blocks[target_index].averageElevation(blocks, x_size * y_size, x_size);
					}
				}
			}

			// Handle edges on Y axis extremes
			for (int xy=0; xy < 2; xy++) {
				for (int g=0; g < scale_ratio; g++) {
					int curr_x = (x * scale_ratio) + g;
					int target_index = (y_extremes[xy] * x_size) + curr_x;

					if (target_index < x_size * y_size) {
						blocks[target_index].averageElevation(blocks, x_size * y_size, x_size);
					}
				}
			}
		}
	}

}

void World::render_world(SDL_Renderer* ren) {
	for (int y=0; y < y_size; y++) {
		for (int x=0; x < x_size; x++) {
			blocks[(y * x_size) + x].render(ren);
		}
	}
}