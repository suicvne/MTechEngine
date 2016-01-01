/**
  About customalgorithms.h/CustomAlgorithms.cpp

  This file defines custom C++ algoirthms for use with the Standard Library.
  */

#ifndef CUSTOMALGORITHMS_H
#define CUSTOMALGORITHMS_H

#include <iostream>
#include <algorithm>
#include <string>
template<class TContainer>
bool begins_with(const TContainer& input, const TContainer& match)
{
    return input.size() >= match.size() && equal(match.begin(), match.end(), input.begin());
};

std::string toLower(std::string input)
{
    std::string _i = input;
    std::transform(_i.begin(), _i.end(), _i.begin(), ::tolower);
    return _i;
};

#endif // CUSTOMALGORITHMS_H
