#pragma once

// Defining the world dimensions
const int global_world_size_x = 136;
const int global_world_size_y = 78;
const int block_size = 10;

// Handling the elevation
int max_elevation = 400;

int primary_terrain_ratio = 6;
int primary_reduction_ratio = 2;
float primary_impact = 0.5;

int secondary_terrain_ratio = 2;
float secondary_impact = 0.3;

// River stuff
int maxRiverSize = 1000;