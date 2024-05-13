/**
 * @file src/game/resources/CardCollection.h
 * @brief Defines basic functionality for a Card Group.
 */
#ifndef CARD_COLLECTION_H
#define CARD_COLLECTION_H

#include "Card.h"
#include <memory>
#include <string>
#include <vector>

/**
 * @class CardCollection
 * @brief Base class for a collection of cards.
 *
 * This class provides a common set of basic operations for managing a
 * collection of cards.
 */
class CardCollection
{
 public:
   /**
    * @brief Default Constructor
    */
   CardCollection();

   /**
    * @brief Construct from a vector of Card pointers.
    *
    * @param cards_v
    */
   CardCollection(std::vector<std::shared_ptr<Card>> cards_v);

   /**
    * @brief Default destructor for the CardCollection class.
    */
   virtual ~CardCollection() = default;

   /**
    * @brief Adds a card to the collection.
    * @param card Pointer to the card to add.
    */
   virtual void add(const std::shared_ptr<Card> &card);

   /**
    * @brief Removes a card from the collection.
    * @param card Pointer to the card to remove.
    * @return std::shared_ptr<Card> if the card was successfully removed,
    * nullptr otherwise.
    */
   virtual void remove(const std::shared_ptr<Card> &card);

   /**
    * @brief Returns a card from the collection by index.
    * @param index Index of the card.
    * @return std::shared_ptr<Card> if the card was found, nullptr otherwise.
    */
   virtual std::shared_ptr<Card> get(int index) const;

   /**
    * @brief Gets the number of cards in the collection.
    * @return The number of cards.
    */
   virtual size_t size() const;

   /**
    * @brief Checks if the collection is empty.
    * @return True if the collection is empty, false otherwise.
    */
   virtual bool isEmpty() const;

   /**
    * @brief Retrieves all card names in the collection.
    * @param verbose Flag to indicate if full names should be returned.
    * @return A vector of strings containing the names of the cards.
    */
   virtual std::vector<std::string> getCardNames(bool verbose = true) const;

   /**
    * @brief Returns a string representation of the cards in the collection.
    *
    * @param verbose Flag for full card descriptions.
    * @return std::string
    */
   virtual std::string getCardsDescription(bool verbose = true) const;

 protected:
   std::vector<std::shared_ptr<Card>> cards; ///< Collection Card vector
};

#endif // CARD_COLLECTION_H
