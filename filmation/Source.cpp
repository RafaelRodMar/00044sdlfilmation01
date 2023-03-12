#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include<vector>
#include"Vector2D.h"
#include"json.hpp"
#include"AssetsManager.h"
#include"InputHandler.h"
#include"game.h"

//the game class
Game* Game::s_pInstance = 0;

Game::Game() {
	m_pRenderer = nullptr;
	m_pWindow = nullptr;
}

Game::~Game() {}

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	m_gameWidth = width;
	m_gameHeight = height;

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = SDL_WINDOW_SHOWN;
		if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

		// if succeeded create our window
		std::cout << "SDL init success\n";
		m_pWindow = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, flags);
		// if the window creation succeeded create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0)
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // sdl could not initialize
	}

	if (TTF_Init() == 0)
	{
		std::cout << "sdl font initialization success\n";
	}
	else
	{
		std::cout << "sdl font init fail\n";
		return false;
	}

	std::cout << "init success\n";
	m_bRunning = true;

	//pass the renderer to the assets manager
	AssetsManager::Instance()->renderer = m_pRenderer;
	//load all the assets in the json file
	AssetsManager::Instance()->loadAssetsJson();

	g_pRenderer = m_pRenderer;
	g_pWindow = m_pWindow;
	return true;
}

void Game::handleEvents() {
	InputHandler::Instance()->update();
}

void Game::update() {
	//update the position of the cubes
	for (cubo = 0; xyz_objetos_zona_1[cubo][0] != ULTIMO; cubo++)
	{
		if (xyz_objetos_zona_1[cubo][2] == 0)
		{
			xyz_objetos_zona_1[cubo][7] = +2;
		}
		else if (xyz_objetos_zona_1[cubo][2] == 72)
		{
			xyz_objetos_zona_1[cubo][7] = -2;
		}
		xyz_objetos_zona_1[cubo][2] += xyz_objetos_zona_1[cubo][7];
	}
}

void Game::render() {
	// set to black // This function expects Red, Green, Blue and
	// Alpha as color values
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(g_pRenderer);

	//draw walls and floor
	for (bloq = 0; mapa_zona_1[bloq][0] != ULTIMO; bloq++) {
		SDL_Rect src, dest;
		src.x = mapa_zona_1[bloq][0];
		src.y = mapa_zona_1[bloq][1];
		dest.x = mapa_zona_1[bloq][2];
		dest.y = mapa_zona_1[bloq][3];
		src.w = dest.w = mapa_zona_1[bloq][4];
		src.h = dest.h = mapa_zona_1[bloq][5];
		SDL_SetTextureAlphaMod(AssetsManager::Instance()->getTexture("filma"), 255);
		SDL_RenderCopyEx(g_pRenderer, AssetsManager::Instance()->getTexture("filma"), &src, &dest, 0.0, 0, SDL_FLIP_NONE);
	}

	//draw objects
	for (bloq = 0; xyz_objetos_zona_1[bloq][0] != ULTIMO; bloq++) {
		x = xyz_objetos_zona_1[bloq][2];
		y = xyz_objetos_zona_1[bloq][3];
		z = xyz_objetos_zona_1[bloq][4];

		//one increment in x or z is 2 horizontal pixels.
		//one increment in y is 2 vertical pixels.
		//x in screen is a combination of x and z.
		//y in screen is a combitantion of x,y and z.
		//In this example the axis range goes from 0 to 72 (72 units by side)
		//so the center is at screen position 144,21
		objetos_zona_1[0] = xyz_objetos_zona_1[bloq][0]; //source x
		objetos_zona_1[1] = xyz_objetos_zona_1[bloq][1]; //source y
		objetos_zona_1[2] = 144 + ((x - z) << 1);  //destination x = [ xorigin + (x-z)*2 ]
		objetos_zona_1[3] = 21 + (x + z) - (y << 1); //destination y = [ yorigin + (x+z) - 2*y ]
		objetos_zona_1[4] = xyz_objetos_zona_1[bloq][5]; //width
		objetos_zona_1[5] = xyz_objetos_zona_1[bloq][6]; //height

		SDL_Rect src, dest;
		src.x = objetos_zona_1[0];
		src.y = objetos_zona_1[1];
		dest.x = objetos_zona_1[2];
		dest.y = objetos_zona_1[3];
		src.w = dest.w = objetos_zona_1[4];
		src.h = dest.h = objetos_zona_1[5];
		SDL_SetTextureAlphaMod(AssetsManager::Instance()->getTexture("filma"), 255);
		SDL_RenderCopyEx(g_pRenderer, AssetsManager::Instance()->getTexture("filma"), &src, &dest, 0.0, 0, SDL_FLIP_NONE); //Load current frame on the buffer game.
	}

	// show the window
	SDL_RenderPresent(g_pRenderer);
}

void Game::quit() {
	m_bRunning = false;
}

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	srand(time(nullptr));

	Uint32 frameStart, frameTime;

	if (Game::Instance()->init("Filmation", 100, 100, 320, 200,
		false))
	{
		while (Game::Instance()->running()) {
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "closing...\n";

	// clean up SDL
	SDL_DestroyWindow(g_pWindow);
	SDL_DestroyRenderer(g_pRenderer);
	AssetsManager::Instance()->clearAllTextures();
	InputHandler::Instance()->clean();
	SDL_Quit();
	return 0;
}