#pragma once

#include "System/SystemStorage.h"

#include <vector>

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
		return g_systems.get<T>(obj);
	}

	template<typename T>
	bool hasComponent(GameObject& obj)
	{
		return g_systems.has<T>(obj);
	}

	void destroyObject(GameObject& obj);

	GameObject* getObjectByID(uint32_t id);

	void processPendingActions();

	inline std::unique_ptr<Scene>& getScene() { return m_scene; }


private:

	SystemStorage g_systems;

	std::unique_ptr<Scene> m_scene;
	std::vector<uint32_t> m_markedForDeletion;
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
