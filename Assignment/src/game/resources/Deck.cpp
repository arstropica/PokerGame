/**
 * @file src/game/resources/Deck.cpp
 * @brief Implementation of functionality for a 52-card Card Deck.
 */

#include "Deck.h"
#include "../../../utils/Logger.h"
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;
using CardPtr = shared_ptr<Card>;

Deck::Deck() : CardCollection()
{
   reset();
}

Deck::Deck(bool empty) : CardCollection()
{
   if (!empty) {
      reset();
   }
}

void Deck::reset()
{
   cards.clear();
   for (auto &suit : Card::suits) {
      for (auto &rank : Card::ranks) {
         cards.push_back(make_shared<Card>(string(1, rank) + suit));
      }
   }
}

void Deck::shuffle()
{
   size_t n = size();
   if (n == 0) {
      Logger::warn("Cannot shuffle an empty deck.");
      return;
   }
   default_random_engine engine{random_device{}()}; ///< random generator
   uniform_int_distribution<size_t> distribution{0, n - 1}; ///< range[0, n-1]
   Logger::trace("Distribution of size: " + to_string(n) + " computed.");
   for (size_t i = n; i-- > 0;) {
      swap(cards[i], cards[distribution(engine)]); ///< swap random idx cards
   }
   Logger::trace(to_string(n) + " cards swapped.");
}

CardPtr Deck::deal(Card::ORIENTATION orientation)
{
   if (isEmpty()) {
      return nullptr;
   }
   CardPtr card = cards.back(); ///< Last card in deck.
   if (card->getOrientation() != orientation) {
      card->flip();
   }
   remove(card);
   Logger::trace("Dealt card from deck: " + card->getName(true) + ".");
   return card;
}
