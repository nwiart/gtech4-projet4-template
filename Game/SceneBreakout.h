#pragma once

#include "IncludeSFML.h"

#include "Scene/Scene.h"




class SceneBreakout : public Scene
{
	enum class GameState {
		Menu,
		Playing,
		GameOver
	};

	GameState gameState = GameState::Menu;


public:

	SceneBreakout();

	virtual void load() override;

	virtual void spawn() override;

	virtual void update() override;

private:

	void startGame();

	static bool onBrickCollide(GameObject& objA, PhysicsComponent& collA, GameObject& objB, PhysicsComponent& collB);


private:

	GameObject* m_paddle;
	GameObject* m_score;
	GameObject* m_menuText;
	GameObject* m_gameOverText;

	sf::Texture brickTex;
	sf::Font font;
};
