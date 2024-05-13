/**
 * @file src/game/resources/Card.cpp
 * @brief Implementation of the Card class.
 */
#include "Card.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <unordered_map>

using namespace std;
using CardPtr = shared_ptr<Card>;

/**
 * @var Card::ranks
 * @brief Indexed card ranks.
 */
const vector<char> Card::ranks = {
    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'
};

/**
 * @var Card::suits
 * @brief Indexed card suits.
 */
const vector<char> Card::suits = {'C', 'D', 'H', 'S'};

/**
 * @var Card::legend
 * @brief Initialize readability map.
 */
const map<char, string> Card::legend = {
    {'2', "2"},
    {'3', "3"},
    {'4', "4"},
    {'5', "5"},
    {'6', "6"},
    {'7', "7"},
    {'8', "8"},
    {'9', "9"},
    {'T', "Ten"},
    {'J', "Jack"},
    {'Q', "Queen"},
    {'K', "King"},
    {'A', "Ace"},
    {'C', "Clubs"},
    {'D', "Diamonds"},
    {'H', "Hearts"},
    {'S', "Spades"}
};

/**
 * @brief Protected constructor for derived Card classes.
 */
Card::Card() : orientation(FACE_DOWN), rank(' '), suit(' ') {}

Card::Card(ORIENTATION orientation)
    : orientation(orientation), rank(' '), suit(' ')
{}

Card::Card(string token)
{
   rank = token.at(0);
   suit = token.at(1);
}

Card::Card(string token, ORIENTATION orientation) : Card(token)
{
   this->orientation = orientation;
}

bool Card::isValid() const
{
   return find(ranks.begin(), ranks.end(), rank) != ranks.end() &&
          find(suits.begin(), suits.end(), suit) != suits.end();
}

char Card::getSuit() const
{
   return suit;
}

char Card::getRank() const
{
   return rank;
}

int Card::getValue() const
{
   auto it = std::find(ranks.begin(), ranks.end(), rank);
   return (it != ranks.end()) ? distance(ranks.begin(), it) + 2 : -1;
}

string Card::getName(bool verbose) const
{
   if (verbose) {
      return legend.at(rank) + " of " + legend.at(suit);
   } else {
      return std::string(1, rank) + std::string(1, suit);
   }
}

Card::ORIENTATION Card::getOrientation() const
{
   return orientation;
}

Card::ORIENTATION Card::flip()
{
   orientation = orientation == FACE_UP ? FACE_DOWN : FACE_UP;
   return orientation;
}

weak_ordering Card::operator<=>(const CardPtr &other) const
{
   auto r = ranks;
   return distance(r.begin(), find(r.begin(), r.end(), rank)) <=>
          distance(r.begin(), find(r.begin(), r.end(), other->rank));
}

bool Card::operator==(const CardPtr &other) const
{
   auto r = ranks;
   return distance(r.begin(), find(r.begin(), r.end(), rank)) ==
          distance(r.begin(), find(r.begin(), r.end(), other->rank));
}
