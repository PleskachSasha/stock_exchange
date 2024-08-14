#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include "chrono"
#include "transaction.h"
#include "ordertype.h"

class Order
{
public:
    Order();
    updateStatus();
    cancel();
private:
    bool status;
    unsigned int id;
    OrderType orderType;
    std::chrono::system_clock::time_point creationTime;
    std::chrono::system_clock::time_point executionTime;
    std::vector<Transaction> transactions;
};

#endif // ORDER_H
