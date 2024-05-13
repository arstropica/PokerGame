/**
 * @file src/PokerGame.cpp
 * @brief Implementation of the Poker game class.
 */

#include "PokerGame.h"
#include "../utils/Logger.h"
#include "game/PokerEngine.h"
#include "game/player/AIPokerPlayer.h"
#include "game/player/HumanPokerPlayer.h"
#include "game/resources/PokerHand.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
using PokerPlayerPtr = shared_ptr<PokerPlayer>;
using EnginePtr = shared_ptr<PokerEngine>;

PokerGame::PokerGame() : gameEngine(make_shared<PokerEngine>()) {}

PokerGame::PokerGame(EnginePtr engine) : gameEngine(engine) {}

void PokerGame::run()
{
   initialize();
   setupPlayers();
   gameEngine->startGame();
   displayResults();
}

void PokerGame::initialize()
{
   Logger::console("Welcome to the 5-Card Draw Poker Game!");
   Logger::console(
       "Enter a value for the ante or use the default [" +
           PokerEngine::formatCurrency(PokerEngine::DEFAULT_ANTE) + "]: ",
       false
   );

   double ante;
   string input;
   getline(cin, input);
   std::cout << std::endl;
   Logger::debug("Ante input: " + input);

   if (input.empty()) {
      ante = PokerEngine::DEFAULT_ANTE;
   } else {
      try {
         ante = stod(input);
      } catch (const invalid_argument &e) {
         Logger::debug("Invalid ante input detected.");
         Logger::trace(e.what());
         Logger::console("Invalid input. Using default ante.");
         ante = PokerEngine::DEFAULT_ANTE;
      }
   }
   Logger::console("Ante set to: " + PokerEngine::formatCurrency(ante));
   Logger::console("");
   gameEngine->setAnte(ante);
}

int PokerGame::promptStrategy()
{
   Logger::console("Choose an AI Strategy:");
   Logger::console("1: Conservative, 2: Balanced, 3: Aggressive, [4]: Random");

   string input;
   getline(cin, input);
   Logger::debug("User AI Strategy input: " + input);

   int strategy;
   if (input == "1") {
      strategy = (int)AIPokerPlayer::Strategy::CONSERVATIVE;
      Logger::console("You selected Conservative strategy.");
   } else if (input == "2") {
      strategy = (int)AIPokerPlayer::Strategy::BALANCED;
      Logger::console("You selected Balanced strategy.");
   } else if (input == "3") {
      strategy = (int)AIPokerPlayer::Strategy::AGGRESSIVE;
      Logger::console("You selected Aggressive strategy.");
   } else {
      strategy = 0;
      Logger::console("You selected Random strategy.");
   }
   Logger::console("");
   return strategy;
}

void PokerGame::setupPlayers()
{
   int n = 0;
   using AIS = AIPokerPlayer::Strategy;
   int sValues[] = {AIS::CONSERVATIVE, AIS::BALANCED, AIS::AGGRESSIVE};
   map<int, string> sNames = {
       {AIS::CONSERVATIVE, "Conservative"},
       {AIS::BALANCED, "Balanced"},
       {AIS::AGGRESSIVE, "Aggressive"}
   };
   AIPokerPlayer::Strategy strategy;
   int s = promptStrategy();

   Logger::console("Choose at least two players.");

   while (n < 7) {
      if (n >= 2) {
         Logger::console(
             "\nAdd a [H]uman or [A]I player, or press [Enter] to stop: ",
             false
         );
      } else {
         Logger::console("Add a [H]uman or [A]I player: ", false);
      }

      string input;
      getline(cin, input);
      Logger::debug("New player input: " + input);

      if (input.empty() && n >= 2) {
         Logger::trace("Empty input detected. Stopping...");
         Logger::console("");
         break;
      }

      if (s == 0) {
         srand(time(0));
         strategy = static_cast<AIPokerPlayer::Strategy>(sValues[rand() % 3]);
      } else {
         strategy = static_cast<AIPokerPlayer::Strategy>(s);
      }

      if (input == "A" || input == "H") {
         n++;
         UserType playerType = (input == "A") ? UserType::AI : UserType::HUMAN;
         PokerPlayerPtr p;
         if (playerType == UserType::HUMAN) {
            p = make_shared<HumanPokerPlayer>(gameEngine, n, 100.0);
         } else {
            Logger::trace("Selecting AI strategy: " + sNames[strategy] + ".");
            p = make_shared<AIPokerPlayer>(gameEngine, n, 100.0, strategy);
         }
         gameEngine->addPlayer(p);
         Logger::console(p->getName() + " added.");
         Logger::console("");
      }
   }
}

void PokerGame::displayResults()
{
   gameEngine->endGame(true);
}
