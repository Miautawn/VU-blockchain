#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include "main_imports.hpp"
#include "number_generator.hpp"
#include "hash.hpp"
#include "user.hpp"
#include "transaction.hpp"

BlockchainUser generate_user(string name);

BlockchainTransaction generate_transaction(BlockchainUser &sender, BlockchainUser &recipient, int pool_index);

//generate candidate transaction pools
vector<vector<BlockchainTransaction>> generate_candidate_pools(vector<BlockchainTransaction> transaction_pool, int block_capacity);


#endif