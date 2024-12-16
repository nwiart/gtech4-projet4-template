#pragma once

#include "System/RenderSystem.h"

class GameObject;


class GameManager
{
public:

	static GameManager& getInstance();

	GameManager();

	GameManager(const GameManager&) = delete;

	void run();

	template<typename T>
	T* addComponentToObject(GameObject& obj);


private:

	RenderSystem m_renderSystem;
};


template<typename T>
T* GameManager::addComponentToObject(GameObject& obj)
{
	static_assert(0);
	return 0;
}

template<>
RenderComponent* GameManager::addComponentToObject<RenderComponent>(GameObject& obj)
{
	return m_renderSystem.add(obj);
}
