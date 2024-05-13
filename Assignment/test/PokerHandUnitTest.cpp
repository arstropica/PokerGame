/**
 * @file test/PokerHandUnitTest.cpp
 * @brief Unit tests for the PokerHand class.
 */
#include "./PokerHandUnitTest.h"
#include "../../catch_amalgamated.hpp"
#include "../src/game/resources/Hand.h"
#include "../src/game/resources/PokerHand.h"
#include "../utils/Logger.h"
#include <iostream>

using HandPtr = std::shared_ptr<Hand>;
using Test = PokerHandUnitTest;
using Category = PokerHand::Category;
using Outcome = Hand::Comparison;
using Sample = Test::Sample;
using InputArray = std::string[10][6];
using namespace std;

std::string Test::input[10][6] = {
    // High Card
    "2D 4H 7S 9C JH", // EXAMPLE_1
    "3S 5D 8H TC KH", // EXAMPLE_2
    "2D 3H 4S 5C 7H", // LOWEST
    "9D JH QS KC AH", // HIGHEST
    "2D 4C 7D 9S JS", // EQUIVALENT
    "2D 4H 7S 9C 9D", // COUNTEREXAMPLE

    // One Pair
    "2D 2H 7S 9C JH", // EXAMPLE_1
    "AS AD 8H TC KH", // EXAMPLE_2
    "2D 2H 3S 4C 5H", // LOWEST
    "AH AS JC QD KS", // HIGHEST
    "2D 2C 7H 9S JS", // EQUIVALENT
    "2D 7H 7S 9C 9H", // COUNTEREXAMPLE

    // Two Pair
    "2D 2H 7S 7C JH", // EXAMPLE_1
    "AS AD KH KC 9H", // EXAMPLE_2
    "2D 2H 3S 3C 4H", // LOWEST
    "AH AS KH KD QS", // HIGHEST
    "2D 2C 7H 7S JD", // EQUIVALENT
    "2D 2H 7S 7C 7H", // COUNTEREXAMPLE

    // Three of a Kind
    "2D 2H 2S 7C JH", // EXAMPLE_1
    "AS AD AH KC 9H", // EXAMPLE_2
    "2D 2H 2S 3C 4H", // LOWEST
    "AH AS AC KD QS", // HIGHEST
    "2D 2C 2H 7S JD", // EQUIVALENT
    "7S 7C 7H 4D 4H", // COUNTEREXAMPLE

    // Straight
    "AS 2D 3H 4C 5H", // EXAMPLE_1
    "TD JH KS QC AH", // EXAMPLE_2
    "2D 3H 4S 5C 6H", // LOWEST
    "TD JH QS KC AH", // HIGHEST
    "AD 2H 3C 4S 5H", // EQUIVALENT
    "2D 3H 4S 5C 7H", // COUNTEREXAMPLE

    // Flush
    "2D 4D 7D 9D JD", // EXAMPLE_1
    "3S 5S 8S TS KS", // EXAMPLE_2
    "2D 3D 4D 5D 7D", // LOWEST
    "9D JD QD KD AD", // HIGHEST
    "2H 4H 7H 9H JH", // EQUIVALENT
    "2D 4D 7D 9D JH", // COUNTEREXAMPLE

    // Full House
    "2D 2H 2S 7C 7H", // EXAMPLE_1
    "AS AD AH KC KH", // EXAMPLE_2
    "2D 2H 2S 3C 3H", // LOWEST
    "AH AS AC KD KS", // HIGHEST
    "2D 2H 2S 7D 7H", // EQUIVALENT
    "2D 2H 2S 7C 2C", // COUNTEREXAMPLE

    // Four of a Kind
    "2D 2H 2S 2C 7H", // EXAMPLE_1
    "AS AD AH AC KH", // EXAMPLE_2
    "2D 2H 2S 2C 3H", // LOWEST
    "AH AS AC AD KS", // HIGHEST
    "2D 2H 2S 2C 7D", // EQUIVALENT
    "2D 2H 2S 3C 3H", // COUNTEREXAMPLE

    // Straight Flush
    "AS 2S 3S 4S 5S", // EXAMPLE_1
    "2D 3D 4D 5D 6D", // EXAMPLE_2
    "2D 3D 4D 5D 6D", // LOWEST
    "TD JD QD KD AD", // HIGHEST
    "2H 3H 4H 5H 6H", // EQUIVALENT
    "2D 3D 4D 5D 6H", // COUNTEREXAMPLE

    // Invalid Hands
    "3D 9H 7S 5C TD JH", // TOO MANY CARDS
    "3D 9H 7S 5C",       // TOO FEW CARDS
    "2D 2D AS 7C KD",    // DUPLICATE CARDS
    "3F TS AC QD 4H",    // INCORRECT SUIT
    "1S 2D 3D 4D 5D",    // INCORRECT RANK
};

