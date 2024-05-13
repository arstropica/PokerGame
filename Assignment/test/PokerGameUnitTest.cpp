/**
 * @file test/PokerGameUnitTest.cpp
 * @brief Unit tests for the PokerHand class.
 */
#include "./PokerGameUnitTest.h"
#include "../../catch_amalgamated.hpp"
#include "../src/game/resources/Hand.h"
#include "../src/game/resources/PokerHand.h"
#include "../utils/Logger.h"
#include <iostream>

using HandPtr = std::shared_ptr<Hand>;
using Test = PokerGameUnitTest;
using Category = PokerHand::Category;
using Outcome = Hand::Comparison;
using Sample = Test::Sample;
using InputArray = std::vector<std::vector<std::array<std::string, 3>>>;
using namespace std;

std::vector<std::vector<std::array<std::string, 3>>> Test::input = {
    {
        // High card
        {{"KS 6C 5H 3D 2C", "QS JD 6C 5H 3C", "INEQUALITY"}},
        {{"QS JD 6C 5H 3C", "QS TD 8C 7D 4S", "INEQUALITY"}},
        {{"QS TD 8C 7D 4S", "QH TH 7C 6H 4S", "INEQUALITY"}},
        {{"QH TH 7C 6H 4S", "QC TC 7D 5C 4D", "INEQUALITY"}},
        {{"QC TC 7D 5C 4D", "QH TD 7S 5S 2H", "INEQUALITY"}},
        {{"TC 8S 7S 6H 4D", "TD 8D 7S 6C 4C,", "EQUALITY"}},
    },
    {
        // One pair
        {{"9C 9D QS JH 5H", "6D 6H KS 7H 4C", "INEQUALITY"}},
        {{"6D 6H KS 7H 4C", "6D 6H QH JS 2C", "INEQUALITY"}},
        {{"6D 6H KS 7H 4C", "6D 6H QH JS 2C", "INEQUALITY"}},
        {{"6D 6H QH JS 2C", "6D 6H QS 8C 7D", "INEQUALITY"}},
        {{"6D 6H QS 8C 7D", "6D 6H QD 8H 3S", "INEQUALITY"}},
        {{"8S 8D TH 6C 5S", "8H 8C TC 6S 5C,", "EQUALITY"}},
    },
    {
        // Two pair
        {{"TD TS 2S 2C KC", "5C 5S 4D 4H TH", "INEQUALITY"}},
        {{"5C 5S 4D 4H TH", "5C 5S 3C 3D QS", "INEQUALITY"}},
        {{"5C 5S 3C 3D QS", "5C 5S 3C 3D JS", "INEQUALITY"}},
        {{"KD KS 7D 7H 8H", "KC KS 7C 7H 8C,", "EQUALITY"}},
    },
    {
        // Three of a kind
        {{"6H 6D 6S QC 4S", "3D 3S 3C KS 2S", "INEQUALITY"}},
        {{"3D 3S 3C KS 2S", "3D 3S 3C JC 7H", "INEQUALITY"}},
        {{"3D 3S 3C JC 7H", "3D 3S 3C JS 5D", "INEQUALITY"}},
        {{"9S 9H 9D TD 8H", "9C 9S 9H TD 8D,", "EQUALITY"}},
    },
    {
        // Straight
        {{"JH TH 9C 8S 7H", "TS 9S 8C 7H 6S", "INEQUALITY"}},
        {{"TS 9S 8C 7H 6S", "6C 5S 4H 3S 2D", "INEQUALITY"}},
        {{"9C 8C 7C 6D 5D", "9S 8S 7S 6H 5H,", "EQUALITY"}},
    },
    {
        // Flush
        {{"KD JD 9D 6D 4D", "QC JC 7C 6C 5C", "INEQUALITY"}},
        {{"QC JC 7C 6C 5C", "JH TH 9H 4H 2H", "INEQUALITY"}},
        {{"JH TH 9H 4H 2H", "JS TS 8S 6S 3S", "INEQUALITY"}},
        {{"JS TS 8S 6S 3S", "JH TH 8H 4H 3H", "INEQUALITY"}},
        {{"JH TH 8H 4H 3H", "JC TC 8C 4C 2C", "INEQUALITY"}},
        {{"TD 8D 7D 6D 5D", "TS 8S 7S 6S 5S,", "EQUALITY"}},
    },
    {
        // Full house
        {{"8S 8D 8H 7D 7C", "4D 4S 4C 9D 9C", "INEQUALITY"}},
        {{"4D 4S 4C 9D 9C", "4D 4S 4C 5C 5D", "INEQUALITY"}},
        {{"KC KS KD JC JS", "KC KH KD JC JH,", "EQUALITY"}},
    },
    {
        // Four of a kind
        {{"KS KH KC KD 3H", "7H 7D 7S 7C QH", "INEQUALITY"}},
        {{"7H 7D 7S 7C QH", "7H 7D 7S 7C TS", "INEQUALITY"}},
        {{"4C 4S 4D 4H 9C", "4C 4S 4D 4H 9D", "EQUALITY"}},
    },
    {
        // Royal Flush
        {{"AS KS QS JS TS", "8H 7H 6H 5H 4H", "INEQUALITY"}},
        // Straight Flush
        {{"TC 9C 8C 7C 6C", "8H 7H 6H 5H 4H", "INEQUALITY"}},
        {{"8H 7H 6H 5H 4H", "6S 5S 4S 3S 2S", "INEQUALITY"}},
        {{"7D 6D 5D 4D 3D", "7S 6S 5S 4S 3S,", "EQUALITY"}},
    }};

