#include "SandboxGame.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Object.h"
#include "TextureComponent.h"
#include "MoveComponent.h"
#include "TextComponent.h"
#include "SpriteComponent.h"
#include "SceneSwapComponent.h"
#include "MenuLogicComponent.h"
#include "GameLogicComponent.h"
#include "PlayerControllerComponent.h"
#include "HitboxCircleComponent.h"
#include <memory>
#include <iostream>
#include <vector>

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
	LoadMainMenu();
	LoadPauseMenu();

	LoadGame(Gamemode::Multiplayer, true);
	//GAME
	Transform t{};

	//Scene& game = SceneManager::GetInstance().CreateScene("Game");


	//std::shared_ptr<Object> starfighterExplosion = std::make_shared<Object>();
	//starfighterExplosion->AddComponent(std::make_shared<SpriteComponent>(starfighterExplosion, "StarfighterExplosion.png", 4, 0.6f));
	//t.SetPosition(Position2D{ 270.f, 440.f });
	//starfighterExplosion->SetTransform(t);
	//game.Add(starfighterExplosion);

	//std::shared_ptr<Object> boss = std::make_shared<Object>();
	//boss->AddComponent(std::make_shared<SpriteComponent>(boss, "BossGreen.png", 2, 0.4f));
	//t.SetPosition(Position2D{ 320.f, 40.f });
	//boss->SetTransform(t);
	//game.Add(boss);

	//std::shared_ptr<Object> bossDamaged = std::make_shared<Object>();
	//bossDamaged->AddComponent(std::make_shared<SpriteComponent>(bossDamaged, "BossBlue.png", 2, 0.4f));
	//t.SetPosition(Position2D{ 280.f, 40.f });
	//bossDamaged->SetTransform(t);
	//game.Add(bossDamaged);

	//std::shared_ptr<Object> goei = std::make_shared<Object>();
	//goei->AddComponent(std::make_shared<SpriteComponent>(goei, "Goei.png", 2, 0.4f));
	//t.SetPosition(Position2D{ 320.f, 80.f });
	//goei->SetTransform(t);
	//game.Add(goei);

	//std::shared_ptr<Object> zako = std::make_shared<Object>();
	//zako->AddComponent(std::make_shared<SpriteComponent>(zako, "Zako.png", 2, 0.4f));
	//t.SetPosition(Position2D{ 320.f, 120.f });
	//zako->SetTransform(t);
	//game.Add(zako);

	//std::shared_ptr<Object> galagaExplosion = std::make_shared<Object>();
	//galagaExplosion->AddComponent(std::make_shared<SpriteComponent>(galagaExplosion, "GalagaExplosion.png", 5, 0.25f));
	//t.SetPosition(Position2D{ 270.f, 100.f });
	//galagaExplosion->SetTransform(t);
	//game.Add(galagaExplosion);



	//GAME END
	Scene& EndScreen = SceneManager::GetInstance().CreateScene("EndScreen");

	std::shared_ptr<Object> galagaVisual = std::make_shared<Object>();
	galagaVisual->AddComponent(std::make_shared<TextureComponent>(galagaVisual, "GalagaLogo.png"));
	t.SetPosition(Position2D{ 320.f, 130.f });
	galagaVisual->SetTransform(t);
	EndScreen.Add(galagaVisual);

	std::shared_ptr<Object> resultVisual = std::make_shared<Object>();
	resultVisual->AddComponent(std::make_shared<TextComponent>(resultVisual, "---RESULT---", "Emulogic.ttf", 24, 220, 220, 0));
	t.SetPosition(Position2D{ 320.f, 270.f });
	resultVisual->SetTransform(t);
	EndScreen.Add(resultVisual);

	std::shared_ptr<Object> totalShotsVisual = std::make_shared<Object>();
	totalShotsVisual->AddComponent(std::make_shared<TextComponent>(totalShotsVisual, "TOTAL SHOTS: 100", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 320.f });
	totalShotsVisual->SetTransform(t);
	EndScreen.Add(totalShotsVisual);

	std::shared_ptr<Object> shotsHitVisual = std::make_shared<Object>();
	shotsHitVisual->AddComponent(std::make_shared<TextComponent>(shotsHitVisual, "SHOTS HIT: 36", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 370.f });
	shotsHitVisual->SetTransform(t);
	EndScreen.Add(shotsHitVisual);

	std::shared_ptr<Object> hitMissVisual = std::make_shared<Object>();
	hitMissVisual->AddComponent(std::make_shared<TextComponent>(hitMissVisual, "HIT MISS RATIO: 36%", "Emulogic.ttf", 24, 220, 220, 220));
	t.SetPosition(Position2D{ 320.f, 420.f });
	hitMissVisual->SetTransform(t);
	EndScreen.Add(hitMissVisual);



	SceneManager::GetInstance().SetCurrentScene("MainMenu");

	std::cout << "Sandbox game loaded\n";
}

