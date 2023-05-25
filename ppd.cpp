#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "helper.h"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>
#include <map>
#include <regex>
#include "CashRegister.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

const string menuText =
    "\nMain Menu\n"
    "        1. Display Items\n"
    "        2. Purchase Items\n"
    "        3. Save and Exit\n"
    "Administrator-Only Menu:\n"
    "        4. Add Item\n"
    "        5. Remove Item\n"
    "        6. Display Coins\n"
    "        7. Reset Stock\n"
    "        8. Reset Coins\n"
    "        9. Abort Program";
;

int main(int argc, char **argv)
{
    CashRegister *cash_register = new CashRegister();
    LinkedList *linked_list = new LinkedList();

    // Needs to check if there are exactly 3 lines of code or error
    if (argc != 3)
    {
        return EXIT_FAILURE;
    }
    if (argc == 3)
    {

        std::ifstream file1(argv[1]);
        if (!file1)
        {
            std::cerr << "Failed to open stock file" << endl;
            return EXIT_FAILURE;
        }

        string line;
        while (std::getline(file1, line))
        {

            bool file_error = false;
            vector<string> tokens = {};
            Helper::splitString(line, tokens, "|");

            if (tokens.size() == 5)
            {
                file_error = !linked_list->insert(tokens);
            }
            else
            {
                file_error = true;
            }

            if (file_error)
            {
                cout << "File error" << endl;
                return EXIT_FAILURE;
            }
        }

        std::ifstream file2(argv[2]);
        if (!file2)
        {
            std::cerr << "Failed to open coin file" << endl;
            return EXIT_FAILURE;
        }

        cash_register->LoadRegister(argv[2]);
    }
    
    bool quitProgram = false;
    while (!quitProgram)
    {
        cout << menuText << endl;
        cout << "\nSelect your option (1-9): ";
        vector<string> tokens = {};
        string input = Helper::readInput();
        Helper::splitString(input, tokens, " ");

          // if user hits enter on empty line, quit program without saving
        if (tokens.size() == 0) {
            quitProgram = true;
        }

        else if (tokens.size() == 1 && tokens[0] == "1")
        {
            linked_list->DisplayItems();
        }
        else if (tokens.size() == 1 && tokens[0] == "2")
        {
            // Purchasing
            cout << "Purchase Item" << endl;
            cout << "-------------" << endl;
            cout << "Please enter the id of the item you wish to purchase: ";

            string userInput = Helper::readInput();

            linked_list->BuyItem(userInput, *cash_register);
        }
        else if (tokens.size() == 1 && tokens[0] == "3")
        {
            linked_list->saveStock(argv[1]);
            cash_register->saveRegister(argv[2]);
            quitProgram = true;
        }
        else if (tokens.size() == 1 && tokens[0] == "4")
        {
            linked_list->addStock(linked_list);
        }
        else if (tokens.size() == 1 && tokens[0] == "5")
        {
            cout << "Please select the item you want to remove" << endl;

            string userInput = Helper::readInput();

            if (!cin.eof())
            {
                if (Helper::checkUserInputForRemoveItem(userInput))
                {
                    linked_list->remove_index(userInput);
                }
            }
        }
        else if (tokens.size() == 1 && tokens[0] == "6")
        {
            cash_register->display_coins();
        }

        else if (tokens.size() == 1 && tokens[0] == "7") {
            linked_list->resetStock();
            cout << "All stock has been reset to the default level of "
            << DEFAULT_STOCK_LEVEL;
        }

        else if (tokens.size() == 1 && tokens[0] == "8") {
            cash_register->resetCoin();
        }

        else if (tokens.size() == 1 && tokens[0] == "9") {
            // quit program without saving
            quitProgram = true;
        }
        else {
            if (tokens.size() >= 2 || Helper::isNumber(tokens[0]) == false) {
                Helper::printInputNotNumber();
            } else {
                Helper::printInvalidInput();
            }
        }
    }

    delete linked_list;
    linked_list = nullptr;

    return EXIT_SUCCESS;
}
