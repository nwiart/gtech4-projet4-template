#pragma once

class GameObject;


template<typename ComponentType>
class System
{
public:

	typedef ComponentType _ComponentType;

public:

	ComponentType* add(GameObject& obj) { return 0; }

	void remove(GameObject& obj) { }

	void update() { }

	bool isRegistered(GameObject& obj) const { return false; }
};