void SandboxGame::LoadGame(Gamemode gamemode, bool reload)
{
	if (reload)
	{
		SceneManager::GetInstance().RemoveScene("Game");
	}
	std::shared_ptr<Scene> scene = nullptr;
	if (!SceneManager::GetInstance().GetScene("Game", scene))
	{
		Transform t{};

		Scene& game = SceneManager::GetInstance().CreateScene("Game");
		std::shared_ptr<Object> gameLogic = std::make_shared<Object>();
		gameLogic->AddComponent(std::make_shared<GameLogicComponent>(gameLogic));
		game.Add(gameLogic);

		std::shared_ptr<Object> starfighter1 = std::make_shared<Object>();
		std::shared_ptr<Object> starfighter2 = std::make_shared<Object>();


		switch (gamemode)
		{
		case Gamemode::Singleplayer:
			starfighter1->AddComponent(std::make_shared<TextureComponent>(starfighter1, "StarfighterWhite.png"));
			starfighter1->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter1, true, true));
			starfighter1->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter1, 13.f));
			t.SetPosition(Position2D{ 320.f, 440.f });
			starfighter1->SetTransform(t);
			game.Add(starfighter1);

			break;
		case Gamemode::Multiplayer:
			starfighter1->AddComponent(std::make_shared<TextureComponent>(starfighter1, "StarfighterWhite.png"));
			starfighter1->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter1, false, true));
			starfighter1->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter1, 13.f));
			t.SetPosition(Position2D{ 320.f, 440.f });
			starfighter1->SetTransform(t);
			game.Add(starfighter1);

			starfighter2->AddComponent(std::make_shared<TextureComponent>(starfighter2, "StarfighterWhite.png"));
			starfighter2->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter2, false, false));
			starfighter2->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter2, 13.f));
			t.SetPosition(Position2D{ 320.f, 440.f });
			starfighter2->SetTransform(t);
			game.Add(starfighter2);

			break;
		case Gamemode::Versus:
			starfighter1->AddComponent(std::make_shared<TextureComponent>(starfighter1, "StarfighterWhite.png"));
			starfighter1->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter1, false, true));
			starfighter1->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter1, 13.f));
			t.SetPosition(Position2D{ 320.f, 440.f });
			starfighter1->SetTransform(t);
			game.Add(starfighter1);

			break;
		default:
			break;
		}
	}
	SceneManager::GetInstance().SetCurrentScene("Game");
}

