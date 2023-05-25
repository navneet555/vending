#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>
#include "Node.h"

class Helper
{
private:
    Helper();

public:

    /**
     * @brief Check whether the given string is an integer or a float 
     * 
     * @param s The given string
     * @return true if the string is an integer or a float 
     * @return false if the string is neither an integer nor a float 
     */
    static bool isNumber(std::string s);

    /**
     * @brief Split the given string given a delimeter. For instance, given the string "1,2,3" and the delimeter ",", 
     *        This string will be splited into "1","2","3", and they will be put into the vector.  
     * 
     * @param s The given string
     * @param tokens The vector containing the results
     * @param delimeter the string based on which splitting is performed
     */
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    /**
     * @brief Read the user input (a line) from keyboard
     * 
     * @return the user input.
     */
    static std::string readInput();

    static void printInvalidInput();

    static bool isProbability(double p); //////

    static bool checkUserInputForRemoveItem(std::string userInput);

    static bool isValidDenom(std::string userInput);

    static std::string strip_spaces(std::string string);

    // Reference 
    //chatGPT with prompt: want it so that if the user types 200 I return the value $2.00 in c++
    static std::string convert_cents_to_dollars(std::string userInput);

    static void cancelAddTask();

    static void printLongInput();

    static std::vector<std::string> createVector(std::string id, std::string name, std::string desc, std::string price);

    static void printInvalidPrice();

    static void printCentsNotMultipleOf5();

    static void printInputNotNumber();
};
#endif