#include "../Unit.h"
#include "../JSON.h"
#include "../Hero.h"
#include "../Monster.h"

#include <gtest/gtest.h>

TEST(UnitTest, ConstructTest)
{
    Unit u1("LevelTest", 100, 10, 1.0, 1);
    ASSERT_EQ(u1.getLevel(), 1);

    Unit u2("LevelTest", 100, 10, 2.1, 10, 30, 30, 0.7, 1, 1);
    ASSERT_EQ(u1.getLevel(), 1);
}

TEST(UnitTest, DuelUnitUnit)
{
    Unit u1("DuelTest1", 200, 10, 0.7, 2);
    Unit u2("DuelTest2", 100, 60, 1.0, 5);

    ASSERT_THROW(u1.fightTilDeath(u1), std::invalid_argument);
    ASSERT_NO_THROW(u1.fightTilDeath(u2));

    ASSERT_EQ(u2.getMaxHealthPoints(), 100);
    ASSERT_EQ(u2.getHealthPoints(), 75);
    ASSERT_EQ(u2.getXP(), 200);
    ASSERT_EQ(u2.getLevel(), 1);
    ASSERT_EQ(u2.getDefense(), 5);
    ASSERT_EQ(u2.getAttackCoolDown(), 1.0);
    ASSERT_EQ(u2.isAlive(), true);

    ASSERT_EQ(u1.getMaxHealthPoints(), 200);
    ASSERT_EQ(u1.getHealthPoints(), 0);
    ASSERT_EQ(u1.getXP(), 25);
    ASSERT_EQ(u1.getLevel(), 1);
    ASSERT_EQ(u1.getDefense(), 2);
    ASSERT_EQ(u1.getAttackCoolDown(), 0.7);
    ASSERT_EQ(u1.isAlive(), false);

    Unit u3("DuelTest3", 200, 10, 0.7, 10, 30, 10, 0.5, 2, 1);
    Unit u4("DuelTest4", 100, 60, 1.0, 0);

    ASSERT_NO_THROW(u3.fightTilDeath(u4));

    ASSERT_EQ(u3.getMaxHealthPoints(), 500);
    ASSERT_EQ(u3.getHealthPoints(), 500);
    ASSERT_EQ(u3.getXP(), 100);
    ASSERT_EQ(u3.getLevel(), 11);
    ASSERT_EQ(u3.getDefense(), 12);
    ASSERT_EQ(u3.isAlive(), true);

    ASSERT_EQ(u4.getMaxHealthPoints(), 100);
    ASSERT_EQ(u4.getHealthPoints(), 0);
    ASSERT_EQ(u4.getXP(), 57);
    ASSERT_EQ(u4.getLevel(), 1);
    ASSERT_EQ(u4.getDefense(), 0);
    ASSERT_EQ(u4.isAlive(), false);
}

TEST(UnitTest, DuelHeroMonster)
{
    Hero h("H", 100, 10, 2.1, 10, 30, 5, 0.4, 1, 2);
    Monster m("M", 200, 13, 0.9, 1);

    ASSERT_NO_THROW(h.fightTilDeath(m));

    ASSERT_EQ(h.isAlive(), true);
    ASSERT_EQ(h.getLevel(), 21);
    ASSERT_EQ(h.getDamage(), 110);
    ASSERT_EQ(h.getDefense(), 41);

    ASSERT_EQ(m.isAlive(), false);
    ASSERT_EQ(m.getDamage(), 13);
}

TEST(UnitTest, isAlive)
{
    Unit u1("Alive", 1, 0, 0, 0);
    ASSERT_EQ(u1.isAlive(), true);

    Unit u2("Dead", 0, 0, 0, 0);
    ASSERT_EQ(u2.isAlive(), false);
}

TEST(UnitTest, PrintFormat)
{
    Unit u1("U1", 201, 11, 0.1, 1);
    std::string expect1("U1: MAX HP: 201, HP: 201, DMG: 11, XP: 0, COOLDOWN: 0.1, DEFENSE: 1, LEVEL: 1");

    std::stringstream res1;
    u1.print(res1);
    ASSERT_EQ(res1.str(), expect1);
}
