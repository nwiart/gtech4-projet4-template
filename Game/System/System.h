#pragma once

class GameObject;


template<typename ComponentType>
class System
{
public:

	ComponentType* add(GameObject& obj) { return 0; }

	void remove(GameObject& obj) { }

	void update() { }
};
