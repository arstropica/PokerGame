// utils/Utility.cpp
#include "Utility.h"
#include <cmath>

const double EPSILON = 1e-6;

bool isZero(double value)
{
   return value == 0.0;
}

bool isEqual(double value1, double value2)
{
   return std::fabs(value1 - value2) < EPSILON;
}

bool isEqual(double value1, double value2, double error)
{
   return std::fabs(value1 - value2) < error;
}