/**
 * @file src/game/resources/Card.h
 * @brief Defines functionality for a Card object.
 */
#ifndef CARD_H
#define CARD_H

#include <compare>
#include <map>
#include <memory>
#include <string>
#include <vector>

/**
 * @class Card
 * @brief This class represents a Poker Card.
 */
class Card
{
 public:
   static const std::vector<char> ranks; ///< Indexed Card Ranks.
   static const std::vector<char> suits; ///< Indexed Card Suits.

   enum ORIENTATION
   {
      FACE_DOWN = 0,
      FACE_UP = 1
   };

   /**
    * @brief Default Constructor for Card.
    *
    * @param token card token value.
    */
   Card(std::string token);

   /**
    * @brief Overloaded Constructor for Card.
    *
    * @param token card token value.
    * @param orientation card orientation.
    */
   Card(std::string token, ORIENTATION orientation);

   /**
    * @brief Checks if the card is valid.
    * @return bool
    */
   bool isValid() const;

   /**
    * @brief Returns the card suit.
    * @return card suit.
    */
   char getSuit() const;

   /**
    * @brief Returns the card rank.
    * @return card rank.
    */
   char getRank() const;

   /**
    * @brief Returns the card value.
    * @return int card value.
    */
   int getValue() const;

   /**
    * @brief Returns the card suit and rank.
    *
    * @param verbose return the longer name format.
    * @return std::string
    */
   virtual std::string getName(bool verbose = false) const;

   /**
    * @brief Gets the orientation of the card.
    * @return The orientation of the card.
    */
   ORIENTATION getOrientation() const;

   /**
    * @brief Toggles the orientation of the card.
    * @param ORIENTATION orientation The new orientation of the card.
    */
   virtual ORIENTATION flip();

   /**
    * @brief Overloads the spaceship operator for rank comparison.
    *
    * @param other The Card object to compare with.
    * @return std::weak_ordering
    */
   virtual std::weak_ordering operator<=>(const std::shared_ptr<Card> &other
   ) const;

   /**
    * @brief Overloaded equality operator for comparing two Card objects.
    *
    * @param other The Card object to compare with.
    * @return true if the Card objects are equal, false otherwise.
    */
   virtual bool operator==(const std::shared_ptr<Card> &other) const;

 protected:
   ORIENTATION orientation; ///< Carc orientation.

   /**
    * @brief Default Constructor for Derived Card.
    */
   Card();

   /**
    * @brief Overloaded Constructor for Derived classes.
    * @param ORIENTATION orientation The orientation of the card.
    */
   Card(const ORIENTATION orientation = FACE_DOWN);

 private:
   static const std::map<char, std::string> legend; ///< Display Names.
   bool valid;                                      ///< Card Validity.
   char suit;                                       ///< Card Suit.
   char rank;                                       ///< Card Rank.
};

#endif // CARD_H
