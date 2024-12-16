#include "GameManager.h"


GameManager& GameManager::getInstance()
{
	static GameManager inst;
	return inst;
}

GameManager::GameManager()
{

}

#include "Scene/Scene.h"
#include "Scene/GameObject.h"

void GameManager::run()
{
	sf::RenderWindow& window = m_renderSystem.getSfmlWindow();

	Scene scene;
	GameObject* obj = scene.instantiateObject();
	auto rc = obj->addComponent<RenderComponent>();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		m_renderSystem.update();
	}
}
