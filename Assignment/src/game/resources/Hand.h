/**
 * @file src/game/resources/Hand.h
 * @brief Defines functionality for a basic card hand.
 */
#ifndef HAND_H
#define HAND_H

#include "CardCollection.h"
#include <compare>
#include <memory>
#include <string>
#include <vector>

class Card; ///< Forward declaration of Card class
class Hand; ///< Forward declaration of Hand class

/**
 * @class Hand
 * @brief Abstract Base defining a card hand in a card game.
 */
class Hand : public CardCollection, public std::enable_shared_from_this<Hand>
{
 public:
   /**
    * @brief Enumerates possible categories for a card hand.
    */
   enum Category
   {
      INVALID_HAND = 0,
   };

   /**
    * @brief Represents possible evaluation states.
    */
   enum Comparison
   {
      INVALID_COMPARISON = -1,
      EQUAL_HAND = 0,
      WINNER_SELF = 1,
      WINNER_OTHER = 2
   };

   /**
    * @brief Default Constructor.
    *
    */
   Hand();

   /**
    *
    * @brief Constructs a Hand object from a Card pointer vector.
    *
    * @param cards Vector containing Card pointers.
    */
   Hand(std::vector<std::shared_ptr<Card>> cards_v);

   /**
    * @brief Compares the hand with another hand and returns the outcome.
    * @param other Pointer to the other hand to compare with.
    * @return The comparison outcome as an Comparison enum.
    */
   virtual Comparison compare(const std::shared_ptr<Hand> other) const;

   /**
    * @see CardCollection::add
    */
   void add(const std::shared_ptr<Card> &card) override;

   /**
    * @see CardCollection::remove
    */
   void remove(const std::shared_ptr<Card> &card) override;

   /**
    * @brief Computes the score of the hand.
    * @return The score of the hand as a long long.
    */
   virtual long long getScore() const = 0;

   /**
    * @brief Gets the score of the hand as a string.
    * @param grouped Flag to indicate if the binary string should be grouped.
    * @return The score of the hand as a binary string.
    */
   virtual std::string getScore(bool grouped) const = 0;

   /**
    * @brief Gets the category of the hand.
    * @return The category of the hand as an integer.
    */
   virtual int getCategory() const = 0;

   /**
    * @brief Pure virtual function to check if the hand is valid.
    * @return True if the hand is valid, false otherwise.
    */
   virtual bool isValid() const = 0;

   /**
    * @brief Gets the description of the hand.
    * @return Description of the hand as a string.
    */
   virtual std::string getDescription() const = 0;

   /**
    * @brief Three-way comparison operator.
    *
    * @param other Pointer to the other hand to compare with.
    * @return The comparison result as a strong ordering.
    */
   virtual std::strong_ordering operator<=>(const std::shared_ptr<Hand> other
   ) const = 0;

   /**
    * @brief Equality operator.
    *
    * @param other Pointer to the other hand to compare with.
    * @return true if the hands are equal, false otherwise.
    */
   virtual bool operator==(const std::shared_ptr<Hand> other) const = 0;

   /**
    * @brief Adds a card to the hand.
    * @param card Pointer to the card to add.
    * @return Reference to the modified hand.
    */
   std::shared_ptr<Hand> operator+=(const std::shared_ptr<Card> &card);

   /**
    * @brief Removes a card from the hand.
    * @param card Pointer to the card to remove.
    * @return Reference to the modified hand.
    */
   std::shared_ptr<Hand> operator-=(const std::shared_ptr<Card> &card);

 protected:
   bool valid; ///< Flag indicating if the hand is valid

   /**
    * @brief Sorts the cards in the hand.
    *
    * @param a Pointer to the first card to compare.
    * @param b Pointer to the second card to compare.
    */
   static bool
   sort(const std::shared_ptr<Card> &a, const std::shared_ptr<Card> &b);

   /**
    * @brief Performs required operations upon initialzation or state changes.
    */
   virtual void process() = 0;

   /**
    * @brief Computes the score and category of the hand.
    */
   virtual void compute() = 0;

   /**
    * @brief Parses the hand notation and returns a private reference to cards.
    * @param notation The notation representing the hand.
    * @return A reference to the vector of Card pointers.
    */
   virtual std::vector<std::shared_ptr<Card>> parse(const std::string notation
   ) = 0;

   /**
    * @brief Validates the card hand.
    * @param cards The vector of Card pointers to validate.
    * @return True if the hand is valid, false otherwise.
    */
   virtual bool validate(const std::vector<std::shared_ptr<Card>> &cards) = 0;
};

#endif // HAND_H