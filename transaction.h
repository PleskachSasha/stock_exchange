#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "asset.h"

class Transaction
{
public:
    Transaction();
private:
    Asset asset;
    int count;
};

#endif // TRANSACTION_H
