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

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_P)){
		sentido = AUM_X;
		if (x < 72 &&
			(x1 > x0 + 8 || x1 < x0 + 8 || y1 - y0 >= 8 || y0 - y1 >= 8 || z1 - z0 >= 8 || z0 - z1 >= 8) &&
			(x2 > x0 + 8 || x2 < x0 + 8 || y2 - y0 >= 8 || y0 - y2 >= 8 || z2 - z0 >= 8 || z0 - z2 >= 8) &&
			(x3 > x0 + 8 || x3 < x0 + 8 || y3 - y0 >= 8 || y0 - y3 >= 8 || z3 - z0 >= 8 || z0 - z3 >= 8) &&
			(x4 > x0 + 8 || x4 < x0 + 8 || y4 - y0 >= 8 || y0 - y4 >= 8 || z4 - z0 >= 8 || z0 - z4 >= 8)) {
			x++; objetos_zona_1[0][2]++;
		}
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
		sentido = AUM_Z;
		if (z < 72 &&
			(x1 - x0 >= 8 || x0 - x1 >= 8 || y1 - y0 >= 8 || y0 - y1 >= 8 || z1 > z0 + 8 || z1 < z0 + 8) &&
			(x2 - x0 >= 8 || x0 - x2 >= 8 || y2 - y0 >= 8 || y0 - y2 >= 8 || z2 > z0 + 8 || z2 < z0 + 8) &&
			(x3 - x0 >= 8 || x0 - x3 >= 8 || y3 - y0 >= 8 || y0 - y3 >= 8 || z3 > z0 + 8 || z3 < z0 + 8) &&
			(x4 - x0 >= 8 || x0 - x4 >= 8 || y4 - y0 >= 8 || y0 - y4 >= 8 || z4 > z0 + 8 || z4 < z0 + 8)) {
			z++; objetos_zona_1[0][4]++;
		}
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_O)) {
		sentido = DIS_X;
		if (x > 0 &&
			(x1<x0 - 8 || x1>x0 - 8 || y1 - y0 >= 8 || y0 - y1 >= 8 || z1 - z0 >= 8 || z0 - z1 >= 8) &&
			(x2<x0 - 8 || x2>x0 - 8 || y2 - y0 >= 8 || y0 - y2 >= 8 || z2 - z0 >= 8 || z0 - z2 >= 8) &&
			(x3<x0 - 8 || x3>x0 - 8 || y3 - y0 >= 8 || y0 - y3 >= 8 || z3 - z0 >= 8 || z0 - z3 >= 8) &&
			(x4<x0 - 8 || x4>x0 - 8 || y4 - y0 >= 8 || y0 - y4 >= 8 || z4 - z0 >= 8 || z0 - z4 >= 8)) {
			x--; objetos_zona_1[0][2]--;
		}
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Q)) {
		sentido = DIS_Z;
		if (z > 0 &&
			(x1 - x0 >= 8 || x0 - x1 >= 8 || y1 - y0 >= 8 || y0 - y1 >= 8 || z1<z0 - 8 || z1>z0 - 8) &&
			(x2 - x0 >= 8 || x0 - x2 >= 8 || y2 - y0 >= 8 || y0 - y2 >= 8 || z2<z0 - 8 || z2>z0 - 8) &&
			(x3 - x0 >= 8 || x0 - x3 >= 8 || y3 - y0 >= 8 || y0 - y3 >= 8 || z3<z0 - 8 || z3>z0 - 8) &&
			(x4 - x0 >= 8 || x0 - x4 >= 8 || y4 - y0 >= 8 || y0 - y4 >= 8 || z4<z0 - 8 || z4>z0 - 8)) {
			z--; objetos_zona_1[0][4]--;
		}
		
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
		if (y < 32 &&
			(x1 - x0 >= 8 || x0 - x1 >= 8 || y1 > y0 + 8 || y1 < y0 + 8 || z1 - z0 >= 8 || z0 - z1 >= 8) &&
			(x2 - x0 >= 8 || x0 - x2 >= 8 || y2 > y0 + 8 || y2 < y0 + 8 || z2 - z0 >= 8 || z0 - z2 >= 8) &&
			(x3 - x0 >= 8 || x0 - x3 >= 8 || y3 > y0 + 8 || y3 < y0 + 8 || z3 - z0 >= 8 || z0 - z3 >= 8) &&
			(x4 - x0 >= 8 || x0 - x4 >= 8 || y4 > y0 + 8 || y4 < y0 + 8 || z4 - z0 >= 8 || z0 - z4 >= 8)) {
			y += 4; objetos_zona_1[0][3] += 4;
		}
	}
}

