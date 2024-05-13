/**
 * @file src/game/PokerEngine.cpp
 * @brief Implementation of the PokerEngine class.
 */

#include "PokerEngine.h"
#include "../../utils/Logger.h"
#include "player/PokerPlayer.h"
#include "resources/CardCollection.h"
#include "resources/Deck.h"
#include "resources/PokerHand.h"
#include <climits>
#include <functional>
#include <iomanip>
#include <map>
#include <sstream>

using namespace std;
using PlayerList = vector<shared_ptr<PokerPlayer>>;
using PokerPlayerPtr = shared_ptr<PokerPlayer>;
using PokerHandPtr = shared_ptr<PokerHand>;

// Static Functions
string PokerEngine::formatCurrency(double amount)
{
   stringstream ss;
   ss << fixed << setprecision(2);
   ss << "$" << amount;
   return ss.str();
}

string PokerEngine::getCategoryDescription(PokerHand::Category category)
{
   return PokerHand::HAND_NAMES.at(category);
}

// Constructors
PokerEngine::PokerEngine()
    : deck(make_shared<Deck>()), discards(make_shared<Deck>(true)),
      players(PlayerList()), ante(DEFAULT_ANTE), pot(0.0),
      currentPlayerIndex(-1)
{}

PokerEngine::PokerEngine(double ante)
    : deck(make_shared<Deck>()), discards(make_shared<Deck>(true)),
      players(PlayerList()), ante(ante), pot(0.0), currentPlayerIndex(-1)
{}

PokerEngine::PokerEngine(shared_ptr<Deck> deck)
    : deck(deck), discards(make_shared<Deck>(true)), players(PlayerList()),
      ante(DEFAULT_ANTE), pot(0.0), currentPlayerIndex(-1)
{}

// Game Phases
void PokerEngine::startGame()
{
   Logger::debug("Starting Game...");
   anteUp();
   dealCards();
   Logger::debug("Starting game loop...");
   while (currentRound < 2) {
      advanceRound();
      bettingRound();
      if (currentRound == 1) {
         drawingRound();
      }
   }
}

multimap<long long, PokerPlayer::Outcome> PokerEngine::endGame(bool output)
{
   if (output) {
      auto winners = determineWinners();
      printResults(winners);
   }
   return showDown();
}

// Utility Functions
void PokerEngine::addPlayer(PokerPlayerPtr player)
{
   Logger::debug("Adding player: " + player->getName());
   players.push_back(player);
}

PokerPlayerPtr PokerEngine::getCurrentPlayer() const
{
   if (currentPlayerIndex >= 0 && currentPlayerIndex < players.size()) {
      return players.at(currentPlayerIndex);
   }
   return nullptr;
}

// Getters and Setters
double PokerEngine::getBlind() const
{
   return blind;
}

double PokerEngine::getPot() const
{
   return pot;
}

void PokerEngine::setAnte(double ante)
{
   Logger::debug("Setting ante to: " + formatCurrency(ante) + ".");
   this->ante = ante;
}

// Protected Functions
void PokerEngine::anteUp()
{
   Logger::console("Ante's Up!");
   Logger::console("");
   for (auto &player : players) {
      if (!player->bet(ante)) {
         player->setState(PokerPlayer::Status::FOLDED);
         Logger::debug(
             player->getName() +
             " has automatically folded due to insufficient funds to ante."
         );
      } else {
         Logger::debug(
             player->getName() + " has paid the ante of " +
             formatCurrency(ante) + "."
         );
      }
      pot += ante;
   }
   int nPlayers = getPlayersByState(PokerPlayer::Status::WAITING).size();
   Logger::debug(to_string(nPlayers) + " players have paid the ante.");
}

void PokerEngine::dealCards()
{
   PlayerList waiting = getPlayersByState(PokerPlayer::Status::WAITING);
   int perPlayer = 5;
   int nPlayers = waiting.size();
   Logger::debug("Deck size is: " + to_string(deck->size()));
   shuffleDeck();
   Logger::console("Dealing cards to " + to_string(nPlayers) + " players.");
   Logger::console("");
   for (int i = 0; i < perPlayer; ++i) {
      for (auto &player : waiting) {
         Card::ORIENTATION orientation = player->type == UserType::AI
                                             ? Card::ORIENTATION::FACE_DOWN
                                             : Card::ORIENTATION::FACE_UP;
         player->receive(CardCollection({deck->deal(orientation)}));
      }
   }
   for (auto &player : waiting) {
      player->setState(PokerPlayer::Status::ACTIVE);
   }
   Logger::debug(
       to_string(nPlayers) + " players were dealt " + to_string(perPlayer) +
       " cards each."
   );
   prompt("Press Enter to continue...");
}

