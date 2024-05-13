/**
 * @file test/PokerHandTest.h
 * @brief Defines testing functionlaity for Poker Hand functionality.
 */
#ifndef POKERHANDTEST_H
#define POKERHANDTEST_H

#include "../src/game/resources/Hand.h"
#include "../src/game/resources/PokerHand.h"

/**
 * @class PokerHandTest
 * @brief Defines testing functionality.
 */
class PokerHandTest
{
 public:
   /**
    * @brief
    *
    */
   PokerHandTest();

   /**
    * @brief Runs the evaluation.
    */
   void run() const;

   /**
    * @brief Compares two hands
    *
    * @param hand1 std::shared_ptr<Hand>
    * @param hand2 std::shared_ptr<Hand>
    * @return PokerHand::Comparison
    */
   static PokerHand::Comparison compare(
       const std::shared_ptr<Hand> &hand1, const std::shared_ptr<Hand> &hand2
   );

 private:
   /**
    * @brief Prompts user for a hand.
    *
    * @param handNumber
    * @return std::shared_ptr<Hand>
    */
   std::shared_ptr<Hand> promptUser(int handNumber) const;

   /**
    * @brief Prints the hand information.
    *
    * @param std::shared_ptr<Hand> hand
    * @param handNumber
    */
   void printHand(const std::shared_ptr<Hand> hand, int handNumber) const;

   /**
    * @brief Prints the winning hand information.
    *
    * @param winner
    */
   void printWinner(PokerHand::Comparison winner) const;
};
#endif // POKERHANDTEST_H
