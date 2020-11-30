#include "../Map.h"
#include "../MarkedMap.h"

#include <gtest/gtest.h>

TEST(MapTest, GetFieldTypeByPosition)
{
    Map map("../maps/map1.txt");

    Map::FieldType type1 = map.getFieldType(0, 0);
    Map::FieldType type2 = map.getFieldType(1, 0);

    ASSERT_EQ(type1, Map::FieldType::Wall);
    ASSERT_EQ(type2, Map::FieldType::Free);
}

TEST(MapTest, GetFieldTypeByValue)
{
    Map map("../maps/map1.txt");

    Map::FieldType type1 = map.getFieldType('#');
    Map::FieldType type2 = map.getFieldType(' ');

    ASSERT_EQ(type1, Map::FieldType::Wall);
    ASSERT_EQ(type2, Map::FieldType::Free);
}

TEST(MapTest, GetField)
{
    Map map("../maps/map1.txt");

    ASSERT_THROW(map.getField(-1, 0), Map::WrongIndexException);
    ASSERT_THROW(map.getField(0, -1), Map::WrongIndexException);
    ASSERT_THROW(map.getField(0, map.getHeight()), Map::WrongIndexException);
    ASSERT_THROW(map.getField(map.getWidth(), 0), Map::WrongIndexException);

    ASSERT_NO_THROW(map.getField(0, 0));
    ASSERT_NO_THROW(map.getField(map.getWidth() - 1, 0));
    ASSERT_NO_THROW(map.getField(0, map.getHeight() - 1));
}

TEST(MapTest, IsFieldExist)
{
    Map map("../maps/map1.txt");

    ASSERT_FALSE(map.isFieldExist(-1, 0));
    ASSERT_FALSE(map.isFieldExist(0, -1));
    ASSERT_FALSE(map.isFieldExist(0, map.getHeight()));
    ASSERT_FALSE(map.isFieldExist(map.getWidth(), 0));

    ASSERT_TRUE(map.isFieldExist(0, 0));
    ASSERT_TRUE(map.isFieldExist(map.getWidth() - 1, 0));
    ASSERT_TRUE(map.isFieldExist(0, map.getHeight() - 1));
}

TEST(MapTest, IsFieldFree)
{
    Map map("../maps/map1.txt");

    ASSERT_THROW(map.isFieldFree(-1, 0), Map::WrongIndexException);
    ASSERT_THROW(map.isFieldFree(0, -1), Map::WrongIndexException);
    ASSERT_THROW(map.isFieldFree(0, map.getHeight()), Map::WrongIndexException);
    ASSERT_THROW(map.isFieldFree(map.getWidth(), 0), Map::WrongIndexException);

    ASSERT_NO_THROW(map.isFieldFree(0, 0));
    ASSERT_NO_THROW(map.isFieldFree(map.getWidth() - 1, 0));
    ASSERT_NO_THROW(map.isFieldFree(0, map.getHeight() - 1));

    ASSERT_FALSE(map.isFieldFree(0, 0));

    ASSERT_TRUE(map.isFieldFree(1, 0));
}

TEST(MapTest, MarkedMapGetHero)
{
    MarkedMap map("../maps/map2.txt");

    Location loc = map.getHeroPosition();
    ASSERT_EQ(loc.x, 2);
    ASSERT_EQ(loc.y, 1);

    MarkedMap map2("../maps/map1.txt");
    ASSERT_THROW(map2.getHeroPosition(), MarkedMap::HeroNotFoundException);
}

TEST(MapTest, MarkedMapGetMonsters)
{
    MarkedMap map("../maps/map2.txt");

    auto locs = map.getMonsterPositions('1');
    ASSERT_EQ(locs[0], Location(2, 3));
    ASSERT_EQ(locs[1], Location(3, 4));
    ASSERT_EQ(locs[2], Location(6, 5));

    auto locs2 = map.getMonsterPositions('2');
    ASSERT_EQ(locs2[0], Location(6, 2));
    ASSERT_EQ(locs2[1], Location(7, 2));
    ASSERT_EQ(locs2[2], Location(3, 3));
}