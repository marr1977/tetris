#pragma once

#include <vector>
#include <string>

class HighScores
{
    public:

    HighScores(const std::string& filename, size_t maxSize);

    struct Score
    {
        std::string name;
        int score;

        bool operator < (const Score& other) const
        {   
            return score < other.score;
        }
    };

    const std::vector<Score>& GetHighScores() const { return highScores; }
    bool IsHighScore(int score) const;
    void AddHighScore(const std::string& name, int score);

    private:
    
    void Load();
    void Save() const;

    private:

    std::vector<Score> highScores;
    std::string filename;
    size_t maxSize;
};
