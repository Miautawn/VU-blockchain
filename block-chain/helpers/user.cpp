#include "user.hpp"

//konstruktorius
BlockchainUser::BlockchainUser(string name, string pub_key, int balance) : name{name},
                                                                            pub_key{pub_key},
                                                                            balance{balance} {}

string BlockchainUser::getName() { return name; }


string BlockchainUser::getPubKey() { return pub_key; }

int BlockchainUser::getBalance() { return balance ;}

void BlockchainUser::setBalance(int new_balance) {

    if (new_balance >= 0) {
        balance = new_balance;
    }

};