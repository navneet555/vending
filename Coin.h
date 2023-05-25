#ifndef COIN_H
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system.
#define DELIM "," // delimiter

// enumeration representing the various types of currency available in the system.
enum Denomination
{
    FIVE_CENTS = 5,
    TEN_CENTS = 10,
    TWENTY_CENTS = 20,
    FIFTY_CENTS = 50,
    ONE_DOLLAR = 100,
    TWO_DOLLARS = 200,
    FIVE_DOLLARS = 500,
    TEN_DOLLARS = 1000
};

// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    enum Denomination denom;

    // the count of how many of these are in the cash register
    int count;

    Coin();

    // the denom and how many coins there are of said denom
    Coin(Denomination denom, int count);

    void print();

    // changing the coins from file into denomation to work with
    // reference: https://cplusplus.com/forum/beginner/231488/
    static Denomination coin_file_to_denomation(unsigned file_denom);

    void incrementCount();

    void decrementCount();

    // WOULD I NEED A DECONSTRUCTER???S
};

#endif // COIN_H
