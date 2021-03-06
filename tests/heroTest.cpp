#include "../Hero.h"
#include "../JSON.h"
#include "../Damage.h"

#include <gtest/gtest.h>

TEST(HeroTest, Parse)
{
    ASSERT_THROW(Hero::parse("nonexistent.json"), JSON::ParseException);

    // A monster does not contain all required keys
    ASSERT_THROW(Hero::parse("../units/Fallen.json"), std::invalid_argument);

    ASSERT_NO_THROW(Hero::parse("../units/Dark_Wanderer.json"));
}

TEST(HeroTest, PrintFormat)
{
    Damage dmg;
    dmg.physical = 11;
    Hero h1("H1", 201, dmg, 0.1, 10, 20, 10, 3, 0.2, 1, 1, 3, 1, "");
    std::string expect1("H1 - LVL1 (HP:201/201, PHYSICAL DAMAGE:11, MAGICAL DAMAGE:0, CD:0.1, XP:0, DEFENSE:1)");

    std::stringstream res1;
    h1.print(res1);
    ASSERT_EQ(res1.str(), expect1);
}
