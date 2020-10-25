#include "../JSON.h"
#include "../jsonFileReadError.h"
#include "../jsonParseError.h"

#include <gtest/gtest.h>

TEST(JsonTest, ParseInts)
{
    ASSERT_THROW(JSON::parseFromString("{\"largevalue\": 2147483650}"), std::out_of_range);
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 9999}"));
}

TEST(JsonTest, ParseFloats)
{
    ASSERT_THROW(JSON::parseFromString("{\"largevalue\": 999999999999999999999999999999999999999.99999}"), std::out_of_range);
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 99.99}"));
}

TEST(JsonTest, Casts)
{
    ASSERT_NO_THROW(std::any_cast<int>(JSON::parseFromString("{\"normalvalue\": 9999}")["normalvalue"]));
    ASSERT_NO_THROW(std::any_cast<int>(JSON::parseFromString("{\"normalvalue\": 9}")["normalvalue"]));

    ASSERT_NO_THROW(std::any_cast<float>(JSON::parseFromString("{\"normalvalue\": 5.43}")["normalvalue"]));
    ASSERT_NO_THROW(std::any_cast<float>(JSON::parseFromString("{\"normalvalue\": 522.1}")["normalvalue"]));

    ASSERT_NO_THROW(std::any_cast<std::string>(JSON::parseFromString("{\"value\": \"itsAValue\"}")["value"]));
    ASSERT_NO_THROW(std::any_cast<std::string>(JSON::parseFromString("{\"value\": \"itsAv   Valu \n\t  e01234\"}")["value"]));
}

TEST(JsonTest, FileRead)
{
    ASSERT_THROW(JSON::parseFromFile("nonexistent.json"), JsonFileReadError);
    ASSERT_NO_THROW(JSON::parseFromFile("../units/unit1.json"));
}

TEST(JsonTest, KeyValuePair)
{
    std::map<std::string, std::any> parsed = JSON::parseFromString("{    \"string\"    \t :  \n  \"a value\"  \t  , \"number\": 65553342      }   ");

    ASSERT_NO_THROW(std::any_cast<std::string>(parsed["string"]));
    ASSERT_EQ(std::any_cast<std::string>(parsed["string"]), "a value");

    ASSERT_NO_THROW(std::any_cast<int>(parsed["number"]));
    ASSERT_EQ(std::any_cast<int>(parsed["number"]), 65553342);
}

TEST(JsonTest, ParseError)
{
    // } instead of ,
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\"} \"bad\": \"end\"}"), JsonParseError);
    // extra } before ,
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\"}, \"bad\": \"end\"}"), JsonParseError);
    // missing value
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\", \"bad\": }"), JsonParseError);
    // missing key
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\", \"bad\" }"), JsonParseError);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}