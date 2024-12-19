#pragma once

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();

    void updateScore();
    void resetScore();

    inline int getCurrentScore() const { return currentScore; }

    static ScoreManager& getInstance()
    {
        static ScoreManager inst;
        return inst;
    }

private:
    int currentScore;

};