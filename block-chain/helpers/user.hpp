#ifndef USER_HPP
#define USER_HPP

#include "main_imports.hpp"

class BlockchainUser {
    private:
        string name;
        string pub_key;
        int balance;

    public:
        BlockchainUser(string name, string pub_key, int balance);

        // Getters & Setters
        string getName();
        string getPubKey();
        int getBalance();
        void setBalance(int new_balance);
};

#endif