/**
 * @file src/game/resources/CardCollection.cpp
 * @brief Implementation of functionality for a Card Group.
 */
#include "CardCollection.h"
#include "../../../utils/Logger.h"
#include "Card.h"
#include <algorithm>

using namespace std;
using CardPtr = shared_ptr<Card>;

CardCollection::CardCollection() : cards(vector<CardPtr>()) {}

CardCollection::CardCollection(vector<CardPtr> cards_v) : cards(cards_v) {}

void CardCollection::add(const CardPtr &card)
{
   Logger::trace("Adding card: " + card->getName(true) + " to collection.");
   cards.push_back(card);
}

void CardCollection::remove(const CardPtr &card)
{
   Logger::trace("Removing card: " + card->getName(true) + " from collection.");
   auto itr = std::remove(cards.begin(), cards.end(), card);
   cards.erase(itr, cards.end());
}

CardPtr CardCollection::get(int idx) const
{
   return cards.at(idx);
}

size_t CardCollection::size() const
{
   return cards.size();
}

bool CardCollection::isEmpty() const
{
   return cards.empty();
}

vector<string> CardCollection::getCardNames(bool verbose) const
{
   vector<string> cardNames;
   cardNames.reserve(cards.size());
   for (const auto &cardPtr : cards) {
      cardNames.push_back(cardPtr->getName(verbose));
   }
   return cardNames;
}

string CardCollection::getCardsDescription(bool verbose) const
{
   string delimiter = " | ";
   string description = "";
   if (!cards.empty()) {
      description += delimiter;
      for (const auto &cardPtr : cards) {
         description += cardPtr->getName(verbose) + delimiter;
      }
   }
   return description;
}