/**
 * @file src/game/resources/Hand.cpp
 * @brief Implementation of the Hand base class.
 */
#include "Hand.h"
#include "../../../utils/Logger.h"
#include "Card.h"
#include <algorithm>

using namespace std;
using CardPtr = shared_ptr<Card>;
using HandPtr = shared_ptr<Hand>;

Hand::Hand() : CardCollection(), valid(false) {}

Hand::Hand(vector<CardPtr> cards_v) : CardCollection(), valid(false)
{
   for (auto &card : cards_v) {
      cards.push_back(card);
   }
}

bool Hand::sort(const CardPtr &a, const CardPtr &b)
{
   return a->getValue() < b->getValue();
}

Hand::Comparison Hand::compare(const HandPtr other) const
{
   strong_ordering result = shared_from_this() <=> other;
   return result == strong_ordering::less      ? WINNER_OTHER
          : result == strong_ordering::greater ? WINNER_SELF
                                               : EQUAL_HAND;
}

void Hand::add(const CardPtr &card)
{
   *this += card;
}

void Hand::remove(const CardPtr &card)
{
   *this -= card;
}

HandPtr Hand::operator+=(const CardPtr &card)
{
   Logger::trace("Adding card: " + card->getName(true) + " to collection.");
   cards.push_back(card);
   process();
   return shared_from_this();
}

HandPtr Hand::operator-=(const CardPtr &card)
{
   Logger::trace("Removing card: " + card->getName(true) + " from collection.");
   auto itr = std::remove(cards.begin(), cards.end(), card);
   cards.erase(itr, cards.end());
   process();
   return shared_from_this();
}