// Alias Test::input
InputArray &input = Test::input;

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
 * @brief Test section for verifying identification of different hand types.
 *
 */
TEST_CASE("Test Hand Identification")
{
   /**
    * @brief Test High Card Hand identification.
    */
   SECTION("High Card")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand = make_shared<PokerHand>(input[Category::HIGH_CARD][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::HIGH_CARD);
      }
   }

   /**
    * @brief Test One Pair Hand identification.
    */
   SECTION("One Pair")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand = make_shared<PokerHand>(input[Category::ONE_PAIR][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::ONE_PAIR);
      }
   }

   /**
    * @brief Test Two Pair Hand identification.
    */
   SECTION("Two Pair")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand = make_shared<PokerHand>(input[Category::TWO_PAIR][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::TWO_PAIR);
      }
   }

   /**
    * @brief Test Three of a Kind Hand identification.
    */
   SECTION("Three of a Kind")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand =
             make_shared<PokerHand>(input[Category::THREE_OF_A_KIND][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::THREE_OF_A_KIND);
      }
   }

   /**
    * @brief Test Straight Hand identification.
    */
   SECTION("Straight")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand = make_shared<PokerHand>(input[Category::STRAIGHT][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::STRAIGHT);
      }
   }

   /**
    * @brief Test Flush Hand identification.
    */
   SECTION("Flush")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand = make_shared<PokerHand>(input[Category::FLUSH][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::FLUSH);
      }
   }

   /**
    * @brief Test Full House Hand identification.
    */
   SECTION("Full House")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand = make_shared<PokerHand>(input[Category::FULL_HOUSE][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::FULL_HOUSE);
      }
   }

   /**
    * @brief Test Four of a Kind Hand identification.
    */
   SECTION("Four of a Kind")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand =
             make_shared<PokerHand>(input[Category::FOUR_OF_A_KIND][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::FOUR_OF_A_KIND);
      }
   }

   /**
    * @brief Test Straight Flush Hand identification.
    */
   SECTION("Straight Flush")
   {
      for (int i = 0; i < 5; ++i) {
         HandPtr hand =
             make_shared<PokerHand>(input[Category::STRAIGHT_FLUSH][i]);
         REQUIRE(hand->isValid() == true);
         REQUIRE(hand->getCategory() == Category::STRAIGHT_FLUSH);
      }
   }
}

/**
 * @brief Test section for verifying correct identification of counterexamples.
 *
 */
TEST_CASE("Test Hand Counterexample Identification")
{
   /**
    * @brief Test High Card Counterexample Identification.
    */
   SECTION("High Card")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::HIGH_CARD][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::HIGH_CARD);
   }

   /**
    * @brief Test One Pair Counterexample Identification.
    */
   SECTION("One Pair")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::ONE_PAIR][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::ONE_PAIR);
   }

   /**
    * @brief Test Two Pair Counterexample Identification.
    */
   SECTION("Two Pair")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::TWO_PAIR][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::TWO_PAIR);
   }

   /**
    * @brief Test Three of a Kind Counterexample Identification.
    */
   SECTION("Three of a Kind")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::THREE_OF_A_KIND][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::THREE_OF_A_KIND);
   }

   /**
    * @brief Test Straight Counterexample Identification.
    */
   SECTION("Straight")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::STRAIGHT][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::STRAIGHT);
   }

   /**
    * @brief Test Flush Counterexample Identification.
    */
   SECTION("Flush")
   {
      HandPtr hand =
          make_shared<PokerHand>(input[Category::FLUSH][Sample::COUNTEREXAMPLE]
          );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::FLUSH);
   }

   /**
    * @brief Test Full House Counterexample Identification.
    */
   SECTION("Full House")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::FULL_HOUSE][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::FULL_HOUSE);
   }

   /**
    * @brief Test Four of a Kind Counterexample Identification.
    */
   SECTION("Four of a Kind")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::FOUR_OF_A_KIND][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::FOUR_OF_A_KIND);
   }

   /**
    * @brief Test Straight Flush Counterexample Identification.
    */
   SECTION("Straight Flush")
   {
      HandPtr hand = make_shared<PokerHand>(
          input[Category::STRAIGHT_FLUSH][Sample::COUNTEREXAMPLE]
      );
      REQUIRE(hand->isValid() == true);
      REQUIRE(hand->getCategory() != Category::STRAIGHT_FLUSH);
   }
}

