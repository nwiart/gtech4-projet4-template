#pragma once

class GameObject;


template<typename SystemType>
class SystemData
{
public:

	inline void add(GameObject& obj) { m_data.add(obj); }

	inline void remove(GameObject& obj) { m_data.remove(obj); }

	inline SystemType& getInstance() { return m_data; }

private:

	SystemType m_data;
};


template<typename... ProcessType>
class SystemStorageBase
	: public SystemData<ProcessType>...
{
public:

	template<typename... Components>
	void addC(GameObject& obj)
	{
		getProcess<ProcessType::Components...>().add(obj);
	}

	template<typename... Systems>
	void add(GameObject& obj)
	{
		(SystemData<Systems>::add(obj), ...);
	}

	template<typename... Systems>
	void remove(GameObject& obj)
	{
		(SystemData<Systems>::remove(obj), ...);
	}

	template<typename SystemType>
	inline SystemType& getSystem() { return SystemData<SystemType>::getInstance(); }
};


#include "System/PhysicsSystem.h"
#include "System/RenderSystem.h"

typedef SystemStorageBase<
	PhysicsSystem,
	RenderSystem
>
SystemStorage;
