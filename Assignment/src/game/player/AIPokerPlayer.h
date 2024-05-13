/**
 * @file src/player/AIPokerPlayer.h
 * @brief Defines the derived AIPokerPlayer class.
 */
#ifndef AIPOKERPLAYER_H
#define AIPOKERPLAYER_H

#include "PokerPlayer.h"
#include <memory>
#include <random>
#include <string>
#include <vector>

class PokerEngine; ///< Forward declaration of PokerEngine class

/**
 * @class AIPokerPlayer
 * @brief Represents an AI poker player.
 *
 * The AIPokerPlayer class is a derived class of the PokerPlayer class and
 * provides functionality to simulate a AI poker player.
 */
class AIPokerPlayer : public PokerPlayer
{
 public:
   /**
    * @brief Enumerates basic strategies for the AI player by percentage.
    */
   enum Strategy
   {
      AGGRESSIVE = 45,
      BALANCED = 20,
      CONSERVATIVE = 5
   };

   /**
    * @brief Constructs a new AIPokerPlayer object.
    *
    * @param engine The poker engine pointer.
    * @param id The player's ID.
    * @param balance The player's balance.
    */
   AIPokerPlayer(std::shared_ptr<PokerEngine> engine, int id, double balance);

   /**
    * @brief Constructs a new AIPokerPlayer object with strategy.
    *
    * @param engine The poker engine pointer.
    * @param id The player's ID.
    * @param balance The player's balance.
    * @param strategy The player's strategy.
    */
   AIPokerPlayer(
       std::shared_ptr<PokerEngine> engine, int id, double balance,
       Strategy strategy
   );

   /**
    * @brief Destructs the AIPokerPlayer object.
    */
   ~AIPokerPlayer() = default;

   /**
    * @see PokerPlayer::discard
    */
   std::vector<int> discard() override;

   /**
    * @see PokerPlayer::bet
    */
   double bet() override;

 protected:
   Strategy strategy; ///< Determines the AI player's strategy.
 private:
   static std::mt19937 rng; ///<  Mersenne Twister engine for randomness
};
#endif // AIPOKERPLAYER_H