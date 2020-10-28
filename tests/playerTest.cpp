#include "../player.h"
#include "../JsonFileReadError.h"

#include <gtest/gtest.h>

TEST(PlayerTest, FileParse)
{
    ASSERT_THROW(Player::parseUnit("unitthatdoesnotexists.json"), JsonFileReadError);

    ASSERT_NO_THROW(Player::parseUnit("../units/unit1.json"));
    ASSERT_NO_THROW(Player::parseUnit("../units/unit2.json"));
}

TEST(PlayerTest, LevelTest)
{
    Player p1("LevelTest", 100, 10, 1.0, 0);
    ASSERT_EQ(p1.GetLevel(), 1);
    Player p2("LevelTest", 100, 10, 1.0, 780);
    ASSERT_EQ(p2.GetLevel(), 8);
}

TEST(PlayerTest, Duel)
{
    Player p1("DuelTest1", 200, 10, 0.7, 0);
    Player p2("DuelTest2", 100, 60, 1.0, 0);
    Player *winner = nullptr;

    ASSERT_THROW(p1.DuelWith(&p1), std::invalid_argument);
    ASSERT_NO_THROW(winner = p1.DuelWith(&p2));

    ASSERT_EQ(winner->GetName(), "DuelTest2");
    ASSERT_EQ(winner->GetMaxHP(), 121);
    ASSERT_EQ(winner->GetHP(), 121);
    ASSERT_EQ(winner->GetXP(), 200);
    ASSERT_EQ(winner->GetLevel(), 3);

    ASSERT_EQ(p1.GetMaxHP(), 200);
    ASSERT_EQ(p1.GetHP(), 0);
    ASSERT_EQ(p1.GetXP(), 50);
    ASSERT_EQ(p1.GetLevel(), 1);
}

TEST(PlayerTest, PrintFormat)
{
    Player p1("P1", 201, 11, 0.1, 0122);
    std::string expect1("P1: MAX HP: 201, HP: 201, DMG: 11, XP: 82, COOLDOWN: 0.1, LEVEL: 1");

    std::stringstream res1;
    p1.Print(res1);
    ASSERT_EQ(res1.str(), expect1);

    Player p2("P2", 44, 122, 12.2, 0);
    std::string expect2("P2: MAX HP: 44, HP: 44, DMG: 122, XP: 0, COOLDOWN: 12.2, LEVEL: 1");

    std::stringstream res2;
    p2.Print(res2);
    ASSERT_EQ(res2.str(), expect2);

    // Levelups only occur after a hit
    Player p3("P3", 58, 5, 10, 1000);
    std::string expect3("P3: MAX HP: 58, HP: 58, DMG: 5, XP: 1000, COOLDOWN: 10, LEVEL: 11");

    std::stringstream res3;
    p3.Print(res3);
    ASSERT_EQ(res3.str(), expect3);
}
