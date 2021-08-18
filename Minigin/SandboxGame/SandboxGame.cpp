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
	Transform t{};
	auto& scene = SceneManager::GetInstance().CreateScene("MainMenu");

	std::shared_ptr<Object> galagaTitle = std::make_shared<Object>();
	galagaTitle->AddComponent(std::make_shared<TextureComponent>(galagaTitle, "GalagaLogo.png"));
	t.SetPosition(Position2D{ 320.f, 130.f });
	galagaTitle->SetTransform(t);
	scene.Add(galagaTitle);

	std::shared_ptr<Object> singleplayerButton = std::make_shared<Object>();
	singleplayerButton->AddComponent(std::make_shared<TextComponent>(singleplayerButton, "SINGLEPLAYER", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 270.f });
	singleplayerButton->SetTransform(t);
	scene.Add(singleplayerButton);

	std::shared_ptr<Object> multiplayerButton = std::make_shared<Object>();
	multiplayerButton->AddComponent(std::make_shared<TextComponent>(multiplayerButton, "MULTIPLAYER", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 320.f });
	multiplayerButton->SetTransform(t);
	scene.Add(multiplayerButton);

	std::shared_ptr<Object> versusButton = std::make_shared<Object>();
	versusButton->AddComponent(std::make_shared<TextComponent>(versusButton, "VERSUS", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 370.f });
	versusButton->SetTransform(t);
	scene.Add(versusButton);

	std::shared_ptr<Object> quitButton = std::make_shared<Object>();
	quitButton->AddComponent(std::make_shared<TextComponent>(quitButton, "QUIT", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 420.f });
	quitButton->SetTransform(t);
	scene.Add(quitButton);
}