/**
 * @brief Test section to verify equivalently ranked hands of different suits.
 *
 */
TEST_CASE("Test Equivalently Ranked Hands")
{
   /**
    * @brief Test Rank-Equivalent High Card Hands.
    */
   SECTION("High Card")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::HIGH_CARD][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::HIGH_CARD][Sample::EQUIVALENT]
          );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent One Pair Hands.
    */
   SECTION("One Pair")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::ONE_PAIR][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::ONE_PAIR][Sample::EQUIVALENT]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent Two Pair Hands.
    */
   SECTION("Two Pair")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::TWO_PAIR][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::TWO_PAIR][Sample::EQUIVALENT]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent Three of a Kind Hands.
    */
   SECTION("Three of a Kind")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::THREE_OF_A_KIND][Sample::EXAMPLE_1]
      );
      HandPtr hand2 = make_shared<PokerHand>(
          input[Category::THREE_OF_A_KIND][Sample::EQUIVALENT]
      );
      cerr << hand1->getScore() << " " << hand2->getScore() << endl;
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent Straight Hands.
    */
   SECTION("Straight")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::STRAIGHT][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::STRAIGHT][Sample::EQUIVALENT]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent Flush Hands.
    */
   SECTION("Flush")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::FLUSH][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::FLUSH][Sample::EQUIVALENT]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent Full House Hands.
    */
   SECTION("Full House")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::FULL_HOUSE][Sample::EXAMPLE_1]
          );
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::FULL_HOUSE][Sample::EQUIVALENT]
          );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent Four of a Kind Hands.
    */
   SECTION("Four of a Kind")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::FOUR_OF_A_KIND][Sample::EXAMPLE_1]
      );
      HandPtr hand2 = make_shared<PokerHand>(
          input[Category::FOUR_OF_A_KIND][Sample::EQUIVALENT]
      );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
   }

   /**
    * @brief Test Rank-Equivalent Straight Flush Hands.
    */
   SECTION("Straight Flush")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::STRAIGHT_FLUSH][Sample::EXAMPLE_1]
      );
      HandPtr hand2 = make_shared<PokerHand>(
          input[Category::STRAIGHT_FLUSH][Sample::EQUIVALENT]
      );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }
}

/**
 * @brief Test section for verifying Outcome of same hand types.
 *
 */
TEST_CASE("Test Similar Hand Outcome")
{
   /**
    * @brief Test Outcome of High Card vs High Card Hand.
    */
   SECTION("High Card vs High Card")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::HIGH_CARD][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::HIGH_CARD][Sample::EXAMPLE_2]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of One Pair vs One Pair Hand.
    */
   SECTION("One Pair vs One Pair")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::ONE_PAIR][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::ONE_PAIR][Sample::EXAMPLE_2]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of Two Pair vs Two Pair Hand.
    */
   SECTION("Two Pair vs Two Pair")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::TWO_PAIR][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::TWO_PAIR][Sample::EXAMPLE_2]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of Three of a Kind vs Three of a Kind Hand.
    */
   SECTION("Three of a Kind vs Three of a Kind")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::THREE_OF_A_KIND][Sample::EXAMPLE_1]
      );
      HandPtr hand2 = make_shared<PokerHand>(
          input[Category::THREE_OF_A_KIND][Sample::EXAMPLE_2]
      );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of Straight vs Straight Hand.
    */
   SECTION("Straight vs Straight")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::STRAIGHT][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::STRAIGHT][Sample::EXAMPLE_2]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of Flush vs Flush Hand.
    */
   SECTION("Flush vs Flush")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::FLUSH][Sample::EXAMPLE_1]);
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::FLUSH][Sample::EXAMPLE_2]);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of Full House vs Full House Hand.
    */
   SECTION("Full House vs Full House")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::FULL_HOUSE][Sample::EXAMPLE_1]
          );
      HandPtr hand2 =
          make_shared<PokerHand>(input[Category::FULL_HOUSE][Sample::EXAMPLE_2]
          );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of Four of a Kind vs Four of a Kind Hand.
    */
   SECTION("Four of a Kind vs Four of a Kind")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::FOUR_OF_A_KIND][Sample::EXAMPLE_1]
      );
      HandPtr hand2 = make_shared<PokerHand>(
          input[Category::FOUR_OF_A_KIND][Sample::EXAMPLE_2]
      );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }

   /**
    * @brief Test Outcome of Straight Flush vs Straight Flush Hand.
    */
   SECTION("Straight Flush vs Straight Flush")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::STRAIGHT_FLUSH][Sample::EXAMPLE_1]
      );
      HandPtr hand2 = make_shared<PokerHand>(
          input[Category::STRAIGHT_FLUSH][Sample::EXAMPLE_2]
      );
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
   }
}

