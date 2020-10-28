#include "../JSON.h"

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
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 9999}").get<int>("normalvalue"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 9}").get<int>("normalvalue"));

    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 5.43}").get<float>("normalvalue"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 522.1}").get<float>("normalvalue"));

    ASSERT_NO_THROW(JSON::parseFromString("{\"value\": \"itsAValue\"}").get<std::string>("value"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"value\": \"itsAv   Valu \n\t  e01234\"}").get<std::string>("value"));
}

TEST(JsonTest, FileRead)
{
    ASSERT_THROW(JSON::parseFromFile("nonexistent.json"), JSON::ParseException);
    ASSERT_NO_THROW(JSON::parseFromFile("../units/Fallen.json"));
}

TEST(JsonTest, KeyValuePair)
{
    JSON parsed = JSON::parseFromString("{    \"string\"    \t :  \n  \"a value\"  \t  , \"number\": 65553342      }   ");

    ASSERT_NO_THROW(parsed.get<std::string>("string"));
    ASSERT_EQ(parsed.get<std::string>("string"), "a value");

    ASSERT_NO_THROW(parsed.get<int>("number"));
    ASSERT_EQ(parsed.get<int>("number"), 65553342);
}

TEST(JsonTest, ParseError)
{
    // } instead of ,
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\"} \"bad\": \"end\"}"), JSON::ParseException);
    // extra } before ,
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\"}, \"bad\": \"end\"}"), JSON::ParseException);
    // missing value
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\", \"bad\": }"), JSON::ParseException);
    // missing key
    ASSERT_THROW(JSON::parseFromString("{\"good\": \"start\", \"bad\" }"), JSON::ParseException);
}
