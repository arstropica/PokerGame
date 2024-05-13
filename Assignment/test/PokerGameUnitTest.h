/**
 * @file test/PokerGameUnitTest.h
 * @brief Tester class for poker game.
 */

#ifndef POKERGAMEUNITTEST_H
#define POKERGAMEUNITTEST_H

#include "../src/game/resources/Hand.h"
#include "../src/game/resources/PokerHand.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

/**
 * @class PokerGameUnitTest
 * @brief Tester class for poker game.
 */
class PokerGameUnitTest
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
      COMPARISON = 2,
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

   ///< Test Input Data.
   static std::vector<std::vector<std::array<std::string, 3>>> input;
};

#endif // POKERGAMEUNITTEST_H