void Game::update() {
	//update the position of the cubes
	x0 = objetos_zona_1[0][2];
	y0 = objetos_zona_1[0][3];
	z0 = objetos_zona_1[0][4];

	x1 = objetos_zona_1[1][2];
	y1 = objetos_zona_1[1][3];
	z1 = objetos_zona_1[1][4];

	x2 = objetos_zona_1[2][2];
	y2 = objetos_zona_1[2][3];
	z2 = objetos_zona_1[2][4];

	x3 = objetos_zona_1[3][2];
	y3 = objetos_zona_1[3][3];
	z3 = objetos_zona_1[3][4];

	x4 = objetos_zona_1[4][2];
	y4 = objetos_zona_1[4][3];
	z4 = objetos_zona_1[4][4];

	//get the distance of every object from the origin 0,0,0
	//adding the three coordinates x,y,z
	dist[0][0] = x0 + y0 + z0; dist[0][1] = 0; //0:distance, 1:number of the object.
	dist[1][0] = x1 + y1 + z1; dist[1][1] = 1;
	dist[2][0] = x2 + y2 + z2; dist[2][1] = 2;
	dist[3][0] = x3 + y3 + z3; dist[3][1] = 3;
	dist[4][0] = x4 + y4 + z4; dist[4][1] = 4;

	//sort objects with bubble method by distance.
	for (n = NUM_OBJETOS - 1; n > 0; n--)
	{
		for (m = 0; m < n; m++)
		{
			if (dist[m][0] > dist[m + 1][0])
			{
				temp = dist[m][0]; dist[m][0] = dist[m + 1][0]; dist[m + 1][0] = temp;
				temp = dist[m][1]; dist[m][1] = dist[m + 1][1]; dist[m + 1][1] = temp;
			}
		}
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
	for (n = 0; n < NUM_OBJETOS; n++)
	{
		//if the object is the ball.
		if (dist[n][1] == 0)
		{
			x = objetos_zona_1[0][2];
			y = objetos_zona_1[0][3];
			z = objetos_zona_1[0][4];

			//change the sprite of the ball by direction
			if (sentido == AUM_X) {
				pos_objeto[0] = xyz_bola_b_zona_1[0];
				pos_objeto[1] = xyz_bola_b_zona_1[1];
			}
			if (sentido == AUM_Z) {
				pos_objeto[0] = xyz_bola_a_zona_1[0];
				pos_objeto[1] = xyz_bola_a_zona_1[1];
			}
			if (sentido == DIS_X) {
				pos_objeto[0] = xyz_bola_d_zona_1[0];
				pos_objeto[1] = xyz_bola_d_zona_1[1];
			}
			if (sentido == DIS_Z) {
				pos_objeto[0] = xyz_bola_c_zona_1[0];
				pos_objeto[1] = xyz_bola_c_zona_1[1];
			}
			pos_objeto[4] = objetos_zona_1[0][5];
			pos_objeto[5] = objetos_zona_1[0][6];
		}

		m = dist[n][1];

		//if the object is not the ball.
		if (m == 1 || m == 2 || m == 3 || m == 4)
		{
			x = objetos_zona_1[m][2];
			y = objetos_zona_1[m][3];
			z = objetos_zona_1[m][4];

			pos_objeto[0] = objetos_zona_1[m][0];
			pos_objeto[1] = objetos_zona_1[m][1];
			pos_objeto[4] = objetos_zona_1[m][5];
			pos_objeto[5] = objetos_zona_1[m][6];
		}

		pos_objeto[2] = 144 + ((x - z) << 1); //calculate the screen x = xorigin + (x-z) * 2;
		pos_objeto[3] = 21 + (x + z) - (y << 1); //calculate the scren y = yorigin + (x+z) - y*2;

		//render the object
		SDL_Rect src, dest;
		src.x = pos_objeto[0];
		src.y = pos_objeto[1];
		dest.x = pos_objeto[2];
		dest.y = pos_objeto[3];
		src.w = dest.w = pos_objeto[4];
		src.h = dest.h = pos_objeto[5];
		SDL_SetTextureAlphaMod(AssetsManager::Instance()->getTexture("filma"), 255);
		SDL_RenderCopyEx(g_pRenderer, AssetsManager::Instance()->getTexture("filma"), &src, &dest, 0.0, 0, SDL_FLIP_NONE);

		//if the ball is jumping make it fall.
		if (!InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && objetos_zona_1[0][3] > 0 && y > 0 &&
			(x1 - x0 >= 8 || x0 - x1 >= 8 || y1<y0 - 8 || y1>y0 - 8 || z1 - z0 >= 8 || z0 - z1 >= 8) &&
			(x2 - x0 >= 8 || x0 - x2 >= 8 || y2<y0 - 8 || y2>y0 - 8 || z2 - z0 >= 8 || z0 - z2 >= 8) &&
			(x3 - x0 >= 8 || x0 - x3 >= 8 || y3<y0 - 8 || y3>y0 - 8 || z3 - z0 >= 8 || z0 - z3 >= 8) &&
			(x4 - x0 >= 8 || x0 - x4 >= 8 || y4<y0 - 8 || y4>y0 - 8 || z4 - z0 >= 8 || z0 - z4 >= 8)) {
			objetos_zona_1[0][3]--;
		}
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