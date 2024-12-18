#pragma once

#include "System/SystemStorage.h"

class Scene;
class GameObject;


class GameManager
{
public:

	static GameManager& getInstance();

	GameManager();

	GameManager(const GameManager&) = delete;

	void run();

	template<typename... Systems>
	void addComponents(GameObject& obj)
	{
		g_systems.add<Systems...>(obj);
	}

	template<typename T>
	T* addComponentToObject(GameObject& obj) { return 0; }

	template<typename T>
	T& getObjectComponent(GameObject& obj)
	{
		g_systems.get<T>(obj);
	}

	GameObject* getObjectByID(uint32_t id);


private:

	SystemStorage g_systems;

	std::unique_ptr<Scene> m_scene;
};


/*template<typename T>
T* GameManager::addComponentToObject(GameObject& obj)
{
	//static_assert(0);
	return 0;
}

template<>
RenderComponent* GameManager::addComponentToObject<RenderComponent>(GameObject& obj)
{
	return m_renderSystem.add(obj);
}*/
