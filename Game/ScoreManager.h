#pragma once

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();

    void updateScore(int score);
    void resetScore();

    static ScoreManager& getInstance()
    {
        static ScoreManager inst;
        return inst;
    }

private:
    int currentScore;

};