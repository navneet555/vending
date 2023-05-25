#ifndef CASHREGISTER_H
#define CASHREGISTER_H
#include <string>
#include <iostream>
#include <fstream>
#include "helper.h"
#include "Coin.h"


using std::string;

class CashRegister{
    private:

        int denominators[8]   = {5,10,20,50,100,200,500,1000};
        int amounts[8]        = {0,0,0,0,0,0,0,0};

      

        // Where I store the coins
        std::vector<Coin*> coins;

    public:
        CashRegister();
        ~CashRegister();

        void Load_file_coins(string filepath);

        bool LoadRegister(string fileName);

        bool InsertCash(int denomination,int amount);

        bool GetChange(int change);

        int TotalMoney();

        string DenomToString(int denomination);

        int coin_file_to_denomation(Denomination file_denom);

        void display_coins();

        void saveRegister(string coinFile);

        void resetCoin();

        void RemoveCount(int index);
};

#endif 