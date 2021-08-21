#include "MiniginPCH.h"
#include "Engine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Scene.h"
#include "Game.h"
#include "ServiceLocator.h"

using namespace std;
using namespace std::chrono;
using namespace minigin;

void PrintSDLVersion()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void Engine::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	ServiceLocator<Renderer>::provide(new Renderer{});
	Renderer* renderer = ServiceLocator<Renderer>::getService();
	renderer->Init(m_Window);

	ServiceLocator<ResourceManager>::provide(new ResourceManager{});
	ServiceLocator<SceneManager>::provide(new SceneManager{});
}

/**
 * Code constructing the scene world starts here
 */

void Engine::SetGame(Game* pGame)
{
	m_pGame = pGame;
}

void Engine::Cleanup()
{
	Renderer* renderer = ServiceLocator<Renderer>::getService();
	renderer->Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Engine::Run()
{

	// tell the resource manager where he can find the game data
	ResourceManager* resourceManager = ServiceLocator<ResourceManager>::getService();
	resourceManager->Init("../Data/");

	m_pGame->Load();

	Renderer* renderer = ServiceLocator<Renderer>::getService();
	SceneManager* sceneManager = ServiceLocator<SceneManager>::getService();
	InputManager* input = ServiceLocator<InputManager>::getService();

	auto previousTime = high_resolution_clock::now();

	bool doContinue = true;
	while (doContinue)
	{
		const auto currentTime = high_resolution_clock::now();

		doContinue = input->ProcessInput();
		sceneManager->Update(duration_cast<duration<float>>(currentTime - previousTime).count());
		renderer->Render();

		previousTime = currentTime;
		auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
		this_thread::sleep_for(sleepTime);
	}

	Cleanup();
}
