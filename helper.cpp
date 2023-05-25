#include "helper.h"
#include <regex>

using std::cin;
using std::string;
using std::vector;

#include <iomanip>


Helper::Helper() {}

void Helper::printInvalidInput()
{
    std::cout << "Error: menu item selected is not valid.\n";
}

bool Helper::isNumber(string s)
{
    string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;

    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    while (it != s.end())
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots > 1)
            {
                break;
            }
        }
        else if (!isdigit(*it))
        {
            break;
        }

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

void Helper::splitString(string s, vector<string> &tokens, string delimeter)
{
    tokens.clear();
    char *_s = new char[s.length() + 1];
    strcpy(_s, s.c_str());

    char *pch;
    pch = strtok(_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok(NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;

    if (!std::getline(std::cin, input))
    {
        std::cout << "End-of-file condition encountered, terminating the program" << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    input = strip_spaces(input);

    std::cout << std::endl;

    return input;
}

bool Helper::checkUserInputForRemoveItem(string userInput)
{
    std::regex pattern("^I\\d{4}$");

    while (userInput == "")
    {
        std::cout << "Please input a valid answer" << std::endl;
        userInput = Helper::readInput();
    }
    // Matching regex and is not eof
    if (std::regex_match(userInput, pattern) && !cin.eof())
    {
        // linked_list->remove_index(3);
        return true;
    }
    else
    {
        std::cout << "ID invalid or was not found" << std::endl;
    }

    return false;
}

string Helper::strip_spaces(string string)
{
    string.erase(std::remove_if(string.begin(), string.end(), isspace), string.end());

    return string;
}

bool Helper::isValidDenom(std::string userInput)
{
    int userInput_int = stoi(userInput);
    bool valid_denom = false;

    if (userInput_int == 10)
    {
        valid_denom = true;
    }
    else if (userInput_int == 20)
    {
        valid_denom = true;
    }
    else if (userInput_int == 50)
    {
        valid_denom = true;
    }
    else if (userInput_int == 100)
    {
        valid_denom = true;
    }
    else if (userInput_int == 200)
    {
        valid_denom = true;
    }
    else if (userInput_int == 500)
    {
        valid_denom = true;
    }
    else if (userInput_int == 1000)
    {
        valid_denom = true;
    }
    else
    {
        valid_denom = false;
    }

    return valid_denom;
}
std::string Helper::convert_cents_to_dollars(std::string userInput)
{
    int cents = stoi(userInput);

    int dollars = cents / 100;
    int cents_remaining = cents % 100;

    std::ostringstream formatted;
    formatted << "$" << dollars << "." << std::setfill('0') << std::setw(2) << cents_remaining;
    return formatted.str();
}

void Helper::cancelAddTask()
{
    std::cout << "Cancelling \"add item\" at user's request.\n"; 
    std::cout << "The task Add Item failed to run successfully.\n";
}

void Helper::printLongInput()
{
    std::cout << "Error: line entered was too long. Please try again.\n";
}

vector<string> Helper::createVector(string id, string name, string desc, string price) {
    vector<string> data = {};
    data.push_back(id);
    data.push_back(name);
    data.push_back(desc);
    data.push_back(price);
    data.push_back(std::to_string(DEFAULT_STOCK_LEVEL));
    return data;
}

void Helper::printInvalidPrice()
{
    std::cout << "Error: the price is not valid.\n";
}

void Helper::printCentsNotMultipleOf5()
{
    std::cout << "Error: the cents need to be a multiple of 5.\n";
}

void Helper::printInputNotNumber() {
    std::cout << "Error: input was not a number. Please try again.\n";
}