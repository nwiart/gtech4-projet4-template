#include "GameManager.h"

#include <SFML/Graphics.hpp>


int main()
{
	//std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>();
	GameManager& gameManager = GameManager::getInstance();

	gameManager.run();

	return 0;
}