void SandboxGame::LoadMainMenu()
{
	Transform t{};
	//MAIN MENU
	Scene& mainMenu = SceneManager::GetInstance().CreateScene("MainMenu");

	std::shared_ptr<Object> galagaTitle = std::make_shared<Object>();
	galagaTitle->AddComponent(std::make_shared<TextureComponent>(galagaTitle, "GalagaLogo.png"));
	t.SetPosition(Position2D{ 320.f, 130.f });
	galagaTitle->SetTransform(t);
	mainMenu.Add(galagaTitle);

	std::shared_ptr<Object> singleplayerButton = std::make_shared<Object>();
	singleplayerButton->AddComponent(std::make_shared<TextComponent>(singleplayerButton, "SINGLEPLAYER", "Emulogic.ttf", 24, 220, 220, 220, "UnselectedVisual"));
	singleplayerButton->AddComponent(std::make_shared<TextComponent>(singleplayerButton, "SINGLEPLAYER", "Emulogic.ttf", 30, 5, 100, 50, "SelectedVisual"));
	singleplayerButton->AddComponent(std::make_shared<SceneSwapComponent>(singleplayerButton, "Game"));
	t.SetPosition(Position2D{ 320.f, 270.f });
	singleplayerButton->SetTransform(t);
	mainMenu.Add(singleplayerButton);

	std::shared_ptr<Object> multiplayerButton = std::make_shared<Object>();
	multiplayerButton->AddComponent(std::make_shared<TextComponent>(multiplayerButton, "MULTIPLAYER", "Emulogic.ttf", 24, 220, 220, 220, "UnselectedVisual"));
	multiplayerButton->AddComponent(std::make_shared<TextComponent>(multiplayerButton, "MULTIPLAYER", "Emulogic.ttf", 30, 5, 100, 50, "SelectedVisual"));
	multiplayerButton->AddComponent(std::make_shared<SceneSwapComponent>(multiplayerButton, "Game"));
	t.SetPosition(Position2D{ 320.f, 320.f });
	multiplayerButton->SetTransform(t);
	mainMenu.Add(multiplayerButton);

	std::shared_ptr<Object> versusButton = std::make_shared<Object>();
	versusButton->AddComponent(std::make_shared<TextComponent>(versusButton, "VERSUS", "Emulogic.ttf", 24, 220, 220, 220, "UnselectedVisual"));
	versusButton->AddComponent(std::make_shared<TextComponent>(versusButton, "VERSUS", "Emulogic.ttf", 30, 5, 100, 50, "SelectedVisual"));
	versusButton->AddComponent(std::make_shared<SceneSwapComponent>(versusButton, "Game"));
	t.SetPosition(Position2D{ 320.f, 370.f });
	versusButton->SetTransform(t);
	mainMenu.Add(versusButton);

	std::shared_ptr<Object> quitButton = std::make_shared<Object>();
	quitButton->AddComponent(std::make_shared<TextComponent>(quitButton, "QUIT", "Emulogic.ttf", 24, 220, 220, 220, "UnselectedVisual"));
	quitButton->AddComponent(std::make_shared<TextComponent>(quitButton, "QUIT", "Emulogic.ttf", 30, 5, 100, 50, "SelectedVisual"));
	quitButton->AddComponent(std::make_shared<SceneSwapComponent>(quitButton, "Quit"));
	t.SetPosition(Position2D{ 320.f, 420.f });
	quitButton->SetTransform(t);
	mainMenu.Add(quitButton);

	std::vector<std::shared_ptr<Object>> pButtons{};
	pButtons.push_back(singleplayerButton);
	pButtons.push_back(multiplayerButton);
	pButtons.push_back(versusButton);
	pButtons.push_back(quitButton);

	std::shared_ptr<Object> menuLogic = std::make_shared<Object>();
	menuLogic->AddComponent(std::make_shared<MenuLogicComponent>(menuLogic, pButtons));
	mainMenu.Add(menuLogic);
}

void SandboxGame::LoadPauseMenu()
{
	Transform t{};
	//PAUSE SCREEN
	Scene& pauseMenu = SceneManager::GetInstance().CreateScene("PauseMenu");

	std::shared_ptr<Object> resumeButton = std::make_shared<Object>();
	resumeButton->AddComponent(std::make_shared<TextComponent>(resumeButton, "RESUME", "Emulogic.ttf", 28, 220, 220, 220, "UnselectedVisual"));
	resumeButton->AddComponent(std::make_shared<TextComponent>(resumeButton, "RESUME", "Emulogic.ttf", 35, 5, 100, 50, "SelectedVisual"));
	resumeButton->AddComponent(std::make_shared<SceneSwapComponent>(resumeButton, "Game"));
	t.SetPosition(Position2D{ 320.f, 160.f });
	resumeButton->SetTransform(t);
	pauseMenu.Add(resumeButton);

	std::shared_ptr<Object> menuButton = std::make_shared<Object>();
	menuButton->AddComponent(std::make_shared<TextComponent>(menuButton, "MAIN MENU", "Emulogic.ttf", 28, 220, 220, 220, "UnselectedVisual"));
	menuButton->AddComponent(std::make_shared<TextComponent>(menuButton, "MAIN MENU", "Emulogic.ttf", 35, 5, 100, 50, "SelectedVisual"));
	menuButton->AddComponent(std::make_shared<SceneSwapComponent>(menuButton, "MainMenu"));
	t.SetPosition(Position2D{ 320.f, 300.f });
	menuButton->SetTransform(t);
	pauseMenu.Add(menuButton);

	std::vector<std::shared_ptr<Object>> pButtons{};
	pButtons.push_back(resumeButton);
	pButtons.push_back(menuButton);

	std::shared_ptr<Object> menuLogic = std::make_shared<Object>();
	menuLogic->AddComponent(std::make_shared<MenuLogicComponent>(menuLogic, pButtons));
	pauseMenu.Add(menuLogic);

}
