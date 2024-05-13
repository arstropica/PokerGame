/**
 * @file src/game/resources/PokerHand.cpp
 * @brief Implementation of the PokerHand class.
 */
#include "PokerHand.h"
#include "../../../utils/Logger.h"
#include "Card.h"
#include "Hand.h"
#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <map>
#include <regex>
#include <unordered_set>

using namespace std;
using CardPtr = shared_ptr<Card>;
using HandPtr = shared_ptr<Hand>;

const vector<string> PokerHand::HAND_NAMES = {
    "High card",
    "One pair",
    "Two pair",
    "Three of a kind",
    "Straight",
    "Flush",
    "Full house",
    "Four of a kind",
    "Straight flush",
    "Invalid"};

PokerHand::PokerHand() : Hand(vector<CardPtr>()), detail{INVALID_HAND, 0} {}

PokerHand::PokerHand(string notation)
    : Hand(parse(notation)), detail{INVALID_HAND, 0}
{
   process();
}

PokerHand::PokerHand(vector<CardPtr> &cards) : Hand(cards)
{
   process();
}

bool PokerHand::validate(const vector<CardPtr> &cards)
{
   if (cards.size() != PokerHand::VALID_COUNT) {
      Logger::debug(
          string("Poker Hand validation: ") +
          "Invalid hand size: " + to_string(cards.size())
      );
      return false;
   }
   for (auto &card : cards) {
      if (!card->isValid()) {
         Logger::debug(
             string("Poker Hand validation: ") +
             "Invalid card found: " + card->getName() + "."
         );
         return false;
      }
   }
   return true;
}

void PokerHand::process()
{
   valid = validate(cards);
   std::sort(cards.begin(), cards.end(), Hand::sort);
   compute();
}

void PokerHand::compute()
{
   int categoryShift = HBWIDTH; ///< Shift for category bits
   long long categoryBase;      ///< Base value for category bits
   long long ordinality = getOrdinality();

   if (valid) {
      if (isFlush() && isStraight()) {
         detail.category = STRAIGHT_FLUSH;
      } else if (isFourOfAKind()) {
         detail.category = FOUR_OF_A_KIND;
      } else if (isFullHouse()) {
         detail.category = FULL_HOUSE;
      } else if (isFlush()) {
         detail.category = FLUSH;
      } else if (isStraight()) {
         detail.category = STRAIGHT;
      } else if (isThreeOfAKind()) {
         detail.category = THREE_OF_A_KIND;
      } else if (isTwoPair()) {
         detail.category = TWO_PAIR;
      } else if (isOnePair()) {
         detail.category = ONE_PAIR;
      } else {
         detail.category = HIGH_CARD;
      }
      categoryBase = (1LL * detail.category);
      if (detail.category >= STRAIGHT) {
         categoryBase += 1;
         if (detail.category >= STRAIGHT_FLUSH) {
            categoryBase += 1;
         }
      }

      ///< if the hand is a low straight, adjust the category base
      if (detail.category == STRAIGHT || detail.category == STRAIGHT_FLUSH) {
         if (cards[0]->getValue() == 2 && cards[4]->getValue() == 14) {
            categoryBase--; ///< Reduce the category base by 1
         }
      }
      detail.score = ordinality;
      detail.score |= (categoryBase << categoryShift);
      Logger::debug(string("Hand ordinality: ") + to_string(ordinality));
      Logger::debug(string("Hand Category: ") + to_string(detail.category));
      Logger::debug(string("Hand score: ") + to_string(detail.score));
   } else {
      Logger::trace("Hand:  Invalid hand detected.");
      detail.category = INVALID_HAND;
      detail.score = 0;
   }
}

vector<CardPtr> PokerHand::parse(const string notation)
{
   unordered_set<string> tokens;
   string delimiter = "\\s+";
   regex patt(delimiter);
   vector<CardPtr> cards_;
   sregex_token_iterator end;

   Logger::trace(
       string("Poker Hand: ") + "Parsing notation: " + notation + "."
   );
   sregex_token_iterator token(notation.begin(), notation.end(), patt, -1);
   for (; token != end; ++token) {
      tokens.insert(*token);
      Logger::trace(
          string("Poker Hand: ") + "Token matched: " + token->str() + "."
      );
   }
   for (string token : tokens) {
      cards_.push_back(make_shared<Card>(token));
      Logger::trace(string("Poker Hand: ") + "Token inserted: " + token + ".");
   }

   return cards_;
}

Hand::Comparison PokerHand::compare(const HandPtr other) const
{
   if (isValid() && other->isValid()) {
      if (getScore() > other->getScore()) {
         return WINNER_SELF;
      } else if (getScore() < other->getScore()) {
         return WINNER_OTHER;
      } else {
         return EQUAL_HAND;
      }
   }
   Logger::trace(string("Poker Hand: ") + "Invalid hand detected.");
   return INVALID_COMPARISON;
}

bool PokerHand::isValid() const
{
   return valid;
}

long long PokerHand::getScore() const
{
   return detail.score;
}

string PokerHand::getScore(bool grouped) const
{
   string binStr = bitset<64>(detail.score).to_string();
   if (grouped) {
      binStr.insert(51, " ");
      binStr.insert(38, " ");
      binStr.insert(25, " ");
      binStr.insert(12, " ");
   }
   return binStr;
}

int PokerHand::getCategory() const
{
   return detail.category;
}

