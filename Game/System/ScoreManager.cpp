#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
    currentScore = 0;
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::updateScore()
{
    currentScore++;
}

void ScoreManager::resetScore()
{
    currentScore = 0;
}
