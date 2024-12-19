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

	sf::Texture brickTex;
	brickTex.loadFromFile("brick.png");

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
	ball->getComponent<PhysicsComponent>().setCollideObjectCallback([](GameObject &objA, PhysicsComponent &collA, GameObject &objB, PhysicsComponent &collB) -> bool {
		bool isBrick = objB.getUserData() == 1;
		sf::Vector2f v = collA.getVelocity();
		if (!isBrick) {
			v.x = 10.0F * (((objA.getPosition().x + 6.0F) - (objB.getPosition().x + 75.0F)));
		}
		v.y = -v.y;
		collA.setVelocity(v);
		return true;
	});
	ball->getComponent<PhysicsComponent>().setCollideScreenCallback([](GameObject &objA, PhysicsComponent &collA, int side) -> bool {
		sf::Vector2f v = collA.getVelocity();
		switch ((PhysicsSystem::ScreenSide) side)
		{
		case PhysicsSystem::ScreenSide::LEFT:   break;
		case PhysicsSystem::ScreenSide::TOP:    break;
		case PhysicsSystem::ScreenSide::RIGHT:  break;
		case PhysicsSystem::ScreenSide::BOTTOM: break;
		}
		collA.setVelocity(v);
		return true;
	});

	const sf::Vector2f brickSize(100.0f, 40.0f);
	const float spacing = 10.0f;
	const float startX = (window.getSize().x - (brickSize.x * 4 + spacing * 3)) / 2;
	const float startY = 50.0f;

	uint32_t color[] =
	{
		0xFF2020ff, 0xFF8020ff, 0xFFFF00ff, 0x20FF20ff, 0x22AAFFff, 0x1050FFff, 0x6020FFff
	};
	int n = 0;

	for (int row = 0; row < 2; ++row) {
		for (int col = 0; col < 4; ++col) {

			float posX = startX + col * (brickSize.x + spacing);
			float posY = startY + row * (brickSize.y + spacing);

			GameObject* brick = m_scene->instantiateObject();
			addComponents<RectSystem, PhysicsSystem, RenderSystem>(*brick);
			brick->setUserData(1);
			brick->setPosition(sf::Vector2f(posX, posY));
			brick->getComponent<RectComponent>().setColor(sf::Color(color[n % 7]));
			brick->getComponent<RectComponent>().setSize(brickSize);
			brick->getComponent<RectComponent>().setTexture(brickTex);
			brick->getComponent<PhysicsComponent>().setCollideObjectCallback([](GameObject &objA, PhysicsComponent &collA, GameObject &objB, PhysicsComponent &collB) -> bool {
				GameManager::getInstance().destroyObject(objA);
				return true;
			});

			n++;
		}
	}

	while (window.isOpen())
	{
		processPendingActions();

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

void GameManager::destroyObject(GameObject& obj)
{
	if (obj.isMarkedForDeletion()) return;

	obj.markForDeletion();
	m_markedForDeletion.push_back(obj);
}

GameObject *GameManager::getObjectByID(uint32_t id)
{
	return m_scene->getObjectByID(id);
}

void GameManager::processPendingActions()
{
	for (uint32_t id : m_markedForDeletion) {
		g_systems.remove(*m_scene->getObjectByID(id));
		m_scene->destroyObject(id);
	}
	m_markedForDeletion.clear();
}
