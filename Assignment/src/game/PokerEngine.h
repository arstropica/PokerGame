/**
 * @file src/game/PokerEngine.h
 * @brief Defines an engine that coordinates a game of 5-card draw poker.
 */
#ifndef ENGINE_H
#define ENGINE_H

#include "../../utils/Logger.h"
#include "player/PokerPlayer.h"
#include "resources/Deck.h"
#include "resources/PokerHand.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

/**
 * @class Engine
 * @brief Manages a 5-card draw poker game with multiple players.
 *
 * Coordinates the game logic including dealing, betting, and
 * determining winners.
 */
class PokerEngine
{
 public:
   static constexpr double DEFAULT_ANTE = 10.0; ///< Default ante value.

   /**
    * @brief Format double as currency.
    *
    * @param amount
    * @return std::string
    */
   static std::string formatCurrency(double amount);

   /**
    * @brief Constructor for the Engine.
    */
   PokerEngine();

   /**
    * @brief Construct a new Poker Engine object with an ante value.
    *
    * @param ante
    */
   PokerEngine(double ante);

   /**
    * @brief Construct a new Poker Engine object with a deck.
    *
    * @param std::shared_ptr<Deck> deck
    */
   PokerEngine(std::shared_ptr<Deck> deck);

   /**
    * @brief Destructor for the Engine.
    */
   ~PokerEngine() = default;

   /**
    * @brief Starts the poker game.
    *
    * Manages the game flow, including dealing, betting rounds, and showdown.
    */
   virtual void startGame();

   /**
    * @brief Returns a list of outcomes.
    * @param output Whether to output the results.
    */
   virtual std::multimap<long long, PokerPlayer::Outcome> endGame(bool output);

   /**
    * @brief Adds a player to the game.
    *
    * @param player A shared pointer to a PokerPlayer.
    */
   void addPlayer(std::shared_ptr<PokerPlayer> player);

   /**
    * @brief Returns a pointer to the active player.
    *
    * @return std::vector<std::shared_ptr<PokerPlayer>>
    */
   std::shared_ptr<PokerPlayer> getCurrentPlayer() const;

   /**
    * @brief Returns the big blind.
    *
    * @return The blind amount.
    */
   double getBlind() const;

   /**
    * @brief Returns the Pot.
    *
    * @param pot The pot amount.
    */
   double getPot() const;

   /**
    * @brief Sets the ante value for the game.
    *
    * @param ante The ante value.
    */
   void setAnte(double ante);

 protected:
   /**
    * @brief Pays the ante from each player into the pot.
    */
   void anteUp();

   /**
    * @brief Deals cards to each player.
    */
   virtual void dealCards();

   /**
    * @brief Executes a round of betting.
    */
   virtual void bettingRound();

   /**
    * @brief Manages the drawing phase where players can exchange cards.
    */
   virtual void drawingRound();

   /**
    * @brief Resets the game state for a new round.
    */
   virtual void advanceRound();

   /**
    * @brief Returns the showdown results.
    */
   virtual std::multimap<long long, PokerPlayer::Outcome> showDown();

   /**
    * @brief Get the current round.
    *
    * @return int
    */
   int getCurrentRound() const;

   /**
    * @brief Prompts the player with a message.
    *
    * @param message
    */
   virtual void prompt(std::string message);

 private:
   int currentPlayerIndex{-1};                        ///< Current player index.
   int currentRound{0};                               ///< Current round.
   double ante;                                       ///< Game ante.
   double pot;                                        ///< Game Pot.
   double blind;                                      ///< Game blind.
   std::vector<std::shared_ptr<PokerPlayer>> players; ///< Game players.
   std::shared_ptr<Deck> deck;                        ///< Game deck.
   std::shared_ptr<Deck> discards;                    ///< Discarded cards.

   /**
    * @brief Returns a string description of the given category.
    *
    * @return Category description.
    */
   static std::string getCategoryDescription(PokerHand::Category category);

   /**
    * @brief Handles the draw phase for a player.
    *
    * @param player The player to handle.
    */
   virtual void handleDraw(std::shared_ptr<PokerPlayer> player);

   /**
    * @brief Handles the bet phase for a player.
    *
    * @param player The player to handle.
    */
   virtual void handleBet(std::shared_ptr<PokerPlayer> player);

   /**
    * @brief Determines the winner(s) of the game.
    *
    * @return std::multimap<int index, PokerPlayer::Outcome>
    */
   std::multimap<int, PokerPlayer::Outcome> determineWinners();

   /**
    * @brief Prints the results of the game.
    *
    * @param winners The winners of the game.
    */
   void printResults(std::multimap<int, PokerPlayer::Outcome> winners);

   /**
    * @brief Returns a list of players with the given state.
    *
    * @param state The player state.
    * @return std::vector<std::shared_ptr<PokerPlayer>>
    */
   std::vector<std::shared_ptr<PokerPlayer>>
   getPlayersByState(PokerPlayer::Status state) const;

   /**
    * @brief Shuffles the deck of cards.
    */
   void shuffleDeck();

   /**
    * @brief Recycles discarded cards back into the deck.
    */
   void recycleDiscards();
};

#endif // ENGINE_H
