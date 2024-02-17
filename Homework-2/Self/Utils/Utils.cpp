//
// Created by Alex Tran on 2/17/24.
//

#include "Utils.h"

std::string Utils::replaceSpacesWithUnderScore(const std::string& s) {
    std::string result = s;
    std::replace(result.begin(), result.end(), ' ', '_');
    return result;
}

std::string Utils::replaceUnderScoreWithSpaces(const std::string& s) {
    std::string result = s;
    std::replace(result.begin(), result.end(), '_', ' ');
    return result;
}