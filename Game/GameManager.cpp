#include "GameManager.h"

#include "Scene/Scene.h"
#include "Scene/GameObject.h"

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

	GameObject* ball = m_scene->instantiateObject();
	addComponents<CircleSystem, RenderSystem, PhysicsSystem>(*ball);
	ball->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	ball->getComponent<CircleComponent>().setColor(sf::Color::Red);
	ball->getComponent<CircleComponent>().setRadius(10);
	ball->getComponent<PhysicsComponent>().setVelocity(sf::Vector2f(80.0F, 80.0F));
	ball->getComponent<PhysicsComponent>().setCollideObjectCallback([](GameObject& objA, PhysicsComponent& collA, GameObject& objB, PhysicsComponent& collB) -> bool {
		sf::Vector2f v = collA.getVelocity();
		v.y = -v.y;
		collA.setVelocity(v);
		return true;
	});

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

		constexpr float PADDLE_SPEED = 3.0F;
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

		/*if (ball->getPosition().x <= 0 || ball->getPosition().x + 20 >= window.getSize().x)
		{
			ballVelocity.x = -ballVelocity.x;
		}
		if (ball->getPosition().y <= 0)
		{
			ballVelocity.y = -ballVelocity.y;
		}

		sf::FloatRect paddleBounds(paddle->getPosition().x, paddle->getPosition().y, paddle->getComponent<RectComponent>().getSizeX(), paddle->getComponent<RectComponent>().getSizeY());
		sf::FloatRect ballBounds = ball->getComponent<CircleComponent>().getShape()->getGlobalBounds();

		if (paddleBounds.intersects(ballBounds))
		{
			ballVelocity.y = -ballVelocity.y;
		}

		if (ball->getPosition().y > window.getSize().y)
		{
			ball->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
			ballVelocity = sf::Vector2f(3.0f, -3.0f);
		}*/


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
