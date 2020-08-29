#include "HighScores.h"

#include <algorithm>
#include <fstream>
#include <iostream>

HighScores::HighScores(const std::string& _filename, size_t _maxSize) :
 filename(_filename), maxSize(_maxSize)
{
    Load();
}

void HighScores::Load()
{
    highScores.clear();

    std::ifstream in(filename);
    std::string name;
    int score;
    std::string line;
    while (std::getline(in, line))
    {
        size_t pos = line.find(':');

        if (pos == std::string::npos)
            continue;

        name = line.substr(0, pos);
        score = std::atoi(line.substr(pos + 1).c_str());

        highScores.push_back({name, score});
    }

    std::cout << "Read " << highScores.size() << " high scores" << std::endl;
}

void HighScores::Save() const
{
    std::ofstream out(filename);

    for (const auto& score : highScores)
        out << score.name << ':' << score.score << std::endl;

    std::cout << "Wrote " << highScores.size() << " high scores" << std::endl;
}

bool HighScores::IsHighScore(int score) const
{
    return highScores.size() < maxSize || highScores[highScores.size() - 1].score < score;
}

void HighScores::AddHighScore(const std::string& name, int score)
{
    if (!IsHighScore(score))
        return;

    highScores.push_back({name, score});

    // Sort
    std::sort(highScores.rbegin(), highScores.rend());

    // Prune list
    while (highScores.size() > maxSize)
        highScores.erase(highScores.end() - 1);

    Save();
}