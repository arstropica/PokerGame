/**
 * @file test/PokerHandUnitTest.h
 * @brief Tester class for comparing poker hands.
 */

#ifndef POKERHANDUNITTEST_H
#define POKERHANDUNITTEST_H

#include "../src/game/resources/Hand.h"
#include "../src/game/resources/PokerHand.h"
#include <array>
#include <memory>
#include <string>

/**
 * @class PokerHandUnitTest
 * @brief Tester class for comparing poker hands.
 */
class PokerHandUnitTest
{
 public:
   /**
    * @enum Sample
    * @brief Represents test sample types for a poker hand.
    */
   enum Sample
   {
      EXAMPLE_1 = 0,
      EXAMPLE_2 = 1,
      LOWEST = 2,
      HIGHEST = 3,
      EQUIVALENT = 4,
      COUNTEREXAMPLE = 5,
   };

   /**
    * @struct TestResult
    * @brief A structure that encapsulates the evaluation of a hand.
    *
    * This structure contains a category variable for the type of hand
    * and a score calculated from the hand type and card values.
    */
   struct TestResult
   {
      PokerHand::Category category; ///< The type of hand.
      long long score;              ///< The raw hand score.
   };

   /**
    * @brief Compares two hands and returns the winner or zero if tied.
    *
    * @param std::shared_ptr<Hand> hand1
    * @param std::shared_ptr<Hand> hand2
    * @return Hand::Comparison The comparison result.
    */
   static Hand::Comparison evaluate(
       const std::shared_ptr<Hand> &hand1, const std::shared_ptr<Hand> &hand2
   );

   static std::string input[10][6]; ///< Test Input Data.
};

#endif // POKERHANDUNITTEST_H
