#include "../Hero.h"
#include "../Monster.h"
#include "../Map.h"
#include "../Game.h"

#include <gtest/gtest.h>

TEST(GameTest, SetMap)
{
    // Map and Units
    Map map("../maps/map1.txt");
    Damage dmg;
    dmg.physical = 11;
    dmg.magical = 2;
    Hero h1("H1", 201, dmg, 0.1, 10, 20, 10, 2, 0.2, 1, 1);
    Monster m1("M1", 201, dmg, 0.1, 1);

    // Empty game
    Game g1;

    // Game with map
    Game g2;
    g2.setMap(map);

    // Game with map and Hero on it
    Game g3;
    g3.setMap(map);
    g3.putHero(h1, 1, 0);

    // Game with map and Monster on it
    Game g4;
    g4.setMap(map);
    g4.putMonster(m1, 2, 0);

    // Game with map, Hero and Monster on it
    Game g5;
    g5.setMap(map);
    g5.putHero(h1, 1, 0);
    g5.putMonster(m1, 2, 0);

    // Started game with map, Hero and Monster on it
    Game g6;
    g6.setMap(map);
    g6.putHero(h1, 1, 0);
    g6.putMonster(m1, 2, 0);
    g6.setGameState(Game::GameState::started);

    ASSERT_THROW(g3.setMap(map), Game::AlreadyHasUnitsException);
    ASSERT_THROW(g4.setMap(map), Game::AlreadyHasUnitsException);
    ASSERT_THROW(g5.setMap(map), Game::AlreadyHasUnitsException);
    ASSERT_THROW(g6.setMap(map), Game::GameAlreadyStartedException);

    ASSERT_NO_THROW(g1.setMap(map));
    ASSERT_NO_THROW(g2.setMap(map));
}

TEST(GameTest, PutHero)
{
    // Map and Hero
    std::string mapString = "../maps/map1.txt";
    Map map(mapString);
    Damage dmg;
    dmg.physical = 11;
    dmg.magical = 2;
    Hero h1("H1", 201, dmg, 0.1, 10, 20, 10, 2, 0.2, 1, 1);

    // Empty game
    Game g1;

    // Game with map
    Game g2(mapString);

    // Game with map and Hero on it
    Game g3(mapString);
    g3.putHero(h1, 1, 0);

    // Started Game with map and Hero on it
    Game g4(mapString);
    g4.putHero(h1, 1, 0);
    g4.setGameState(Game::GameState::started);

    ASSERT_THROW(g1.putHero(h1, 0, 0), Map::WrongIndexException);
    ASSERT_THROW(g2.putHero(h1, -1, 0), Map::WrongIndexException);
    ASSERT_THROW(g2.putHero(h1, 0, -1), Map::WrongIndexException);
    ASSERT_THROW(g2.putHero(h1, 0, map.getHeight()), Map::WrongIndexException);
    ASSERT_THROW(g2.putHero(h1, map.getWidth(), 0), Map::WrongIndexException);
    ASSERT_THROW(g2.putHero(h1, 0, 0), Game::OccupiedException);
    ASSERT_THROW(g3.putHero(h1, 1, 0), Game::AlreadyHasHeroException);
    ASSERT_THROW(g4.putHero(h1, 1, 0), Game::GameAlreadyStartedException);

    ASSERT_NO_THROW(g2.putHero(h1, 1, 0));
}

TEST(GameTest, PutMonster)
{
    // Map and Monster
    std::string mapString = "../maps/map1.txt";
    Map map(mapString);
    Damage dmg;
    dmg.physical = 11;
    dmg.magical = 2;
    Monster m1("M1", 201, dmg, 0.1, 1);

    // Game with map
    Game g1(mapString);

    ASSERT_THROW(g1.putMonster(m1, 0, 0), Game::OccupiedException);
    ASSERT_THROW(g1.putMonster(m1, -1, 0), Map::WrongIndexException);
    ASSERT_THROW(g1.putMonster(m1, 0, -1), Map::WrongIndexException);
    ASSERT_THROW(g1.putMonster(m1, 0, map.getHeight()), Map::WrongIndexException);
    ASSERT_THROW(g1.putMonster(m1, map.getWidth(), 0), Map::WrongIndexException);

    ASSERT_NO_THROW(g1.putMonster(m1, 2, 0));
}

TEST(GameTest, CheckFieldAvailability)
{
    // Map and Monster
    std::string mapString = "../maps/map1.txt";
    Map map(mapString);
    Damage dmg;
    dmg.physical = 11;
    dmg.magical = 2;
    Monster m1("M1", 201, dmg, 0.1, 1);

    // Game with map
    Game g1(mapString);

    ASSERT_THROW(g1.checkFieldAvailability(0, 0), Game::OccupiedException);
    ASSERT_THROW(g1.checkFieldAvailability(-1, 0), Map::WrongIndexException);
    ASSERT_THROW(g1.checkFieldAvailability(0, -1), Map::WrongIndexException);
    ASSERT_THROW(g1.checkFieldAvailability(0, map.getHeight()), Map::WrongIndexException);
    ASSERT_THROW(g1.checkFieldAvailability(map.getWidth(), 0), Map::WrongIndexException);

    ASSERT_NO_THROW(g1.checkFieldAvailability(1, 0));
    ASSERT_NO_THROW(g1.checkFieldAvailability(2, 0));
}

TEST(UnitTest, PrintGameBoard)
{
    Game g1("../maps/map1.txt");
    std::string expect1("\n╔════════════════════════════╗\n║██░░░░░░░░░░░░░░████░░░░████║\n║██░░░░████░░░░░░░░██████░░░░║\n║████░░░░██░░░░░░██░░░░██░░░░║\n║██████░░░░░░░░░░░░░░██░░░░░░║\n║████░░░░░░░░░░░░░░░░░░██░░░░║\n╚════════════════════════════╝\n");

    std::stringstream res1;
    g1.print(res1);

    ASSERT_EQ(res1.str(), expect1);
}
