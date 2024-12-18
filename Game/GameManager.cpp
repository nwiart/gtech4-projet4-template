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
	addComponents<RenderSystem, RectSystem>(*paddle);
	paddle->setPosition(sf::Vector2f((window.getSize().x / 2), (window.getSize().y - 100)));
	paddle->getComponent<RectComponent>().setColor(sf::Color::Green);
	paddle->getComponent<RectComponent>().setSize(sf::Vector2f(150, 20));

	GameObject* ball = m_scene->instantiateObject();
	addComponents<RenderSystem, CircleSystem>(*ball);
	ball->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	ball->getComponent<CircleComponent>().setColor(sf::Color::Red);
	ball->getComponent<CircleComponent>().setRadius(10);

	sf::Vector2f ballVelocity(3.0f, -3.0f);

	//GameObject *obj3 = m_scene->instantiateObject();
	//addComponents<RenderSystem, CircleSystem>(*obj3);
	//obj3->setPosition(sf::Vector2f(200, 100));

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

		//if (obj3)
		//{
		//	obj3->setPosition(obj3->getPosition() + sf::Vector2f(1, 0));

		//	if (obj3->getPosition().x > 300)
		//	{
		//		g_systems.remove(*obj3);
		//		m_scene->destroyObject(obj3);
		//		obj3 = 0;
		//	}
		//}

		ball->setPosition(ball->getPosition() + ballVelocity);

		if (ball->getPosition().x <= 0 || ball->getPosition().x + 20 >= window.getSize().x)
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
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (paddle->getPosition().x > 0)
			{
				paddle->setPosition(paddle->getPosition() - sf::Vector2f(3.0f, 0));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (paddle->getPosition().x + 150 < window.getSize().x)
			{
				paddle->setPosition(paddle->getPosition() + sf::Vector2f(3.0f, 0));
			}
		}

		g_systems.getSystem<RectSystem>().update(0);
		g_systems.getSystem<CircleSystem>().update(0);

		renderSys.update();
	}
}

GameObject *GameManager::getObjectByID(uint32_t id)
{
	return m_scene->getObjectByID(id);
}
