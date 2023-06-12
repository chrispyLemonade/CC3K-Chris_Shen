#ifndef COLOR_H 
#define COLOR_H 
#include <string>

// Use these for the colour version
const std::string YELLOW =  "\033[33m"; // treasure
const std::string GREEN = "\033[32m"; // gold
const std::string RED = "\u001b[31m"; // enemy
const std::string BLUE = "\u001b[34m"; // player

// Use this for both versions
const std::string RESET =  "\033[0m";
#endif