/**
 * @brief Test section for verifying mixed hand Outcomes.
 *
 */
TEST_CASE("Test Mixed Hand Outcomes")
{
   /**
    * @brief Test High Card vs Mixed Hands.
    */
   SECTION("High Card vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::HIGH_CARD][Sample::LOWEST]);
      for (int i = 0; i < 9; ++i) {
         if (i != Category::HIGH_CARD) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::HIGH_CARD) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test One Pair vs Mixed Hands.
    */
   SECTION("One Pair vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::ONE_PAIR][Sample::LOWEST]);
      for (int i = 0; i < 9; ++i) {
         if (i != Category::ONE_PAIR) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::ONE_PAIR) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test Two Pair vs Mixed Hands.
    */
   SECTION("Two Pair vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::TWO_PAIR][Sample::LOWEST]);
      for (int i = 0; i < 9; ++i) {
         if (i != Category::TWO_PAIR) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::TWO_PAIR) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test Three of a Kind vs Mixed Hands.
    */
   SECTION("Three of a Kind vs Mixed")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::THREE_OF_A_KIND][Sample::LOWEST]
      );
      for (int i = 0; i < 9; ++i) {
         if (i != Category::THREE_OF_A_KIND) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::THREE_OF_A_KIND) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test Straight vs Mixed Hands.
    */
   SECTION("Straight vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::STRAIGHT][Sample::LOWEST]);
      for (int i = 0; i < 9; ++i) {
         if (i != Category::STRAIGHT) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::STRAIGHT) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test Flush vs Mixed Hands.
    */
   SECTION("Flush vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::FLUSH][Sample::LOWEST]);
      for (int i = 0; i < 9; ++i) {
         if (i != Category::FLUSH) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::FLUSH) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test Full House vs Mixed Hands.
    */
   SECTION("Full House vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::FULL_HOUSE][Sample::LOWEST]);
      for (int i = 0; i < 9; ++i) {
         if (i != Category::FULL_HOUSE) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::FULL_HOUSE) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test Four of a Kind vs Mixed Hands.
    */
   SECTION("Four of a Kind vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::FOUR_OF_A_KIND][Sample::LOWEST]
          );
      for (int i = 0; i < 9; ++i) {
         if (i != Category::FOUR_OF_A_KIND) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::FOUR_OF_A_KIND) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }

   /**
    * @brief Test Straight Flush vs Mixed Hands.
    */
   SECTION("Straight Flush vs Mixed")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::STRAIGHT_FLUSH][Sample::LOWEST]
          );
      for (int i = 0; i < 9; ++i) {
         if (i != Category::STRAIGHT_FLUSH) {
            HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
            if (i < Category::STRAIGHT_FLUSH) {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
            } else {
               REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
            }
         }
      }
   }
}

/**
 * @brief Test section for verifying behavior under unique conditions.
 *
 */
