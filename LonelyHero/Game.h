#pragma once

#include <vector>
#include "Player.h"
#include "Ground.h"
#include <fstream>
#include <utility>
#include "Enemy.h"
#include <thread>

class Game
{
public:
	Game();
	~Game();

	void init();
	void update();
	void render();
	void run();

	void updateCollision();

	void loadAndCreateMap(const std::string& mapFilePath);

	void updateTexturesAndAnimations();

	static bool isRunning;

private:
	sf::RenderWindow m_window{ sf::VideoMode(constants::screenWidth, constants::screenHeight), "Lonely Hero" };

	sf::Clock m_clock{};
	sf::Event m_event{};
	float m_deltaTime{};

	Player m_player{ constants::playerSpriteWidth, constants::playerSpriteHeight, constants::playerIdleAnimationFramesAmount, constants::playerShapeWidth, constants::playerShapeHeight, constants::playerSpriteScale, sf::Vector2f{constants::playerFirstPositionX, constants::playerFirstPositionY}, "playerIdle", "./_Idle.png"};
	std::vector<Ground> grounds{};
	
	sf::View m_view{sf::Vector2f{0.f, 0.f}, sf::Vector2f{450.f, 450.f}};

	std::thread playerAnimationThread;

	Enemy m_enemy{ constants::skeletonSpriteWidth, constants::skeletonSpriteHeight, constants::skeletonIdleAnimationFramesAmount, constants::skeletonShapeWidth, constants::skeletonShapeHeight, constants::skeletonSpriteScale, sf::Vector2f{constants::skeletonFirstPositionX, constants::skeletonFirstPositionY}, "skeletonIdle", "./SkeletonIdle.png" };
};
