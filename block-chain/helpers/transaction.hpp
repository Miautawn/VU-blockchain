#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "main_imports.hpp"
#include "hash.hpp"
#include <string>

class BlockchainTransaction {
    private:
        string transaction_id;
        string sender;
        string recipient;
        int sum;
        int pool_index;

    public:
        BlockchainTransaction(string sender, string recipient, int sum, int pool_index);

        // Getters & Setters
        string getTransactionID();
        string getSender();
        string getRecipient();
        int getSum();
        int getIndex();
};

#endif