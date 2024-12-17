#pragma once

#include "System/SystemStorage.h"

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


private:

	SystemStorage g_systems;
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
