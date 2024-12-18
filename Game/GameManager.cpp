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
	addComponents<RenderSystem, PhysicsSystem>(*obj2);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		renderSys.update();
	}
}

GameObject* GameManager::getObjectByID(uint32_t id)
{
	return m_scene->getObjectByID(id);
}
