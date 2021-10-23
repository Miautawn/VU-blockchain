#include "generators.hpp"

RandomInt number_generator;

BlockchainUser generate_user(string name) {

    string pub_key = my_hash(name);
    int balance = number_generator.rnd(100, 1000000);

    BlockchainUser new_user(name, pub_key, balance);

    return new_user;
}

BlockchainTransaction generate_transaction(BlockchainUser &sender, BlockchainUser &recipient, int pool_index) {
    BlockchainTransaction transaction(
        sender.getPubKey(),
        recipient.getPubKey(),
        number_generator.rnd(1, sender.getBalance()),
        pool_index
    );

    return transaction;
}

vector<vector<BlockchainTransaction>> generate_candidate_pools(vector<BlockchainTransaction> transaction_pool, int block_capacity) {
    
    int n_candidates = 5;
    int n_transactions = (transaction_pool.size() >= block_capacity) ? block_capacity : transaction_pool.size();
    vector<vector<BlockchainTransaction>> candidate_pools = {};

    for(int i = 0; i<n_candidates; i++) {
        vector<BlockchainTransaction> original_pool = transaction_pool;
        vector<BlockchainTransaction> candidate_pool = {};

        for(int j = 0; j<n_transactions; j++) {
            int transaction_index = number_generator.rnd(0, original_pool.size() - 1);
            candidate_pool.push_back(original_pool[transaction_index]);
            original_pool.erase(original_pool.begin() + transaction_index);
        }

        candidate_pools.push_back(candidate_pool);
    }
    
    return candidate_pools;
}