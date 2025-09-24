#include <iostream>
#include <cstdlib>
#include "config.hpp"
#include "world.cpp"

int world_size_x = 136;
int world_size_y = 78;

int main() {
	World landscape = World(world_size_x, world_size_y);
}