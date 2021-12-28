#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "main_imports.hpp"
#include "hash.hpp"
#include "block.hpp"
#include "transaction.hpp"
#include "number_generator.hpp"
#include "user.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <bitcoin/system.hpp>

bool yes_or_no(string text); //asks yes or no question
string get_time(); //gets current time
string read_from_file(string filename); //reads the specified file
vector<string> list_dir(string path); //lists the specified directory


//updates user balances
void perform_transactions(vector<BlockchainTransaction> &transaction_pool,
                        vector<BlockchainTransaction> transactions,
                        vector<BlockchainUser> &users);

// mines the block and returns it
BlockchainBlock mine_block(int &miner_id,
                            string previous_block_hash,
                            BlockchainBlock* previous_block_ptr,
                            string version,
                            int difficulty_target,
                            vector<vector<BlockchainTransaction>> candidate_pools);

//logs the block
void log_block(int winer_miner_id, int block_number, BlockchainBlock* block);

#endif