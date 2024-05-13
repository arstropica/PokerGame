/**
 * @file src/player/HumanPokerPlayer.cpp
 * @brief Implementation of the derived HumanPokerPlayer class.
 */

#include "HumanPokerPlayer.h"
#include "../../../utils/Logger.h"
#include "../PokerEngine.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;
using EnginePtr = shared_ptr<PokerEngine>;

HumanPokerPlayer::HumanPokerPlayer(EnginePtr engine, int id, double balance)
    : PokerPlayer(engine, id, UserType::HUMAN, balance)
{}

vector<int> HumanPokerPlayer::discard()
{
   string input, test, confirmation;
   vector<int> discards;
   bool validInput = false;
   vector<string> names = hand->getCardNames();
   string handDetail = hand->getCardsDescription(true);

   Logger::console("Your current hand is: " + hand->getDescription());
   Logger::console(handDetail);
   if (prompt("Do you want to discard any cards?")) {
      while (!validInput) {
         input = "", test = "", confirmation = "";
         Logger::console(
             "Enter the indices of your card replacements (space separated): ",
             false
         );
         getline(cin, input);
         Logger::debug("User input: " + input);

         // No input means no discards
         if (input.empty()) {
            Logger::console("Skipping Draw. No cards were selected.");
         } else {
            // Check that the input consists only of digits and spaces
            validInput = true;
            istringstream iss(input);
            while (iss >> test) {
               if (!all_of(test.begin(), test.end(), ::isdigit)) {
                  validInput = false;
                  Logger::console(
                      "Invalid. Enter only space-separated integers."
                  );
                  break;
               }
            }
         }

         // If input is valid, convert to integers and validate indices
         if (validInput) {
            istringstream validIss(input);
            int i;
            while (validIss >> i) {
               if (i < 0 || i >= hand->size()) {
                  Logger::console(
                      "Card Index: " + to_string(i) + " is invalid. " +
                      "Try again."
                  );
                  validInput = false; // Reset
                  discards.clear();
                  break;
               }
               discards.push_back(i);
            }
         }

         // Confirm discards with the user
         if (!discards.empty()) {
            Logger::console(
                "You are about to discard the following cards: | ",
                false
            );
            for (int index : discards) {
               Logger::console(hand->get(index)->getName(true) + " | ", false);
            }
            Logger::console("");
         } else if (validInput) {
            Logger::console("You have chosen to keep all of your cards.");
         }
         if (prompt("Are you sure?")) {
            break;
         } else {
            Logger::console("Action cancelled.");
            discards.clear(); // Empty the vector if user cancels
            validInput = false;
         }
      }
   }
   if (discards.size() > 0) {
      string dbg = "You are discarding cards at index: ";
      for (int index : discards) {
         dbg += to_string(index) + " ";
      }
      Logger::debug(dbg);
   } else {
      Logger::debug("You are keeping all of your cards.");
   }

   return discards;
}

double HumanPokerPlayer::bet()
{
   double amount = 0;
   double blind = engine->getBlind();
   string decision, message;
   string cBlind = PokerEngine::formatCurrency(blind);
   string cAmount = PokerEngine::formatCurrency(amount);
   string cBalance = PokerEngine::formatCurrency(balance);
   char choice;
   if (balance < blind) {
      if (prompt("You can't make the blind. Do you want to go all in?")) {
         amount = balance;
         allIn(amount);
      }
   } else {
      Logger::console("Your current balance is: " + cBalance + ".");
      Logger::console("The blind bet is: " + cBlind + ".");

      do {
         Logger::console("Do you want to [R]aise, [C]all, or [F]old? ", false);
         getline(cin, decision);
         Logger::debug("User input: " + decision);
         choice = toupper(decision[0]);
         switch (choice) {
            case 'R':
               amount = captureBet();
               raise(amount);
               break;
            case 'C':
               amount = blind;
               call(amount);
               break;
            case 'F':
               fold();
               break;
            default:
               Logger::console("Invalid input. Please try again.");
               break;
         }
      } while (string("RCF").find(choice) == string::npos);
   }
   balance -= amount;
   return amount;
}

bool HumanPokerPlayer::prompt(string message)
{
   string confirmation;
   Logger::console(message + " [Y]/n: ", false);
   getline(cin, confirmation);
   Logger::debug("User input: " + confirmation);
   Logger::console("");
   if (toupper(confirmation[0]) == 'N') {
      return false;
   } else {
      return true;
   }
}

double HumanPokerPlayer::captureBet()
{
   double amount = 0;
   double blind = engine->getBlind();
   string decision, sAmount, cAmount;
   string cBlind = PokerEngine::formatCurrency(blind);
   string cBalance = PokerEngine::formatCurrency(balance);
   string tip = blind > 0 ? (" of at least " + cBlind) : "";

   while (true) {
      Logger::console("Enter an amount" + tip + ": ", false);
      getline(cin, sAmount);
      Logger::debug("User input: " + sAmount);
      if (!sAmount.empty()) {
         try {
            amount = stod(sAmount);
         } catch (const invalid_argument &e) {
            amount = 0;
            Logger::debug("Invalid bet input detected.");
            Logger::trace(e.what());
            Logger::console("Please re-enter a valid amount.");
            continue; // Ask for the input again
         }
      }

      // Check if the input is a valid number and does not exceed balance
      if (cin.fail() || (amount + 0.001) < blind) { // error margin
         Logger::console("Please re-enter a valid amount.");
         continue; // Ask for the input again
      } else {
         cAmount = PokerEngine::formatCurrency(amount);
         if (amount > balance) {
            Logger::console(
                "Insufficient balance. You have " + cBalance + " and bet " +
                cAmount + ". Please enter a smaller amount."
            );
            continue; // Ask for the input again
         } else {
            break; // Exit the loop
         }
      }
   }
   return amount;
}