/**
 * @file src/game/resources/Deck.h
 * @brief Card Deck .
 */

#ifndef DECK_H
#define DECK_H

#include "CardCollection.h"
#include <memory>
#include <string>
#include <vector>

class Card; ///< Forward declaration of Card class

/**
 * @class Deck
 * @brief Represents a deck of cards.
 */
class Deck : public CardCollection
{
 public:
   /**
    * @brief Constructs and initializes a new standard 52-card Deck.
    */
   Deck();

   /**
    * @brief Constructs and initializes a new Deck.
    * @param empty Empty deck if true, otherwise a standard 52-card deck.
    */
   Deck(bool empty);

   /**
    * @brief Resets the deck of cards.
    */
   void reset();

   /**
    * @brief Shuffles the deck of cards using the Knuth shuffle algorithm.
    * @link https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
    */
   void shuffle();

   /**
    * @brief Deals a card from the deck.
    * @param orientation Orientation of the card dealt.
    * @return std::shared_ptr<Card> to the card dealt.
    */
   std::shared_ptr<Card>
   deal(Card::ORIENTATION orientation = Card::ORIENTATION::FACE_DOWN);
};
#endif // DECK_H