#include "../JSON.h"

#include <gtest/gtest.h>

TEST(JsonTest, ParseInts)
{
    ASSERT_THROW(JSON::parseFromString("{\"largevalue\": 2147483650}"), std::out_of_range);
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 9999}"));
}

TEST(JsonTest, ParseDoubles)
{
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 99.945674139}"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 99.9}"));
}

TEST(JsonTest, Casts)
{
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 9999}").get<int>("normalvalue"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 9}").get<int>("normalvalue"));

    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 5.43}").get<double>("normalvalue"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"normalvalue\": 522.1}").get<double>("normalvalue"));

    ASSERT_NO_THROW(JSON::parseFromString("{\"value\": \"itsAValue\"}").get<std::string>("value"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"value\": \"itsAv   Valu \n\t  e01234\"}").get<std::string>("value"));
}

TEST(JsonTest, FileRead)
{
    ASSERT_THROW(JSON::parseFromFile("nonexistent.json"), JSON::ParseException);
    ASSERT_NO_THROW(JSON::parseFromFile("../units/Fallen.json"));
}

TEST(JsonTest, KeyExists)
{
    JSON parsed = JSON::parseFromString("{\"a\":1,\"a_b_c\": 0.1}");

    ASSERT_EQ(parsed.count("a"), 1);
    ASSERT_EQ(parsed.count("a_b_c"), 1);
    ASSERT_EQ(parsed.count("b"), 0);
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

TEST(JsonTest, ParseArray)
{
    ASSERT_THROW(JSON::parseFromString("{\"array\": [1111,]}"), JSON::ParseException);
    ASSERT_THROW(JSON::parseFromString("{\"array\": [abcd]}"), JSON::ParseException);
    ASSERT_THROW(JSON::parseFromString("{\"array\": [,1111]}"), JSON::ParseException);
    ASSERT_THROW(JSON::parseFromString("{\"array\": 1111]}"), JSON::ParseException);
    ASSERT_THROW(JSON::parseFromString("{\"array\": [1234}"), JSON::ParseException);
    ASSERT_THROW(JSON::parseFromString("{\"array\": [\"key\": 1234]}"), JSON::ParseException);

    ASSERT_NO_THROW(JSON::parseFromString("{\"array\": [1234]}"));
    ASSERT_NO_THROW(JSON::parseFromString("{\"array\": [1234, \"abcd\", 12.34]}"));
    ASSERT_NO_THROW(JSON::parseFromString("{    \"array\":   \n\r[  \t  1234   \t, \t\"abcd\"             , \t  12.34       \r\n     ]\t    }"));
}

TEST(JsonTest, ArrayCasts)
{
    JSON json = JSON::parseFromString("{\"array\": [1234, \"abcd\", 12.34]}");

    ASSERT_NO_THROW(json.get<JSON::list>("array"));

    JSON::list list = json.get<JSON::list>("array");

    int i = 0;
    for (auto value : list)
    {
        switch (i++)
        {
        case 0:
            ASSERT_THROW(std::get<double>(value), std::bad_variant_access);
            ASSERT_NO_THROW(std::get<int>(value));
            break;
        case 1:
            ASSERT_NO_THROW(std::get<std::string>(value));
            break;
        case 2:
            ASSERT_THROW(std::get<int>(value), std::bad_variant_access);
            ASSERT_NO_THROW(std::get<double>(value));
            break;
        }
    }
}