TEST_CASE("Corner and Edge Cases")
{
   /**
    * @brief Test the lowest possible hand against all other hand types.
    */
   SECTION("Lowest Possible Hand")
   {
      HandPtr hand1 =
          make_shared<PokerHand>(input[Category::HIGH_CARD][Sample::LOWEST]);
      for (int i = 1; i < 9; ++i) {
         HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::LOWEST]);
         REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
      }
   }

   /**
    * @brief Test the highest possible hand against all other hand types.
    */
   SECTION("Highest Possible Hand")
   {
      HandPtr hand1 = make_shared<PokerHand>(
          input[Category::STRAIGHT_FLUSH][Sample::HIGHEST]
      );
      for (int i = 0; i < 8; ++i) {
         HandPtr hand2 = make_shared<PokerHand>(input[i][Sample::HIGHEST]);
         REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_SELF);
      }
   }

   /**
    * @brief Test hands that are one card away from forming a better hand->
    */
   SECTION("Almost Higher Hand")
   {
      for (int i = 0; i < 9; ++i) {
         HandPtr hand1 = make_shared<PokerHand>(input[i][0]);
         HandPtr hand2 = make_shared<PokerHand>(input[i][1]);
         REQUIRE(Test::evaluate(hand1, hand2) == Outcome::WINNER_OTHER);
      }
   }

   /**
    * @brief Ensure that identical hands will tie.
    */
   SECTION("Identical Hands")
   {
      for (int i = 0; i < 9; ++i) {
         HandPtr hand1 = make_shared<PokerHand>(input[i][0]);
         HandPtr hand2 = make_shared<PokerHand>(input[i][0]);
         REQUIRE(Test::evaluate(hand1, hand2) == Outcome::EQUAL_HAND);
      }
   }
}

/**
 * @brief Test section for verifying behavior at program limits.
 */
TEST_CASE("Test Boundary Cases")
{
   /**
    * @brief Test Outcome of More Than Five Cards.
    */
   SECTION("Compare More Than 5 Cards")
   {
      HandPtr hand1 = make_shared<PokerHand>(input[Category::INVALID_HAND][0]);
      HandPtr hand2 = make_shared<PokerHand>(input[0][0]);
      REQUIRE(hand1->getScore() == Outcome::EQUAL_HAND);
      REQUIRE(hand1->getCategory() == Category::INVALID_HAND);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::INVALID_COMPARISON);
   }

   /**
    * @brief Test Outcome of Less Than Five Cards.
    */
   SECTION("Compare Less Than 5 Cards")
   {
      HandPtr hand1 = make_shared<PokerHand>(input[Category::INVALID_HAND][1]);
      HandPtr hand2 = make_shared<PokerHand>(input[0][0]);
      REQUIRE(hand1->getScore() == Outcome::EQUAL_HAND);
      REQUIRE(hand1->getCategory() == Category::INVALID_HAND);
      REQUIRE(Test::evaluate(hand1, hand2) == Outcome::INVALID_COMPARISON);
   }
}

/**
 * @brief Test section for verifying the correctness of error codes.
 */
TEST_CASE("Test Error Cases")
{
   /**
    * @brief Test More Than Five Cards.
    */
   SECTION("More Than 5 Cards")
   {
      HandPtr hand = make_shared<PokerHand>(input[Category::INVALID_HAND][0]);
      REQUIRE(hand->isValid() == false);
   }

   /**
    * @brief Test Less Than Five Cards.
    */
   SECTION("Less Than 5 Cards")
   {
      HandPtr hand = make_shared<PokerHand>(input[Category::INVALID_HAND][1]);
      REQUIRE(hand->isValid() == false);
   }

   /**
    * @brief Test Duplicate Cards.
    */
   SECTION("Duplicate Cards")
   {
      HandPtr hand = make_shared<PokerHand>(input[Category::INVALID_HAND][2]);
      REQUIRE(hand->isValid() == false);
   }

   /**
    * @brief Test Invalid Card Suit.
    */
   SECTION("Invalid Card Suit")
   {
      HandPtr hand = make_shared<PokerHand>(input[Category::INVALID_HAND][3]);
      REQUIRE(hand->isValid() == false);
   }

   /**
    * @brief Test Invalid Card Rank.
    */
   SECTION("Invalid Card Rank")
   {
      HandPtr hand = make_shared<PokerHand>(input[Category::INVALID_HAND][2]);
      REQUIRE(hand->isValid() == false);
   }
}
