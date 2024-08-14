#ifndef WALLET_H
#define WALLET_H
#include <vector>
#include <map>
#include "transaction.h"

class Wallet
{
public:
    Wallet();
private:
    float balance;
    std::vector<Transaction> transactions;
    std::map<Transaction, int> wallet; //unordered_map?
};

#endif // WALLET_H
