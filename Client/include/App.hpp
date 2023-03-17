#pragma once

#include <SDL.h>
#include <iostream>

class App
{
public:
	App();
	int run();

private:
	int initialise();

	void input();
	void update();
	void render();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_isRunning;
	int m_screenWidth;
	int m_screenHeight;

};