#pragma once

#include "System/PhysicsSystem.h"
#include "System/RenderSystem.h"

class GameObject;


template<typename ProcessType>
class ProcessWrapper
{
public:

	void add(GameObject& obj)
	{
		m_data.add(obj);
	}

	inline ProcessType& getInstance() { return m_data; }

private:

	ProcessType m_data;
};

template<typename... ProcessType>
class ProcessStorage
	: public ProcessWrapper<ProcessType>...
{
public:

	template<typename... Components>
	void addC(GameObject& obj)
	{
		getProcess<ProcessType::Components...>().add(obj);
	}

	template<typename... SystemT>
	void add(GameObject& obj)
	{
		(ProcessWrapper<SystemT>::add(obj), ...);
	}

	template<typename... Components>
	void remove(GameObject& obj)
	{
		getProcess<ProcessType::Components...>().remove(obj);
	}
	
	template<typename SystemType>
	inline SystemType& getProcess() { return ProcessWrapper<SystemType>::getInstance(); }
};


class GameManager
{
public:

	static GameManager& getInstance();

	GameManager();

	GameManager(const GameManager&) = delete;

	void run();

	template<typename... SystemT>
	void addComponents(GameObject& obj)
	{
		g_processes.add<SystemT...>(obj);
	}

	template<typename T>
	T* addComponentToObject(GameObject& obj) { return 0; }


private:

	ProcessStorage<
		PhysicsSystem,
		RenderSystem
	>
	g_processes;
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
