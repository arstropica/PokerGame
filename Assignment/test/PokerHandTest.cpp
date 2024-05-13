/**
 * @file test/PokerHandTest.cpp
 * @brief Implementation of the PokerHandTest class.
 */
#include "PokerHandTest.h"
#include "../src/game/resources/Hand.h"
#include "../src/game/resources/PokerHand.h"
#include "../utils/Logger.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using HandPtr = shared_ptr<Hand>;

PokerHandTest::PokerHandTest() {}

void PokerHandTest::run() const
{
   HandPtr hand1 = promptUser(1);
   HandPtr hand2 = promptUser(2);
   cout << endl;

   printHand(hand1, 1);
   printHand(hand2, 2);

   PokerHand::Comparison winner = compare(hand1, hand2);

   printWinner(winner);
}

HandPtr PokerHandTest::promptUser(int handNumber) const
{
   while (true) {
      Logger::console(
          string("Enter hand ") + to_string(handNumber) + ": ",
          false
      );
      string input;
      getline(cin, input);
      Logger::debug("User hand input: " + input);

      HandPtr hand = make_shared<PokerHand>(input);

      if (hand->isValid()) {
         return hand; // Return valid hand
      } else {
         Logger::debug("Invalid user hand entered.");
         Logger::console("Invalid hand. Please try again.");
      }
   }
}

void PokerHandTest::printHand(const HandPtr hand, int handNumber) const
{
   ostringstream ss;
   ss << "Hand " << handNumber << "\n"
      << "==========\n";
   if (hand->isValid()) {
      ss << "Type: " << hand->getDescription() << endl;
      ss << "Cards: ";
      auto cardNames = hand->getCardNames();
      ss << " | ";
      for (const auto &cardName : cardNames) {
         ss << cardName << " | ";
      }
      ss << endl;
      ss << "Score: " << hand->getScore() << endl;
   } else {
      ss << "Invalid hand." << endl;
   }
   ss << endl;
   Logger::console(ss.str());
}

PokerHand::Comparison
PokerHandTest::compare(const HandPtr &hand1, const HandPtr &hand2)
{
   return hand1->compare(hand2);
}

void PokerHandTest::printWinner(PokerHand::Comparison winner) const
{
   ostringstream ss;
   ss << "Result: ";
   if (winner > 0) {
      ss << "Hand " << winner << " wins!" << endl;
   } else {
      ss << "It's a tie!" << endl;
   }
   ss << endl;
   Logger::console(ss.str());
}
