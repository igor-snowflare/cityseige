#pragma once
#include "world.hpp"

class River {

public:
	River(int startPosX, int startPosY, World& world, bool allowTributaries=true);
};