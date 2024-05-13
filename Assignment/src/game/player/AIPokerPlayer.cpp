/**
 * @file src/player/AIPokerPlayer.cpp
 * @brief Implementation of the derived AIPokerPlayer class.
 */

#include "AIPokerPlayer.h"
#include "../../../utils/Logger.h"
#include "../PokerEngine.h"
#include "../resources/PokerHand.h"
#include <algorithm>
#include <numeric>

using namespace std;
using EnginePtr = shared_ptr<PokerEngine>;

mt19937 AIPokerPlayer::rng(random_device{}()); ///< Initialize static RNG

AIPokerPlayer::AIPokerPlayer(EnginePtr engine, int id, double balance)
    : PokerPlayer(engine, id, UserType::AI, balance),
      strategy(Strategy::BALANCED)
{}

AIPokerPlayer::AIPokerPlayer(
    EnginePtr engine, int id, double balance, Strategy strategy
)
    : PokerPlayer(engine, id, UserType::AI, balance), strategy(strategy)
{}

vector<int> AIPokerPlayer::discard()
{
   PokerHand::Category category = (PokerHand::Category)hand->getCategory();
   vector<int> discards(hand->size());
   vector<int> keep;

   iota(discards.begin(), discards.end(), 0); ///< initialize using std::iota

   Logger::debug(getName() + " has a " + hand->getDescription() + ".");
   Logger::debug(hand->getCardsDescription());

   switch (category) {
      case PokerHand::Category::HIGH_CARD:
         break;
      case PokerHand::Category::ONE_PAIR:
      case PokerHand::Category::TWO_PAIR:
      case PokerHand::Category::THREE_OF_A_KIND:
      case PokerHand::Category::FOUR_OF_A_KIND:
         keep = hand->indexByCategory(PokerHand::Category::ONE_PAIR);
         break;
      case PokerHand::Category::STRAIGHT:
      case PokerHand::Category::FLUSH:
      case PokerHand::Category::FULL_HOUSE:
      case PokerHand::Category::STRAIGHT_FLUSH:
      case PokerHand::Category::INVALID_HAND:
         discards.clear();
         break;
   }
   if (keep.size() > 0) {
      // Remove all indexes from discards that are not in the keep vector
      std::sort(keep.begin(), keep.end(), std::greater<int>()); ///< desc sort
      for (const auto &idx : keep) {
         if (idx < discards.size()) { ///< index check
            discards.erase(discards.begin() + idx);
         }
      }
   }
   if (discards.size() > 0) {
      Logger::debug(
          getName() + " is discarding " + to_string(discards.size()) + " cards."
      );
   }
   return discards;
}

double AIPokerPlayer::bet()
{
   double blind = engine->getBlind();
   double minBet = max(blind, balance * (static_cast<double>(strategy) / 100));
   int variance = static_cast<int>(minBet / 4);
   double bet = 0.0;
   string message, cBet;
   PokerHand::Category category =
       static_cast<PokerHand::Category>(hand->getCategory());

   // Create a distribution range from 0 to +variance
   uniform_int_distribution<> dist(0, variance);
   minBet += dist(rng); // Randomize bet amount
   if (minBet < blind && balance >= blind) {
      minBet = blind;
   }

   Logger::debug(
       getName() + " has a " + hand->getDescription() + ", a minimum bet of " +
       PokerEngine::formatCurrency(blind) + ", and a balance of " +
       PokerEngine::formatCurrency(balance) + "."
   );

   switch (category) {
      case PokerHand::Category::HIGH_CARD:
         if (minBet <=
             (balance * (static_cast<double>(strategy) /
                         static_cast<double>(Strategy::AGGRESSIVE)))) {
            bet = minBet;
         }
         break;
      case PokerHand::Category::ONE_PAIR:
      case PokerHand::Category::TWO_PAIR:
      case PokerHand::Category::THREE_OF_A_KIND:
      case PokerHand::Category::STRAIGHT:
      case PokerHand::Category::FLUSH:
      case PokerHand::Category::FULL_HOUSE:
      case PokerHand::Category::FOUR_OF_A_KIND:
      case PokerHand::Category::STRAIGHT_FLUSH:
         if (minBet * static_cast<double>(category) < balance) {
            bet = minBet * static_cast<double>(category);
         } else {
            bet = balance;
         }
         break;
      case PokerHand::Category::INVALID_HAND:
         break;
   }

   if (bet > balance) {
      bet = balance;
   }
   if (bet == 0) {
      fold();
   } else if (bet < blind) {
      allIn(bet);
   } else if (bet == blind) {
      call(bet);
   } else {
      raise(bet);
   }
   balance -= bet;
   return bet;
}
