#include "generators.hpp"

RandomInt number_generator;

BlockchainUser generate_user(string name) {

    string pub_key = my_hash(name);
    int balance = number_generator.rnd(100, 1000000);

    BlockchainUser new_user(name, pub_key, balance);

    return new_user;
}

BlockchainTransaction generate_transaction(BlockchainUser &sender, BlockchainUser &recipient) {
    BlockchainTransaction transaction(
        sender.getPubKey(),
        recipient.getPubKey(),
        number_generator.rnd(0, sender.getBalance() / 2)
    );

    return transaction;
}