bool PokerHand::isFlush() const
{
   // Compare suit of all cards to the first one
   return std::all_of(
       cards.begin(),
       cards.end(),
       [s = cards.front()->getSuit()](const CardPtr &card) {
          return card->getSuit() == s;
       }
   );
}

bool PokerHand::isStraight() const
{
   // Check if the cards form a numerical sequence
   for (size_t i = 1; i < cards.size(); ++i) {
      int a = cards[i]->getValue(), b = cards[i - 1]->getValue();
      if ((a != (b + 1)) && !(i == 4 && a == 14 && b == 5)) { // Low Ace
         return false;
      }
   }
   return true;
}

bool PokerHand::isThreeOfAKind() const
{
   // Check for exactly three cards of the same rank
   return getCardinality() == 3 && getCardinality(true) == 3;
}

bool PokerHand::isFourOfAKind() const
{
   // Check for exactly four cards of the same rank
   return getCardinality() == 2 && getCardinality(true) == 4;
}

bool PokerHand::isFullHouse() const
{
   return getCardinality() == 2 && getCardinality(true) == 3;
}

bool PokerHand::isTwoPair() const
{
   // Exactly two pairs of cards
   return (getCardinality() == 3 && getCardinality(true) == 2);
}

bool PokerHand::isOnePair() const
{
   // Exactly one pair of cards
   return getCardinality() == 4 && getCardinality(true) == 2;
}

int PokerHand::getCardinality(const bool inverse) const
{
   map<int, int> ranks;
   int cardinality = 0;
   for (const auto &card : cards) {
      ranks[card->getValue()]++;
   }
   for (const auto &it : ranks) {
      if (inverse) {
         cardinality = max(cardinality, it.second);
      } else {
         cardinality = it.second > 0 ? cardinality + 1 : cardinality;
      }
   }
   return cardinality;
}

long long PokerHand::getOrdinality(int startIdx) const
{
   map<char, long long> suits = {{'C', 0}, {'D', 1}, {'H', 2}, {'S', 3}};
   map<int, long long> rcnts;
   long long ordinality = 0;
   long long rank_range = 1LL * 13;
   long long count_range = 3LL * 13;
   long long suit, count_base, rank_shift, count_shift;
   int j = VALID_COUNT;
   int rank;

   for (const auto &card : cards) { ///< Count cards by rank
      rcnts[card->getValue()]++;
   }

   for (int i = 0; i < cards.size(); ++i) {
      if (VALID_COUNT - startIdx >= j) {       ///< Exclude first startIdx cards
         CardPtr card = cards.at(i);           ///< Get the card
         rank = card->getValue();              ///< Get the rank value
         rank_shift = 1LL * (rank - 2);        ///< Get rank shift
         count_shift = (rcnts[rank] - 2) * 13; ///< Get count shift
         count_base = 1LL * (rank - 2);        ///< Get count multiply
         ordinality |= (1LL << rank_shift);    ///< Set rank bit
         if (rcnts[rank] > 1) {                ///< Set count bit
            ordinality |= (1LL << count_base << count_shift << rank_range);
         }
      }
      j--;
   }
   return ordinality;
}

string PokerHand::getDescription() const
{
   return HAND_NAMES.at(detail.category);
}

vector<string> PokerHand::getCardNames(bool verbose) const
{
   std::vector<std::string> cardNames;
   cardNames.reserve(cards.size());
   for (const auto &cardPtr : cards) {
      cardNames.push_back(cardPtr->getName(verbose));
   }
   return cardNames;
}

vector<int> PokerHand::indexByCategory(const Category category) const
{
   vector<int> indices;
   switch (category) {
      case ONE_PAIR:
         indices = indexByCardinality(2);
         break;
      case TWO_PAIR:
         indices = indexByCardinality(2);
         if (indices.size() != 4) {
            indices.clear();
         }
         break;
      case THREE_OF_A_KIND:
         indices = indexByCardinality(3);
         break;
      case FOUR_OF_A_KIND:
         indices = indexByCardinality(4);
         break;
      case STRAIGHT_FLUSH:
      case STRAIGHT:
      case FLUSH:
      case FULL_HOUSE:
         if (detail.category == category) {
            for (int i = 0; i < cards.size(); ++i) {
               indices.push_back(i);
            }
         }
         break;
      case INVALID_HAND:
      case HIGH_CARD:
         break;
   }
   return indices;
}

vector<int> PokerHand::indexByCardinality(const int cardinality) const
{
   vector<int> indices;
   map<int, int> ranks;
   for (const auto &card : cards) {
      ranks[card->getValue()]++;
   }
   for (const auto &it : ranks) {
      if (it.second == cardinality) {
         for (size_t i = 0; i < cards.size(); ++i) {
            if (cards[i]->getValue() == it.first) {
               indices.push_back(i);
            }
         }
      }
   }
   return indices;
}

strong_ordering PokerHand::operator<=>(const HandPtr other) const
{
   if (isValid() && other->isValid()) {
      if (getScore() > other->getScore()) {
         return strong_ordering::greater;
      } else if (getScore() < other->getScore()) {
         return strong_ordering::less;
      } else {
         return strong_ordering::equal;
      }
   }
   return strong_ordering::equivalent;
}

bool PokerHand::operator==(const HandPtr other) const
{
   return getScore() == other->getScore();
}
