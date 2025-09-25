#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class World;

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render(World *world);
	void clean();

	bool running() { return isRunning; }

private:
	int frameCount;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;


};