void PokerEngine::bettingRound()
{
   for (int i = 0; i < players.size(); i++) {
      auto player = players.at(i);
      if (player->getState() == PokerPlayer::Status::ACTIVE) {
         handleBet(player);
         currentPlayerIndex = i;
         prompt("Press Enter to continue...");
      }
   }
   currentPlayerIndex = -1;
}

void PokerEngine::drawingRound()
{
   for (int i = 0; i < players.size(); i++) {
      auto player = players.at(i);
      if (player->getState() != PokerPlayer::Status::FOLDED) {
         handleDraw(player);
         currentPlayerIndex = i;
         prompt("Press Enter to continue...");
      }
   }
   currentPlayerIndex = -1;
}

void PokerEngine::advanceRound()
{
   Logger::console("");
   Logger::console("==============================");
   Logger::console("New Round Starting...");
   Logger::console("The pot is now: " + formatCurrency(pot) + ".");
   Logger::console("==============================");
   Logger::console("");

   PlayerList inactivePlayers = getPlayersByState(PokerPlayer::Status::FOLDED);
   if ((players.size() - inactivePlayers.size()) > 0) {
      for (auto &player : players) {
         if (player->getState() != PokerPlayer::Status::FOLDED) {
            player->setState(PokerPlayer::Status::ACTIVE);
         }
      }
   }
   currentRound++;
}

multimap<long long, PokerPlayer::Outcome> PokerEngine::showDown()
{
   multimap<long long, PokerPlayer::Outcome> outcomes;
   for (auto &player : players) {
      auto outcome = player->show();
      outcomes.insert({outcome.playerHand->getScore(), outcome});
   }
   return outcomes;
}

int PokerEngine::getCurrentRound() const
{
   return currentRound;
}

void PokerEngine::prompt(string message)
{
   string confirmation;
   Logger::console(message, false);
   getline(cin, confirmation);
   Logger::debug("User input: " + confirmation);
   Logger::console("");
}

// Private Functions
void PokerEngine::handleDraw(PokerPlayerPtr player)
{
   if (player->getState() != PokerPlayer::Status::FOLDED) {
      Card::ORIENTATION orientation = player->type == UserType::AI
                                          ? Card::ORIENTATION::FACE_DOWN
                                          : Card::ORIENTATION::FACE_UP;
      auto discardIdxs = player->discard();
      if (!discardIdxs.empty()) {
         auto replacements = CardCollection();
         for (auto &idx : discardIdxs) {
            replacements.add(deck->deal(orientation));
         }
         auto discarded = player->replace(discardIdxs, replacements);
         for (int i = 0; i < discarded.size(); i++) {
            discards->add(discarded.get(i));
         }
         Logger::trace(
             "Added " + to_string(discarded.size()) + " cards to discard deck."
         );
         Logger::debug(
             player->getName() + " discarded " + to_string(discardIdxs.size()) +
             " cards."
         );
         Logger::debug(
             player->getName() + " received the following " +
             to_string(discardIdxs.size()) +
             " new cards: " + replacements.getCardsDescription() + "."
         );
         Logger::console(
             player->getName() + " drew " + to_string(discardIdxs.size()) +
             " card(s)."
         );
         Logger::console("");

         if (deck->size() <= 5) {
            Logger::trace("Deck is running low, returning discards.");
            recycleDiscards();
         }
      } else {
         Logger::console(player->getName() + " stands pat.");
      }
      player->setState(PokerPlayer::Status::DRAWING);
   }
}

void PokerEngine::handleBet(PokerPlayerPtr player)
{
   if (player->getState() == PokerPlayer::Status::ACTIVE) {
      double b = player->bet();
      Logger::debug(
          "Engine received bet: " + formatCurrency(b) + " from " +
          player->getName() + "."
      );
      pot += b;
      if (b > blind) {
         Logger::debug("Setting new blind to: " + formatCurrency(b));
         Logger::console("The minimum bet is now: " + formatCurrency(b) + "!");
         Logger::console("");
         blind = max(blind, b);
      }
   } else {
      Logger::debug(player->getName() + " is not an active player.");
   }
}

