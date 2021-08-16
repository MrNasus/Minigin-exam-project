#include "SandboxGame.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Object.h"
#include "TextureComponent.h"
#include "MoveComponent.h"
#include "TextComponent.h"
#include <iostream>

using namespace minigin;

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

	std::shared_ptr<Object> o = std::make_shared<Object>();
	o->AddComponent(new TextureComponent(o, "background.jpg"));
	scene.Add(o);

	o = std::make_shared<Object>();
	o->AddComponent(new MoveComponent(o, Position2D{3.f, 10.f}));
	o->AddComponent(new TextureComponent(o, "logo.png"));
	Transform t{};
	t.SetPosition(Position2D{ 216.f, 180.f });
	o->SetTransform(t);
	scene.Add(o);

	o = std::make_shared<Object>();
	o->AddComponent(new TextComponent(o, "Programming 4 Assignment", "Lingua.otf", 36));
	t.SetPosition(Position2D{ 80.f, 20.f });
	o->SetTransform(t);
	scene.Add(o);


	//std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	//go->SetTexture("background.jpg");
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);

}