/**
 * @file src/game/resources/PokerHand.h
 * @brief Defines functionality for a poker hand.
 */
#ifndef POKERHAND_H
#define POKERHAND_H

#include "Hand.h"
#include <compare>
#include <memory>
#include <string>
#include <vector>

class Card; ///< Forward declaration of Card class

/**
 * @class PokerHand
 * @brief Represents a poker hand.
 *
 * The PokerHand class is a derived class of the Hand class and provides
 * functionality to simulate a poker hand.
 */
class PokerHand : public Hand
{
 public:
   /**
    * @brief Enumerates possible types of card hand.
    */
   enum Category
   {
      HIGH_CARD = 0,
      ONE_PAIR = 1,
      TWO_PAIR = 2,
      THREE_OF_A_KIND = 3,
      STRAIGHT = 4,
      FLUSH = 5,
      FULL_HOUSE = 6,
      FOUR_OF_A_KIND = 7,
      STRAIGHT_FLUSH = 8,
      INVALID_HAND = 9
   };

   static const int HBWIDTH = 52; ///< The base mask width for the hand

   /**
    * @brief Defines hand names.
    */
   static const std::vector<std::string> HAND_NAMES;

   /**
    * @brief Stores information about the hand.
    */
   struct Detail
   {
      Category category;
      long long score;
   };

   /**
    * @brief Default Constructor
    */
   PokerHand();

   /**
    * @brief Notation Constructor.
    *
    * @param notation The string notation of the poker hand.
    */
   PokerHand(std::string notation);

   /**
    * @brief Constructor that takes a vector of CardPtr.
    *
    * @param cards The vector of CardPtr representing the hand.
    */
   PokerHand(std::vector<std::shared_ptr<Card>> &cards);

   /**
    * @see Hand::isValid
    */
   bool isValid() const override;

   /**
    * @see CardCollection::getCardNames
    */
   std::vector<std::string> getCardNames(bool verbose = true) const override;

   /**
    * @see Hand::getScore
    */
   long long getScore() const override;

   /**
    * @see Hand::getScore
    */
   std::string getScore(bool grouped) const override;

   /**
    * @see Hand::getCategory
    */
   int getCategory() const override;

   /**
    * @see Hand::compare
    */
   Comparison compare(const std::shared_ptr<Hand> other) const override;

   /**
    * @see Hand::getDescription
    */
   std::string getDescription() const override;

   /**
    * @brief Get the indices of cards that match a given Category.
    *
    * @param Category category
    * @return std::vector<int>
    */
   std::vector<int> indexByCategory(const Category category) const;

   /**
    * @brief Get the indices of cards that match a given cardinality.
    *
    * @param int cardinality
    * @return std::vector<int>
    */
   std::vector<int> indexByCardinality(const int cardinality) const;

   /**
    * @see Hand::operator<=>
    */
   std::strong_ordering operator<=>(const std::shared_ptr<Hand> other
   ) const override;

   /**
    * @see Hand::operator==
    */
   bool operator==(const std::shared_ptr<Hand> other) const override;

 protected:
   /**
    * @see Hand::validate
    */
   bool validate(const std::vector<std::shared_ptr<Card>> &cards) override;

   /**
    * @see Hand::parse
    */
   std::vector<std::shared_ptr<Card>> parse(const std::string notation
   ) override;

   /**
    * @see Hand::process
    */
   void process() override;

   /**
    * @see Hand::compute
    */
   void compute() override;

 private:
   static const int VALID_COUNT{5}; ///< The valid count of cards in a hand
   Detail detail;                   ///< Hand detail information

   /**
    * @brief Checks if the hand is a flush.
    *
    * @return true if the hand is a flush, false otherwise.
    */
   bool isFlush() const;

   /**
    * @brief Checks if the hand is a straight.
    *
    * @return true if the hand is a straight, false otherwise.
    */
   bool isStraight() const;

   /**
    * @brief Checks if the hand is three of a kind.
    *
    * @return true if the hand is three of a kind, false otherwise.
    */
   bool isThreeOfAKind() const;

   /**
    * @brief Checks if the hand is four of a kind.
    *
    * @return true if the hand is four of a kind, false otherwise.
    */
   bool isFourOfAKind() const;

   /**
    * @brief Checks if the hand is a full house.
    *
    * @return true if the hand is a full house, false otherwise.
    */
   bool isFullHouse() const;

   /**
    * @brief Checks if the hand is two pair.
    *
    * @return true if the hand is two pair, false otherwise.
    */
   bool isTwoPair() const;

   /**
    * @brief Checks if the hand is one pair.
    *
    * @return true if the hand is one pair, false otherwise.
    */
   bool isOnePair() const;

   /**
    * @brief Checks if the hand has exactly n pairs of cards.
    *
    * @param n Number of pairs to check for.
    * @return true if hand has exactly n pairs of cards, otherwise false
    */
   bool countPairs() const;

   /**
    * @brief Returns the number of distinct or identical cards in a hand.
    * @param inverse Flag to return the number of identical cards.
    *
    * @return The number of distinct cards in the hand.
    */
   int getCardinality(const bool inverse = false) const;

   /**
    * @brief Returns the rank value of the nth highest card.
    *
    * @param startIdx The starting index to consider when finding the nth
    * highest card.
    * @return The rank value of the nth highest card.
    */
   long long getOrdinality(int startIdx = 0) const;
};

#endif // POKERHAND_H
