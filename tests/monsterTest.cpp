#include "../Monster.h"
#include "../JSON.h"
#include "../Damage.h"

#include <gtest/gtest.h>

TEST(MonsterTest, Parse)
{
    ASSERT_THROW(Monster::parse("nonexistent.json"), JSON::ParseException);

    ASSERT_NO_THROW(Monster::parse("../units/Fallen.json"));

    // A hero requires different keys to be set
    ASSERT_THROW(Monster::parse("../units/Dark_Wanderer.json"), std::invalid_argument);
}

TEST(MonsterTest, PrintFormat)
{
    Damage dmg;
    dmg.physical = 11;
    Monster m1("M1", 201, dmg, 0.1, 1, "");
    std::string expect1("M1 (HP:201, PHYSICAL DAMAGE:11, MAGICAL DAMAGE:0, CD:0.1, DEFENSE:1)");

    std::stringstream res1;
    m1.print(res1);
    ASSERT_EQ(res1.str(), expect1);
}
