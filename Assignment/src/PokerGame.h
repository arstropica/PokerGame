/**
 * @file src/PokerGame.h
 * @brief Defines the control class for a game of 5-card draw poker.
 */
#ifndef POKERGAME_H
#define POKERGAME_H

#include <memory>
#include <string>

class PokerEngine; ///< Forward declaration of PokerEngine class

/**
 * @class PokerGame
 * @brief Manages a session of 5-card draw poker, interfacing with users and the
 * engine.
 */
class PokerGame
{
 public:
   /**
    * @brief Default Constructor for PokerGame.
    */
   PokerGame();

   /**
    * @brief Overleaded Constructor with PokerEngine.
    * @param engine The poker engine instance pointer.
    */
   PokerGame(std::shared_ptr<PokerEngine> engine);

   /**
    * @brief Runs the poker game.
    */
   virtual void run();

 protected:
   /**
    * @brief Performs any startup actions for the game.
    */
   virtual void initialize();

   /**
    * @brief Prompts the user for the AI Strategy.
    * @return The selected AI strategy.
    */
   virtual int promptStrategy();

   /**
    * @brief Sets up the players by asking the user for player details.
    */
   virtual void setupPlayers();

   /**
    * @brief Displays the results of the game and declares a winner.
    */
   virtual void displayResults();

 protected:
   std::shared_ptr<PokerEngine> gameEngine; ///< The poker game engine pointer.
};

#endif // POKERGAME_H