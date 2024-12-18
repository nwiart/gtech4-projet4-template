#include "GameManager.h"

#include "Scene/Scene.h"
#include "Scene/GameObject.h"


GameManager& GameManager::getInstance()
{
	static GameManager inst;
	return inst;
}

GameManager::GameManager()
{

}

void GameManager::run()
{
	RenderSystem& renderSys = g_systems.getSystem<RenderSystem>();
	sf::RenderWindow& window = renderSys.getSfmlWindow();

	m_scene = std::make_unique<Scene>();

	//GameObject* obj = m_scene->instantiateObject();
	//auto rc = obj->addComponent<RenderComponent>();

	GameObject* obj2 = m_scene->instantiateObject();
	addComponents<RenderSystem, CircleSystem>(*obj2);

	GameObject* obj3 = m_scene->instantiateObject();
	addComponents<RenderSystem, CircleSystem>(*obj3);
	obj3->setPosition(sf::Vector2f( 200, 100));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		obj3->setPosition(obj3->getPosition() + sf::Vector2f(1, 0));

		g_systems.getSystem<RectSystem>().update(0);
		g_systems.getSystem<CircleSystem>().update(0);

		renderSys.update();
	}
}

GameObject* GameManager::getObjectByID(uint32_t id)
{
	return m_scene->getObjectByID(id);
}
