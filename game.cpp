#include "game.hpp"

Game::Game() : frameCount(0) {

}

Game::~Game() {

}

void Game::init(const char* title, int width, int height, bool fullscreen) {

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Subsystems Initialized..." << std::endl;
		window = SDL_CreateWindow(title, width, height, flags);

		if (window) {
			std::cout << "Window Created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, NULL);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 52, 72, 87, 255);
			std::cout << "Rendered Initialized..." << std::endl;
		}

		isRunning = true;
	} else {
		std::cout << "Initialization failed" << std::endl;
		SDL_GetError();
		isRunning = false;
	}


}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		
		default:
			break;
	}
}

void Game::update() {
	frameCount += 1;
}

void Game::render(World *world) {
	SDL_RenderClear(renderer);
	world->render_world(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Session Terminated" << std::endl;
}