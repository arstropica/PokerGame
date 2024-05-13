/**
 * @file Experiments/PokerDemo.cpp
 * @brief Executes the Hand comparison.
 * @details Part of Module 12: Experiments.
 */

#include "../Assignment/src/PokerGame.h"
#include "../Assignment/utils/Logger.h"
#include <spdlog/spdlog.h>

/**
 * @brief The main entry point of the PokerHandTest demo application.
 * @return Returns 0 upon successful execution.
 */
int main()
{
   // Set the Logger to debug mode.
   Logger::set_level(spdlog::level::trace);

   PokerGame game;
   game.run();

   return 0;
}
