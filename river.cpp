#include <iostream>
#include "river.hpp"
#include "world.hpp"

River::River(int startPosX, int startPosY, World& world, bool allowTributaries) {
	Block* currBlock = world.get_block(startPosX, startPosY);
	currBlock->convertToRiver();
	world.logRiver(currBlock);
	int currPosX = startPosX;
	int currPosY = startPosY;

	bool conditionMet = false;
	int currRiverSize = 1;

	while (conditionMet == false) {
		currRiverSize += 1;
		currBlock = world.getLowestNeighbour(currPosX, currPosY);

		if (currBlock == nullptr) {
			conditionMet = true;
			continue;
		}

		currPosX = currBlock->getPosX();
		currPosY = currBlock->getPosY();

		currBlock->convertToRiver();
		world.logRiver(currBlock);

		if (allowTributaries) {
			int tributary_dice = rand() % 10;
			//std::cout << "My tributary dice is " << tributary_dice << std::endl;

			if (tributary_dice <= 1) {
				River tributary = River(currPosX, currPosY, world, false);
				//std::cout << "Initializing tributary because the dice was " << tributary_dice << std::endl;
			}
		}

		if (currPosX == 0 || currPosY == 0 || currPosX == world.worldSizeX() - 1 || currPosY == world.worldSizeY() - 1 || currRiverSize >= maxRiverSize) {
			conditionMet = true;
		}
	}
}