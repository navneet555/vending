#include "CashRegister.h"
#include "LinkedList.h"
#include <iomanip>
#include <algorithm>

using std::cout;
CashRegister::CashRegister()
{
    // reference: https://stackoverflow.com/questions/22067705/c-vector-stdout-of-range-error i love u
    this->coins.resize(8);
}
CashRegister::~CashRegister()
{
    
}

void CashRegister::Load_file_coins(string filepath)
{
}

int CashRegister::coin_file_to_denomation(Denomination file_denom)
{
    int index = 0;

    if (file_denom == 10)
    {
        index = 1;
    }
    else if (file_denom == 20)
    {
        index = 2;
    }
    else if (file_denom == 50)
    {
        index = 3;
    }
    else if (file_denom == 100)
    {
        index = 4;
    }
    else if (file_denom == 200)
    {
        index = 5;
    }
    else if (file_denom == 500)
    {
        index = 6;
    }
    else if (file_denom == 1000)
    {
        index = 7;
    }

    return index;
}

bool CashRegister::LoadRegister(string file_name)
{
    std::ifstream coins_file(file_name);

    std::string line;
    vector<string> coins_output;

    if (!coins_file)
    {
        std::cout << file_name << " : "
                  << "failed to open file" << std::endl;
        return false;
    }

    while (std::getline(coins_file, line))
    {
        // Initialize the vector with the required number of elements
        std::vector<Coin *> ret(8);

        Helper::splitString(line, coins_output, ",");

        if (coins_output.size() >= 2)
        {
            // Getting the coins
            std::string coin_denom = coins_output[0];
            std::string coin_value = coins_output[1];

            // Checks if the denom and value are numbers
            if (Helper::isNumber(coin_value) && Helper::isNumber(coin_denom))
            {
                // the denom values are stripped of spaces
                coins_output[0] = Helper::strip_spaces(coins_output.at(0));

                // turns the values into enums for the denomination
                Denomination denomination = Coin::coin_file_to_denomation(stoi(coins_output.at(0)));

                // makes the index of the coins
                int index_coin = coin_file_to_denomation(denomination);

                // makes new coin (the denomination, the value)
                Coin *coin_ptr = new Coin(denomination, std::stoi(coins_output.at(1)));

                // this line sets the Coin object pointed to by coin_ptr to the index_coin-th position of the coins vector using the at() function
                this->coins.at(index_coin) = coin_ptr;

            }
            else
            {
                std::cout << coin_denom << " : "
                          << "nots a number" << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << line << " : "
                      << "coins_output.size()!=2" << std::endl;
            return false;
        }
    }

    
    return true;
}

// reference: chatgpt helped with this part
void CashRegister::display_coins()
{
    cout << "Coins Summary" << std::endl;
    cout << "---------------" << std::endl;
    cout << "Denomination     |     Count" << std::endl;
    cout << "-----------------------------" << std::endl;

    for (const auto &coin : this->coins)
    {
        string denom_str;
        if (coin->denom % 100 != 0)
        {
            denom_str = std::to_string(coin->denom) + " Cents";
        }
        else
        {
            denom_str = std::to_string(coin->denom / 100) + " Dollars";
        }

        cout << std::left << std::setw(18) << denom_str << "| " << std::right << std::setw(9) << coin->count << std::endl;
    }
}

int CashRegister::TotalMoney()
{
    int total_money = 0;

    for (Coin *coin : coins)
    {
        total_money += coin->denom * coin->count;
    }

    return total_money;
}

void CashRegister::RemoveCount(int index)
{
    for (size_t i = 0; i < coins.size(); ++i)
    {
        if (coins[i]->denom == index)
        {
            coins[i]->decrementCount();

        }
    }
}

bool CashRegister::GetChange(int change)
{
    bool can_do_payment = false;
    int total_money = 0;

    total_money = TotalMoney();

    if (total_money <= 0)
    {
        std::cout << "Can not do purchase, no money left in register" << std::endl;
        std::cout << "Your money will be returned and purchase will be canceled" << std::endl;
        can_do_payment = false;
    }
    else
    {
        // Getting valid denoms
        std::vector<int> valid_denoms;
        for (size_t i = 0; i < coins.size(); ++i)
        {
            if (coins[i]->count > 0 && coins[i]->denom > 0)
            {
                valid_denoms.push_back(coins[i]->denom);
            }
        }

        // Sorting them
        std::sort(valid_denoms.rbegin(), valid_denoms.rend());

        // Tries to get change the first time e.g 500 x 1
        std::vector<int> change_counts(valid_denoms.size(), 0);
        for (size_t i = 0; i < valid_denoms.size(); ++i)
        {
            while (change >= valid_denoms[i])
            {
                change -= valid_denoms[i];
                RemoveCount(valid_denoms[i]);

                change_counts[i]++;
            }
        }
        if (change > 0)
        {
            // Tries to get change the first time e.g 500 x 1   100 x 1
            for (size_t i = 0; i < valid_denoms.size(); ++i)
            {
                while (change >= valid_denoms[i])
                {
                    change -= valid_denoms[i];
                    RemoveCount(valid_denoms[i]);
                    change_counts[i]++;
                }
            }

            // If can't get change
            if (change > 0)
            {
                std::cout << "Cannot make exact change, returning your money" << std::endl;
                can_do_payment = false;
            }
            else
            {
                // Print the change
                std::cout << "Here is your change: " << std::endl;
                for (size_t i = 0; i < valid_denoms.size(); ++i)
                {
                    if (change_counts[i] > 0)
                    {
                        std::cout  << Helper::convert_cents_to_dollars(std::to_string(valid_denoms[i])) << " x " << change_counts[i] << std::endl;
                    }
                }

                can_do_payment = true;
            }
        }
        else
        {
            // Print the change
            std::cout << "Here is your change: " << std::endl;
            for (size_t i = 0; i < valid_denoms.size(); ++i)
            {
                if (change_counts[i] > 0)
                {
                    std::cout <<  Helper::convert_cents_to_dollars(std::to_string(valid_denoms[i])) << " x " << change_counts[i] << std::endl;
                }
            }

            can_do_payment = true;
        }
    }

    return can_do_payment;
}

void CashRegister::saveRegister(string coinFile)
{
    std::ofstream file;

     // open coin file
    file.open(coinFile);

    // for each coin, write the denominator and count to the file
    for (const auto &coin : this->coins)
    {
        file << coin->denom << "," << coin->count << std::endl;
    }

    // close file
    file.close();
}

void CashRegister::resetCoin()
{
    std::ofstream file;

    for (size_t i = 0; i < coins.size(); i++)
    {
        coins[i]->count = DEFAULT_COIN_COUNT;
    }

    std::cout << "All coins have been reset to the default level of " << DEFAULT_COIN_COUNT << std::endl;
}