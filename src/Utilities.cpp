#include "../include/Utilities.hpp"

int Max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int Min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

std::string to_lower(std::string in) {
    std::string result = "";

    for (char c : in) {
        result += std::tolower(c);
    }

    return result;
}

std::string to_upper(std::string in) {
    std::string result = "";

    for (char c : in) {
        result += std::toupper(c);
    }

    return result;
}
