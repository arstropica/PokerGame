/**
 * @file src/player/HumanPokerPlayer.h
 * @brief Defines the derived HumanPokerPlayer class.
 */
#ifndef HUMANPOKERPLAYER_H
#define HUMANPOKERPLAYER_H

#include "PokerPlayer.h"
#include <memory>
#include <string>
#include <vector>

class PokerEngine; ///< Forward declaration of PokerEngine class

/**
 * @class HumanPokerPlayer
 * @brief Represents a human poker player.
 *
 * The HumanPokerPlayer class is a derived class of the PokerPlayer class and
 * provides functionality to simulate a human poker player.
 */
class HumanPokerPlayer : public PokerPlayer
{
 public:
   /**
    * @brief Constructs a new HumanPokerPlayer object.
    *
    * @param engine The poker engine pointer.
    * @param id The player's ID.
    * @param balance The player's balance.
    */
   HumanPokerPlayer(
       std::shared_ptr<PokerEngine> engine, int id, double balance
   );

   /**
    * @brief Destructs the HumanPokerPlayer object.
    */
   ~HumanPokerPlayer() = default;

   /**
    * @see PokerPlayer::discard
    */
   std::vector<int> discard() override;

   /**
    * @see PokerPlayer::bet
    */
   double bet() override;

 protected:
   /**
    * @brief Prompts the player with a message.
    *
    * @param message
    * @return true if yes, otherwise false
    */
   virtual bool prompt(std::string message);

 private:
   /**
    * @brief Captures the player bet input.
    *
    * @return The amount to bet.
    */
   double captureBet();
};
#endif // HUMANPOKERPLAYER_H