#include "../json.h"
#include "../jsonFileReadError.h"

#include <gtest/gtest.h>

TEST(JsonTest, ParseInts) {
    ASSERT_THROW(Json::ParseJson("{\"largevalue\": 2147483650}"), std::out_of_range);
    ASSERT_NO_THROW(Json::ParseJson("{\"normalvalue\": 9999}"));
}

TEST(JsonTest, ParseFloats) {
    ASSERT_THROW(Json::ParseJson("{\"largevalue\": 999999999999999999999999999999999999999.99999}"), std::out_of_range);
    ASSERT_NO_THROW(Json::ParseJson("{\"normalvalue\": 99.99}"));
}

TEST(JsonTest, Casts) {
    ASSERT_NO_THROW(std::any_cast<int>(Json::ParseJson("{\"normalvalue\": 9999}")["normalvalue"]));
    ASSERT_NO_THROW(std::any_cast<int>(Json::ParseJson("{\"normalvalue\": 9}")["normalvalue"]));

    ASSERT_NO_THROW(std::any_cast<float>(Json::ParseJson("{\"normalvalue\": 5.43}")["normalvalue"]));
    ASSERT_NO_THROW(std::any_cast<float>(Json::ParseJson("{\"normalvalue\": 522.1}")["normalvalue"]));

    ASSERT_NO_THROW(std::any_cast<std::string>(Json::ParseJson("{\"value\": \"itsAValue\"}")["value"]));
    ASSERT_NO_THROW(std::any_cast<std::string>(Json::ParseJson("{\"value\": \"itsAv   Valu \n\t  e01234\"}")["value"]));
}

TEST(JsonTest, FileRead) {
    ASSERT_THROW(Json::ParseJson("nonexistent.json"), JsonFileReadError);
    ASSERT_NO_THROW(Json::ParseJson("../units/unit1.json"));
}

TEST(JsonTest, KeyValuePair) {
    std::map<std::string, std::any> parsed = Json::ParseJson("{    \"string\"    \t :  \n  \"a value\"  \t  , \"number\": 65553342      }   ");

    ASSERT_NO_THROW(std::any_cast<std::string>(parsed["string"]));
    ASSERT_EQ(std::any_cast<std::string>(parsed["string"]), "a value");

    ASSERT_NO_THROW(std::any_cast<int>(parsed["number"]));
    ASSERT_EQ(std::any_cast<int>(parsed["number"]), 65553342);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}