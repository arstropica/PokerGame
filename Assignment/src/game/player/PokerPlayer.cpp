/**
 * @file src/player/PokerPlayer.cpp
 * @brief Implementation of the PokerPlayer class.
 */

#include "PokerPlayer.h"
#include "../../../utils/Logger.h"
#include "../PokerEngine.h"
#include "../resources/Card.h"
#include "../resources/CardCollection.h"
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
using EnginePtr = shared_ptr<PokerEngine>;

PokerPlayer::PokerPlayer(
    EnginePtr engine, int id, UserType type, double startBal
)
    : engine(engine), id(id), type(type), balance(startBal), state(WAITING),
      hand(make_shared<PokerHand>())
{}

void PokerPlayer::receive(CardCollection cards)
{
   Logger::debug(getName() + " receives: " + cards.getCardsDescription());
   for (int i = 0; i < cards.size(); i++) {
      hand->add(cards.get(i));
   }
   if (hand->isValid() && type == UserType::HUMAN) {
      if (state == ACTIVE) {
         Logger::console(
             string("You have received ") + to_string(cards.size()) +
             " new card(s)."
         );
      }
      Logger::console("Your new hand is: ", false);
      Logger::console(hand->getCardsDescription());
      Logger::console("You have a " + hand->getDescription() + ".");
      Logger::console("");
   }
}

CardCollection PokerPlayer::replace(vector<int> idxs, CardCollection &cards)
{
   auto discards = CardCollection();
   std::sort(idxs.begin(), idxs.end(), greater<int>()); ///< desc sort
   for (const auto &idx : idxs) {
      auto card = hand->get(idx);
      if (card != nullptr) {
         Logger::debug(getName() + " discards: " + card->getName(true));
         hand->remove(card);
         discards.add(card);
      }
   }

   receive(cards);
   return discards;
}

bool PokerPlayer::bet(double amount)
{
   if (amount > balance) {
      Logger::debug(
          getName() + " does not have enough balance to bet " +
          PokerEngine::formatCurrency(amount) + "!"
      );
      return false;
   }

   balance -= amount;
   return true;
}

void PokerPlayer::raise(double amount)
{
   state = RAISING;
   double blind = engine->getBlind();
   string cAmount = PokerEngine::formatCurrency(amount - blind);
   Logger::debug(getName() + " raises with: " + hand->getDescription() + ".");
   Logger::console(getName() + " raises by: " + cAmount + "!");
   Logger::console("");
}

void PokerPlayer::call(double amount)
{
   state = CALLING;
   string cAmount = PokerEngine::formatCurrency(amount);
   Logger::debug(getName() + " calls with: " + hand->getDescription() + ".");
   Logger::console(getName() + " calls with: " + cAmount + "!");
   Logger::console("");
}

void PokerPlayer::allIn(double amount)
{
   state = ALLIN;
   string cAmount = PokerEngine::formatCurrency(amount);
   Logger::debug(getName() + " all in with: " + hand->getDescription() + "!");
   Logger::console(getName() + " goes all in with: " + cAmount + "!");
   Logger::console("");
}

void PokerPlayer::fold()
{
   state = FOLDED;
   Logger::debug(getName() + " folds with: " + hand->getDescription() + "!");
   Logger::console(getName() + " folds!");
   Logger::console("");
}

PokerPlayer::Outcome PokerPlayer::show() const
{
   return Outcome(getName(), balance, hand);
}

PokerPlayer::Status PokerPlayer::getState() const
{
   return state;
}

void PokerPlayer::setState(Status state)
{
   this->state = state;
}

string PokerPlayer::getName() const
{
   string playerType = type == UserType::AI ? "AI" : "Human";
   return playerType + " Player (" + to_string(id) + ")";
}
