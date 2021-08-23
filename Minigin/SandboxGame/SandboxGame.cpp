#include "SandboxGame.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Renderer.h"
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
#include "HitboxRectangleComponent.h"
#include "EnemyComponent.h"
#include "EnemyManagerComponent.h"
#include "GameOverScreenComponent.h"
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
	LoadGameOver();
	LoadGame(Gamemode::Singleplayer, true);

	SceneManager::GetInstance().SetCurrentScene("MainMenu");
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
		gameLogic->AddComponent(std::make_shared<SceneSwapComponent>(gameLogic, "PauseMenu"));
		game.Add(gameLogic);

		std::shared_ptr<Object> bulletManager = std::make_shared<Object>();
		int w, h;
		Renderer::GetInstance().GetWindowSize(w, h);
		std::shared_ptr<HitboxRectangleComponent> wHitbox = std::make_shared<HitboxRectangleComponent>(bulletManager, float(w), float(h), float(w) / 2.f, float(h) / 2.f);
		bulletManager->AddComponent(wHitbox);
		bulletManager->AddComponent(std::make_shared<BulletManagerComponent>(bulletManager, 20, wHitbox));
		game.Add(bulletManager);

		//enemies
		std::shared_ptr<Object> enemyManager = std::make_shared<Object>();
		enemyManager->AddComponent(std::make_shared<SceneSwapComponent>(enemyManager, "GameOverScreen"));
		enemyManager->AddComponent(std::make_shared<EnemyManagerComponent>(enemyManager, bulletManager->GetComponent<BulletManagerComponent>(), 10, false));
		game.Add(enemyManager);

		//players
		std::shared_ptr<Object> starfighter1 = std::make_shared<Object>();
		std::shared_ptr<Object> starfighter2 = std::make_shared<Object>();


		switch (gamemode)
		{
		case Gamemode::Singleplayer:
			starfighter1->AddComponent(std::make_shared<TextureComponent>(starfighter1, "StarfighterWhite.png"));
			starfighter1->AddComponent(std::make_shared<SpriteComponent>(starfighter1, "StarfighterExplosion.png", 4, 0.6f));
			starfighter1->AddComponent(std::make_shared<SceneSwapComponent>(starfighter1, "GameOverScreen"));
			starfighter1->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter1, 13.f));
			starfighter1->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter1, bulletManager->GetComponent<BulletManagerComponent>(), enemyManager->GetComponent<EnemyManagerComponent>(), true, true));
			t.SetPosition(Position2D{ 320.f, 440.f });
			starfighter1->SetTransform(t);
			game.Add(starfighter1);

			break;
		case Gamemode::Multiplayer:
			starfighter1->AddComponent(std::make_shared<TextureComponent>(starfighter1, "StarfighterWhite.png"));
			starfighter1->AddComponent(std::make_shared<SpriteComponent>(starfighter1, "StarfighterExplosion.png", 4, 0.6f));
			starfighter1->AddComponent(std::make_shared<SceneSwapComponent>(starfighter1, "GameOverScreen"));
			starfighter1->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter1, 13.f));
			starfighter1->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter1, bulletManager->GetComponent<BulletManagerComponent>(), enemyManager->GetComponent<EnemyManagerComponent>(), false, true));
			t.SetPosition(Position2D{ 320.f, 440.f });
			starfighter1->SetTransform(t);
			game.Add(starfighter1);

			starfighter2->AddComponent(std::make_shared<TextureComponent>(starfighter2, "StarfighterWhite.png"));
			starfighter2->AddComponent(std::make_shared<SpriteComponent>(starfighter2, "StarfighterExplosion.png", 4, 0.6f));
			starfighter2->AddComponent(std::make_shared<SceneSwapComponent>(starfighter2, "GameOverScreen"));
			starfighter2->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter2, 13.f));
			starfighter2->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter2, bulletManager->GetComponent<BulletManagerComponent>(), enemyManager->GetComponent<EnemyManagerComponent>(), false, false));
			t.SetPosition(Position2D{ 320.f, 440.f });
			starfighter2->SetTransform(t);
			game.Add(starfighter2);

			break;
		case Gamemode::Versus:
			starfighter1->AddComponent(std::make_shared<TextureComponent>(starfighter1, "StarfighterWhite.png"));
			starfighter1->AddComponent(std::make_shared<SpriteComponent>(starfighter1, "StarfighterExplosion.png", 4, 0.6f));
			starfighter1->AddComponent(std::make_shared<SceneSwapComponent>(starfighter1, "GameOverScreen")); 
			starfighter1->AddComponent(std::make_shared<HitboxCircleComponent>(starfighter1, 13.f));
			starfighter1->AddComponent(std::make_shared<PlayerControllerComponent>(starfighter1, bulletManager->GetComponent<BulletManagerComponent>(), enemyManager->GetComponent<EnemyManagerComponent>(), false, true));
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

void SandboxGame::LoadGameOver()
{
	//GAME END
	Scene& EndScreen = SceneManager::GetInstance().CreateScene("GameOverScreen");

	Transform t{};

	std::shared_ptr<Object> galagaVisual = std::make_shared<Object>();
	galagaVisual->AddComponent(std::make_shared<TextureComponent>(galagaVisual, "GalagaLogo.png"));
	galagaVisual->AddComponent(std::make_shared<SceneSwapComponent>(galagaVisual, "MainMenu"));
	galagaVisual->AddComponent(std::make_shared<GameOverScreenComponent>(galagaVisual));
	t.SetPosition(Position2D{ 320.f, 130.f });
	galagaVisual->SetTransform(t);
	EndScreen.Add(galagaVisual);

	std::shared_ptr<Object> gameOverVisual = std::make_shared<Object>();
	gameOverVisual->AddComponent(std::make_shared<TextComponent>(gameOverVisual, "GAME OVER", "Emulogic.ttf", 24, 220, 220, 0));
	t.SetPosition(Position2D{ 320.f, 270.f });
	gameOverVisual->SetTransform(t);
	EndScreen.Add(gameOverVisual);
}
