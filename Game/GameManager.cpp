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
	paddle->setPosition(sf::Vector2f((window.getSize().x - 100), (window.getSize().y - 100)));
	paddle->getComponent<RectComponent>().setColor(sf::Color::Green);
	paddle->getComponent<RectComponent>().setSize(sf::Vector2f(100, 20));

	GameObject *obj2 = m_scene->instantiateObject();
	addComponents<RenderSystem, CircleSystem>(*obj2);

	GameObject *obj3 = m_scene->instantiateObject();
	addComponents<RenderSystem, CircleSystem>(*obj3);
	obj3->setPosition(sf::Vector2f(200, 100));

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

		if (obj3)
		{
			obj3->setPosition(obj3->getPosition() + sf::Vector2f(1, 0));

			if (obj3->getPosition().x > 300)
			{
				g_systems.remove(*obj3);
				m_scene->destroyObject(obj3);
				obj3 = 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{

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
