#include "transaction.hpp"

//konstruktorius
BlockchainTransaction::BlockchainTransaction(
    string sender,
    string recipient,
    int sum,
    int pool_index
    ) : sender{sender}, recipient{recipient}, sum{sum}, pool_index{pool_index} {

        transaction_id = my_hash( sender + recipient + to_string(sum) );


}

string BlockchainTransaction::getTransactionID() { return transaction_id; }

string BlockchainTransaction::getSender() { return sender; }

string BlockchainTransaction::getRecipient() { return recipient; }

int BlockchainTransaction::getSum() { return sum; }

int BlockchainTransaction::getIndex() { return pool_index; }