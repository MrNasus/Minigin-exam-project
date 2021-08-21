#include "SandboxGame.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Object.h"
#include "TextureComponent.h"
#include "MoveComponent.h"
#include "TextComponent.h"
#include "SpriteComponent.h"
#include "ServiceLocator.h"
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
	SceneManager* sceneManager = ServiceLocator<SceneManager>::getService();
	Transform t{};
	//MAIN MENU
	Scene& mainMenu = sceneManager->CreateScene("Menu");

	std::shared_ptr<Object> galagaTitle = std::make_shared<Object>();
	galagaTitle->AddComponent(std::make_shared<TextureComponent>(galagaTitle, "GalagaLogo.png"));
	t.SetPosition(Position2D{ 320.f, 130.f });
	galagaTitle->SetTransform(t);
	mainMenu.Add(galagaTitle);

	std::shared_ptr<Object> singleplayerButton = std::make_shared<Object>();
	singleplayerButton->AddComponent(std::make_shared<TextComponent>(singleplayerButton, "SINGLEPLAYER", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 270.f });
	singleplayerButton->SetTransform(t);
	mainMenu.Add(singleplayerButton);

	std::shared_ptr<Object> multiplayerButton = std::make_shared<Object>();
	multiplayerButton->AddComponent(std::make_shared<TextComponent>(multiplayerButton, "MULTIPLAYER", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 320.f });
	multiplayerButton->SetTransform(t);
	mainMenu.Add(multiplayerButton);

	std::shared_ptr<Object> versusButton = std::make_shared<Object>();
	versusButton->AddComponent(std::make_shared<TextComponent>(versusButton, "VERSUS", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 370.f });
	versusButton->SetTransform(t);
	mainMenu.Add(versusButton);

	std::shared_ptr<Object> quitButton = std::make_shared<Object>();
	quitButton->AddComponent(std::make_shared<TextComponent>(quitButton, "QUIT", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 420.f });
	quitButton->SetTransform(t);
	mainMenu.Add(quitButton);

	//GAME
	Scene& game = sceneManager->CreateScene("Game");

	std::shared_ptr<Object> starfighter = std::make_shared<Object>();
	starfighter->AddComponent(std::make_shared<TextureComponent>(starfighter, "StarfighterWhite.png"));
	t.SetPosition(Position2D{ 320.f, 440.f });
	starfighter->SetTransform(t);
	game.Add(starfighter);

	std::shared_ptr<Object> starfighterExplosion = std::make_shared<Object>();
	starfighterExplosion->AddComponent(std::make_shared<SpriteComponent>(starfighterExplosion, "StarfighterExplosion.png", 4, 0.6f));
	t.SetPosition(Position2D{ 270.f, 440.f });
	starfighterExplosion->SetTransform(t);
	game.Add(starfighterExplosion);

	std::shared_ptr<Object> boss = std::make_shared<Object>();
	boss->AddComponent(std::make_shared<SpriteComponent>(boss, "BossGreen.png", 2, 0.4f));
	t.SetPosition(Position2D{ 320.f, 40.f });
	boss->SetTransform(t);
	game.Add(boss);

	std::shared_ptr<Object> bossDamaged = std::make_shared<Object>();
	bossDamaged->AddComponent(std::make_shared<SpriteComponent>(bossDamaged, "BossBlue.png", 2, 0.4f));
	t.SetPosition(Position2D{ 280.f, 40.f });
	bossDamaged->SetTransform(t);
	game.Add(bossDamaged);

	std::shared_ptr<Object> goei = std::make_shared<Object>();
	goei->AddComponent(std::make_shared<SpriteComponent>(goei, "Goei.png", 2, 0.4f));
	t.SetPosition(Position2D{ 320.f, 80.f });
	goei->SetTransform(t);
	game.Add(goei);

	std::shared_ptr<Object> zako = std::make_shared<Object>();
	zako->AddComponent(std::make_shared<SpriteComponent>(zako, "Zako.png", 2, 0.4f));
	t.SetPosition(Position2D{ 320.f, 120.f });
	zako->SetTransform(t);
	game.Add(zako);

	std::shared_ptr<Object> galagaExplosion = std::make_shared<Object>();
	galagaExplosion->AddComponent(std::make_shared<SpriteComponent>(galagaExplosion, "GalagaExplosion.png", 5, 0.25f));
	t.SetPosition(Position2D{ 270.f, 100.f });
	galagaExplosion->SetTransform(t);
	game.Add(galagaExplosion);


	//PAUSE SCREEN
	Scene& pauseMenu = sceneManager->CreateScene("Pause");

	std::shared_ptr<Object> resumeButton = std::make_shared<Object>();
	resumeButton->AddComponent(std::make_shared<TextComponent>(resumeButton, "RESUME", "Emulogic.ttf", 30, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 160.f });
	resumeButton->SetTransform(t);
	pauseMenu.Add(resumeButton);

	std::shared_ptr<Object> menuButton = std::make_shared<Object>();
	menuButton->AddComponent(std::make_shared<TextComponent>(menuButton, "MAIN MENU", "Emulogic.ttf", 30, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 300.f });
	menuButton->SetTransform(t);
	pauseMenu.Add(menuButton);

	//GAME END
	Scene& GameEnd = sceneManager->CreateScene("End");

	std::shared_ptr<Object> galagaVisual = std::make_shared<Object>();
	galagaVisual->AddComponent(std::make_shared<TextureComponent>(galagaVisual, "GalagaLogo.png"));
	t.SetPosition(Position2D{ 320.f, 130.f });
	galagaVisual->SetTransform(t);
	GameEnd.Add(galagaVisual);

	std::shared_ptr<Object> resultVisual = std::make_shared<Object>();
	resultVisual->AddComponent(std::make_shared<TextComponent>(resultVisual, "---RESULT---", "Emulogic.ttf", 24, 220, 220, 0));
	t.SetPosition(Position2D{ 320.f, 270.f });
	resultVisual->SetTransform(t);
	GameEnd.Add(resultVisual);

	std::shared_ptr<Object> totalShotsVisual = std::make_shared<Object>();
	totalShotsVisual->AddComponent(std::make_shared<TextComponent>(totalShotsVisual, "TOTAL SHOTS: 100", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 320.f });
	totalShotsVisual->SetTransform(t);
	GameEnd.Add(totalShotsVisual);

	std::shared_ptr<Object> shotsHitVisual = std::make_shared<Object>();
	shotsHitVisual->AddComponent(std::make_shared<TextComponent>(shotsHitVisual, "SHOTS HIT: 36", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 370.f });
	shotsHitVisual->SetTransform(t);
	GameEnd.Add(shotsHitVisual);

	std::shared_ptr<Object> hitMissVisual = std::make_shared<Object>();
	hitMissVisual->AddComponent(std::make_shared<TextComponent>(hitMissVisual, "HIT MISS RATIO: 36%", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 420.f });
	hitMissVisual->SetTransform(t);
	GameEnd.Add(hitMissVisual);



	sceneManager->SetCurrentScene("Pause");

	std::cout << "Sandbox game loaded\n";
}