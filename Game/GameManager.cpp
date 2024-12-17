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

	Scene scene;
	GameObject* obj = scene.instantiateObject();
	auto rc = obj->addComponent<RenderComponent>();

	GameObject* obj2 = scene.instantiateObject();
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
