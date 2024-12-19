#include "GameManager.h"

#include "Scene/GameObject.h"

#include "SceneBreakout.h"

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

	m_scene = std::make_unique<SceneBreakout>();
	
	m_scene->load();
	m_scene->spawn();


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

		m_scene->update();

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