// Alias Test::input
InputArray &units = Test::input;

/**
 * @brief Compare Hands.
 *
 * @param hand1
 * @param hand2
 * @return PokerHand::Outcome
 */
Outcome Test::evaluate(const HandPtr &hand1, const HandPtr &hand2)
{
   return hand1->compare(hand2);
}

/**
 * @brief Test High Card Comparisons.
 */
TEST_CASE("Test High Card Comparisons")
{
   for (int i = 0; i < units[Category::HIGH_CARD].size(); i++) {
      auto unit = units[Category::HIGH_CARD][i];
      SECTION("High Card Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test One Pair Comparisons.
 */
TEST_CASE("Test One Pair Comparisons")
{
   for (int i = 0; i < units[Category::ONE_PAIR].size(); i++) {
      auto unit = units[Category::ONE_PAIR][i];
      SECTION("One Pair Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test Two Pair Comparisons.
 */
TEST_CASE("Test Two Pair Comparisons")
{
   for (int i = 0; i < units[Category::TWO_PAIR].size(); i++) {
      auto unit = units[Category::TWO_PAIR][i];
      SECTION("Two Pair Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         if (result != expected) {
            Logger::info("Hand 1: " + hand1->getScore(true));
            Logger::info("Hand 2: " + hand2->getScore(true));
         }
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test Three of a Kind Comparisons.
 */
TEST_CASE("Test Three of a Kind Comparisons")
{
   for (int i = 0; i < units[Category::THREE_OF_A_KIND].size(); i++) {
      auto unit = units[Category::THREE_OF_A_KIND][i];
      SECTION("Three of a Kind Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test Straight Comparisons.
 */
TEST_CASE("Test Straight Comparisons")
{
   for (int i = 0; i < units[Category::STRAIGHT].size(); i++) {
      auto unit = units[Category::STRAIGHT][i];
      SECTION("Straight Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test Flush Comparisons.
 */
TEST_CASE("Test Flush Comparisons")
{
   for (int i = 0; i < units[Category::FLUSH].size(); i++) {
      auto unit = units[Category::FLUSH][i];
      SECTION("Flush Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test Full House Comparisons.
 */
TEST_CASE("Test Full House Comparisons")
{
   for (int i = 0; i < units[Category::FULL_HOUSE].size(); i++) {
      auto unit = units[Category::FULL_HOUSE][i];
      SECTION("Full House Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test Four of a Kind Comparisons.
 */
TEST_CASE("Test Four of a Kind Comparisons")
{
   for (int i = 0; i < units[Category::FOUR_OF_A_KIND].size(); i++) {
      auto unit = units[Category::FOUR_OF_A_KIND][i];
      SECTION("Four of a Kind Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}

/**
 * @brief Test Straight Flush Comparisons.
 */
TEST_CASE("Test Straight Flush Comparisons")
{
   for (int i = 0; i < units[Category::STRAIGHT_FLUSH].size(); i++) {
      auto unit = units[Category::STRAIGHT_FLUSH][i];
      SECTION("Straight Flush Comparison " + to_string(i))
      {
         HandPtr hand1 = make_shared<PokerHand>(unit[Sample::EXAMPLE_1]);
         HandPtr hand2 = make_shared<PokerHand>(unit[Sample::EXAMPLE_2]);
         Outcome expected = unit[Sample::COMPARISON] == "INEQUALITY"
                                ? Outcome::WINNER_SELF
                                : Outcome::EQUAL_HAND;
         auto result = Test::evaluate(hand1, hand2);
         REQUIRE(result == expected);
      }
   }
}