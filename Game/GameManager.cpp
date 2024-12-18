#include "GameManager.h"

#include "Scene/Scene.h"
#include "Scene/GameObject.h"
#include <iostream>

GameManager &GameManager::getInstance()
{
	static GameManager inst;
	return inst;
}

GameManager::GameManager()
{
}

void GameManager::run()
{
	RenderSystem &renderSys = g_systems.getSystem<RenderSystem>();
	sf::RenderWindow &window = renderSys.getSfmlWindow();

	m_scene = std::make_unique<Scene>();

	GameObject *paddle = m_scene->instantiateObject();
	addComponents<RectSystem, RenderSystem, PhysicsSystem>(*paddle);
	paddle->setPosition(sf::Vector2f((window.getSize().x / 2), (window.getSize().y - 100)));
	paddle->getComponent<RectComponent>().setColor(sf::Color::Green);
	paddle->getComponent<RectComponent>().setSize(sf::Vector2f(150, 20));

	GameObject *ball = m_scene->instantiateObject();
	addComponents<CircleSystem, RenderSystem, PhysicsSystem>(*ball);
	ball->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	ball->getComponent<CircleComponent>().setColor(sf::Color::Red);
	ball->getComponent<CircleComponent>().setRadius(10);
	ball->getComponent<PhysicsComponent>().setVelocity(sf::Vector2f(300.0F, 300.0F));
	ball->getComponent<PhysicsComponent>().setCollideObjectCallback([](GameObject &objA, PhysicsComponent &collA, GameObject &objB, PhysicsComponent &collB) -> bool
																	{
		sf::Vector2f v = collA.getVelocity();
		v.y = -v.y;
		v.x = 10.0F * (((objA.getPosition().x + 6.0F) - (objB.getPosition().x + 75.0F)));
		collA.setVelocity(v);
		return true; });
	ball->getComponent<PhysicsComponent>().setCollideScreenCallback([](GameObject &objA, PhysicsComponent &collA, int side) -> bool
																	{
		sf::Vector2f v = collA.getVelocity();
		switch ((PhysicsSystem::ScreenSide) side)
		{
		case PhysicsSystem::ScreenSide::LEFT:   break;
		case PhysicsSystem::ScreenSide::TOP:    break;
		case PhysicsSystem::ScreenSide::RIGHT:  break;
		case PhysicsSystem::ScreenSide::BOTTOM: break;
		}
		collA.setVelocity(v);
		return true; });

	const sf::Vector2f brickSize(100.0f, 30.0f);
	const float spacing = 10.0f;
	const float startX = (window.getSize().x - (brickSize.x * 4 + spacing * 3)) / 2;
	const float startY = 50.0f;

	GameObject *brick = m_scene->instantiateObject();
	addComponents<RenderSystem, RectSystem>(*brick);
	brick->setPosition(sf::Vector2f(200, 100));
	brick->getComponent<RectComponent>().setColor(sf::Color::Blue);
	brick->getComponent<RectComponent>().setSize(brickSize);

	std::vector<GameObject *> bricks;

	 for (int row = 0; row < 2; ++row) {
		for (int col = 0; col < 4; ++col) {
			std::cout << "Creating brick at row " << row << ", col " << col << std::endl;

			float posX = startX + col * (brickSize.x + spacing);
			float posY = startY + row * (brickSize.y + spacing);

			GameObject* brick = m_scene->instantiateObject();
			if (!brick) {
				std::cerr << "Failed to create brick at row " << row << ", col " << col << std::endl;
				continue;
			}

			addComponents<RenderSystem, RectSystem>(*brick);
			brick->setPosition(sf::Vector2f(posX, posY));
			brick->getComponent<RectComponent>().setColor(sf::Color::Blue);
			brick->getComponent<RectComponent>().setSize(brickSize);
			std::cout << brick->getID() << std::endl;

			bricks.push_back(brick);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		constexpr float PADDLE_SPEED = 10.0F;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (paddle->getPosition().x > 0)
			{
				paddle->setPosition(paddle->getPosition() - sf::Vector2f(PADDLE_SPEED, 0));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (paddle->getPosition().x + 150 < window.getSize().x)
			{
				paddle->setPosition(paddle->getPosition() + sf::Vector2f(PADDLE_SPEED, 0));
			}
		}

		g_systems.getSystem<RectSystem>().update(0);
		g_systems.getSystem<CircleSystem>().update(0);

		g_systems.getSystem<PhysicsSystem>().update(1.0F / 60.0F);

		renderSys.update();
	}
}

GameObject *GameManager::getObjectByID(uint32_t id)
{
	return m_scene->getObjectByID(id);
}
