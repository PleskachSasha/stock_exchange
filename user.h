#ifndef USER_H
#define USER_H
#include <string>
#include <chrono>
#include "wallet.h"
#include "asset.h"

class User
{
public:
    User();
    void buy(Asset asset, int count);
    void sell(Asset asset, int count);
    void showOrders(int period);
    void getWallet();
    void changePassword(std::string oldPass, std::string newPass);
    void getTransactionHistory();
private:
    unsigned int id;
    std::string name;
    std::string password;
    std::string phone;
    std::chrono::system_clock::time_point registrationDate;
    std::chrono::system_clock::time_point lastLoginDate;
    Wallet wallet;
};

#endif // USER_H
