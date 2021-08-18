#include "SandboxGame.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Object.h"
#include "TextureComponent.h"
#include "MoveComponent.h"
#include "TextComponent.h"
#include "SpriteComponent.h"
#include <memory>
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
	o->AddComponent(std::make_shared<MoveComponent>(o, Position2D{ -20.f, 10.f }));
	o->AddComponent(std::make_shared<TextureComponent>(o, "background.jpg"));
	scene.Add(o);

	o = std::make_shared<Object>();
	o->AddComponent(std::make_shared<MoveComponent>(o, Position2D{ 4.f, 16.f}));
	o->AddComponent(std::make_shared<TextureComponent>(o, "GalagaLogo.png"));
	Transform t{};
	t.SetPosition(Position2D{ 216.f, 180.f });
	o->SetTransform(t);
	scene.Add(o);

	o = std::make_shared<Object>();
	o->AddComponent(std::make_shared<MoveComponent>(o, Position2D{ 8.f, -30.f}));
	o->AddComponent(std::make_shared<SpriteComponent>(o, "BossGreen.png", 2, 1.f));
	t.SetPosition(Position2D{ 216.f, 350.f });
	t.SetRotation(Rotation2DDEG{ 35.f });
	o->SetTransform(t);
	scene.Add(o);

	o = std::make_shared<Object>();
	o->AddComponent(std::make_shared<MoveComponent>(o, Position2D{ 1.f, 45.f }));
	o->AddComponent(std::make_shared<TextComponent>(o, "PRESS START", "Emulogic.ttf", 24));
	t.SetPosition(Position2D{ 80.f, 20.f });
	t.SetRotation(Rotation2DDEG{ 0.f });
	o->SetTransform(t);
	scene.Add(o);
}