multimap<int, PokerPlayer::Outcome> PokerEngine::determineWinners()
{
   long long maxScore = LLONG_MIN;
   int winnerIdx, tieWinnerIdx = -1;
   string maxCategory;
   string winner;
   string tieWinner;
   vector<PokerPlayer::Outcome> outcomes;
   multimap<int, PokerPlayer::Outcome> winners;

   for (int i = 0; i < players.size(); i++) {
      auto player = players.at(i);
      const auto &outcome = player->show();
      const PokerHandPtr &hand = outcome.playerHand;
      long long handScore = hand->getScore();
      string handDescription = hand->getDescription();
      outcomes.push_back(outcome);
      if (handScore > maxScore) {
         maxScore = handScore;
         maxCategory = handDescription;
         winner = player->getName();
         winnerIdx = i;
      } else if (handScore == maxScore) {
         tieWinner = player->getName();
         tieWinnerIdx = i;
      }
      Logger::trace("current maxScore: " + to_string(maxScore));
      Logger::trace("current maxCategory: " + maxCategory);
      Logger::trace("current winner: " + winner);
      Logger::trace("current winnerIdx: " + to_string(winnerIdx));
      if (tieWinnerIdx >= 0) {
         Logger::trace("current tieWinner: " + tieWinner);
         Logger::trace("current tieWinnerIdx: " + to_string(tieWinnerIdx));
      }
      i++;
   }

   winners.emplace(winnerIdx, outcomes.at(winnerIdx));
   if (tieWinnerIdx >= 0) {
      winners.emplace(tieWinnerIdx, outcomes.at(tieWinnerIdx));
   }
   return winners;
}

void PokerEngine::printResults(multimap<int, PokerPlayer::Outcome> winners)
{
   multimap<long long, ostringstream, std::greater<long long>> ss;

   Logger::console("");
   Logger::console("==============================");
   Logger::console("Showdown:");
   Logger::console("==============================");
   Logger::console("");

   if (winners.empty()) {
      Logger::console("No winners found.");
      return;
   }

   ss.emplace(
       LONG_LONG_MAX,
       ostringstream() << left << setw(20) << "Name" << setw(10) << "Balance"
                       << setw(20) << "Hand Type" << setw(25) << "Hand Score"
                       << setw(50) << "Cards"
   );

   int winnerIdx = winners.begin()->first;
   int tieIdx = winners.size() > 1 ? (++winners.begin())->first : -1;
   string winner = players.at(winnerIdx)->getName();
   string tieWinner = tieIdx >= 0 ? players.at(tieIdx)->getName() : "";
   string maxCategory = winners.begin()->second.playerHand->getDescription();
   for (int i = 0; i < players.size(); i++) {
      auto player = players.at(i);
      const auto &outcome = player->show();
      const shared_ptr<PokerHand> &hand = outcome.playerHand;

      long long handScore = hand->getScore();
      int balance = outcome.playerBalance;
      string handDescription = hand->getDescription();
      vector<string> names = hand->getCardNames();
      string handDetail = hand->getCardsDescription();

      if (tieIdx >= 0) {
         if (tieIdx == i || winnerIdx == i) {
            balance = balance + (pot / 2);
         }
      } else if (winnerIdx == i) {
         balance = balance + pot;
      }
      string cBalance = PokerEngine::formatCurrency(balance);

      ss.emplace(
          handScore,
          ostringstream() << left << setw(20) << outcome.playerName << setw(10)
                          << cBalance << setw(20) << handDescription << setw(25)
                          << handScore << setw(50) << handDetail
      );
   }
   for (auto &s : ss) {
      Logger::console(s.second.str());
   }
   Logger::console("");

   string cPot = PokerEngine::formatCurrency(pot);
   if (tieIdx >= 0) {
      Logger::console(
          "Winners are: " + winner + " and " + tieWinner + " with " +
          maxCategory
      );
   } else {
      Logger::console("Winner is: " + winner + " with " + maxCategory);
   }
   Logger::console("Winning Pot is: " + cPot);
}

PlayerList PokerEngine::getPlayersByState(PokerPlayer::Status state) const
{
   PlayerList result;
   for (const auto &player : players) {
      if (player->getState() == state) {
         result.push_back(player);
      }
   }
   return result;
}

void PokerEngine::shuffleDeck()
{
   Logger::info("Shuffling " + to_string(deck->size()) + " card deck...\n");
   deck->shuffle();
}

void PokerEngine::recycleDiscards()
{
   Logger::debug("Recycling " + to_string(discards->size()) + " discards.");
   for (int i = 0; i < discards->size(); i++) {
      deck->add(discards->get(i));
      discards->remove(discards->get(i));
   }
   shuffleDeck();
}
