#include "PreparedGame.h"
#include "JSON.h"

PreparedGame::PreparedGame(const std::string &file)
{
    JSON properties = JSON::parseFromFile(file);

    const std::vector<std::string> expectedProps{"map", "hero"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (!properties.count(expectedProps[i]))
        {
            throw std::invalid_argument("File does not contain all property for PreparedGame initialization: " + file + " " + expectedProps[i]);
        }
    }

    MarkedMap markedMap(properties.get<std::string>("map"));
    setMap((Map)markedMap);

    Hero hero = Hero::parse(properties.get<std::string>("hero"));
    Location heroLoc = markedMap.getHeroPosition();
    putHero(hero, heroLoc.x, heroLoc.y);

    for (size_t i = 0; i < 9; i++)
    {
        std::string monsterName = "monster-" + std::to_string(i);
        if (properties.count(monsterName))
        {
            std::vector<Location> locations = markedMap.getMonsterPositions('0' + i);
            for (auto loc : locations)
            {
                Monster m = Monster::parse(properties.get<std::string>(monsterName));
                putMonster(m, loc.x, loc.y);
            }
        }
    }
}

void PreparedGame::run()
{
    Game::run();
}
