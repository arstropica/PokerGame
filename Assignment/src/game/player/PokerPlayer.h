/**
 * @file src/player/PokerPlayer.h
 * @brief Defines an abstract base for Poker players.
 */
#ifndef POKERPLAYER_H
#define POKERPLAYER_H

#include <memory>
#include <string>
#include <vector>

class Card;           ///< Forward declaration of Card class
class CardCollection; ///< Forward declaration of CardCollection class
class PokerHand;      ///< Forward declaration of PokerHand class
class PokerEngine;    ///< Forward declaration of PokerEngine class

/**
 * @brief PokerPlayer User Type Enumeration
 */
enum UserType
{
   HUMAN,
   AI
};

/**
 * @class PokerPlayer
 * @brief Abstract base class representing a player in a poker game.
 *
 * Provides an common set of functionalities for all player actions in the game
 * to be implemented by derived human or AI player classes.
 */
class PokerPlayer
{
 public:
   struct Outcome
   {
      std::string playerName = "Unknown";
      double playerBalance;
      std::shared_ptr<PokerHand> playerHand;

      /**
       * @brief Default constructor for Outcome struct.
       */
      Outcome() : playerHand(), playerBalance(0) {}

      /**
       * @brief Constructor for Outcome struct.
       *
       * @param playerName The player name.
       * @param playerBalance The player's balance.
       * @param playerHand The player's hand.
       */
      Outcome(
          std::string playerName, double balance,
          std::shared_ptr<PokerHand> hand
      )
          : playerName(playerName), playerBalance(balance), playerHand(hand)
      {}
   };

   enum Status
   {
      WAITING,
      ACTIVE,
      ALLIN,
      CALLING,
      RAISING,
      DRAWING,
      FOLDED,
   };

   UserType type; ///< The type of player (human or AI).

   /**
    * @brief Constructor for PokerPlayer.
    *
    * @param engine The PokerEngine object pointer.
    * @param id The unique identifier for the player.
    * @param type The type of player (human or AI).
    * @param startBal The initial balance for the player.
    */
   PokerPlayer(
       std::shared_ptr<PokerEngine> engine, int id, UserType type,
       double startBal
   );

   /**
    * @brief Virtual destructor to ensure proper cleanup of derived classes.
    */
   virtual ~PokerPlayer() = default;

   /**
    * @brief Receives cards from the deck.
    *
    * @param cards CardCollection representing cards dealt to the player.
    */
   virtual void receive(CardCollection cards);

   /**
    * @brief Discards a subset of cards and receives new ones.
    *
    * @param idxs The indices of the cards to be discarded.
    * @param repts The new cards to replace the discarded ones.
    * @return CardCollection The discarded cards.
    */
   virtual CardCollection replace(std::vector<int> idxs, CardCollection &repts);

   /**
    * @brief Places a bet in the game.
    *
    * @param amount The amount of money to bet.
    * @return True if the bet was successful, false otherwise.
    */
   virtual bool bet(double amount);

   /**
    * @brief Performs a player-initiated bet in the game.
    *
    * @return The amount of money to bet.
    */
   virtual double bet() = 0;

   /**
    * @brief Raises the current bet in the game.
    * @param amount The amount to raise the bet by.
    */
   virtual void raise(double amount);

   /**
    * @brief Calls the current bet in the game.
    * @param amount The amount to call.
    */
   virtual void call(double amount);

   /**
    * @brief Player goes all-in.
    * @param amount The amount to go all-in with.
    */
   virtual void allIn(double amount);

   /**
    * @brief Withdraws from the game.
    */
   virtual void fold();

   /**
    * @brief Discards cards by index during a draw round in the poker game.
    *
    * This method should encapsulate the decision-making process for the
    * player's replacement strategy during their turn.
    * @return A vector of indices of the cards to be replaced.
    */
   virtual std::vector<int> discard() = 0;

   /**
    * @brief Returns the player's game outcome.
    *
    * @return Outcome.
    */
   virtual Outcome show() const;

   /**
    * @brief Returns the player's state.
    *
    * @return Status Player state.
    */
   virtual Status getState() const;

   /**
    * @brief Sets the player's state.
    *
    * @param state The new player state.
    */
   void setState(Status state);

   /**
    * @brief Returns the player's name.
    *
    * @return Player name.
    */
   virtual std::string getName() const;

 protected:
   std::shared_ptr<PokerHand> hand;     ///< The player's poker hand.
   std::shared_ptr<PokerEngine> engine; ///< The PokerEngine object pointer.
   double balance;                      ///< The player's current balance
   Status state;                        ///< The player's state.

 private:
   int id; ///< Unique identifier for the player.
};

#endif // POKERPLAYER_H
