#include "SandboxGame.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include <iostream>

using namespace dae;

SandboxGame::SandboxGame()
	:Game()
{

}

SandboxGame::~SandboxGame()
{

}

void SandboxGame::Load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

}