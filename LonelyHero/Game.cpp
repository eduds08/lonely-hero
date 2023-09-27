#include "Game.h"

Game::Game()
{
	init();
}

Game::~Game()
{
}

void Game::init()
{
	m_window.setView(m_view);
	loadAndCreateMap("./teste2.txt");
	t = std::thread(&Player::updateTextureAndAnimation, std::ref(m_player));
	run();
}

void Game::update()
{
	m_player.update(m_deltaTime);
	
	updateCollision();
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
}

void Game::render()
{
	m_window.clear();

	m_window.draw(m_player.getShape());
	m_window.draw(m_player.getSprite());

	for (auto const& ground : grounds)
	{
		m_window.draw(ground.getSprite());
	}

	m_window.display();
}

void Game::run()
{
	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart().asSeconds();

		if (m_deltaTime > 1.f / 20.f)
		{
			m_deltaTime = { 1.f / 20.f };
		}

		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				m_player.isRunning = false;
				m_window.close();
			}
		}

		update();
		render();
	}

	t.join();
}

void Game::updateCollision()
{
	for (const auto& ground : grounds)
	{
		if (m_player.isColliding(ground.getSprite()))
		{
			m_player.handleCollision();
			m_player.checkIfCanJump();
		}
	}
}

void Game::loadAndCreateMap(const std::string& mapFilePath)
{
	std::fstream mapFile{ mapFilePath, std::ios::in };
	std::string row{};

	int x{ 0 };
	int y{ 0 };

	std::string a{};

	while (std::getline(mapFile, row))
	{
		for (int i = 0; i < 40; i++)
		{
			mapFile >> a;
			if (a != "0")
			{
				grounds.emplace_back(Ground{ 16, 16, sf::Vector2f{x * 16.f + 8.f, y * 16.f + 8.f}, a,  "./tiles/" + a + ".png" });
			}
			++x;
		}
		
		x = 0;
		y++;
	}

	mapFile.close();
}
