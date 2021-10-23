#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "main_imports.hpp"
#include "hash.hpp"
#include "hash_pointer.hpp"
#include "transaction.hpp"
#include "vector"
#include <string>

class BlockchainBlock {
    private:
        HashPointer<BlockchainBlock> previous_block;
        string hash;
        string time_stamp;
        string version;
        string merkel_root_hash;
        int nonce;
        int difficulty_target;
        vector<BlockchainTransaction> body;


    public:
        BlockchainBlock(string previous_hash, BlockchainBlock* previous_block_ptr,
                        string hash, string time_stamp,
                        string version, int nonce,
                        int difficulty_target,
                        vector<BlockchainTransaction> body, string merkel_root_hash);

        // Getters & Setters
        string getHash();

        string getTimeStamp();

        string getVersion();

        string getMerkelHash();

        int getNonce();

        int getDifficultyTarget();

        vector<BlockchainTransaction> getBody();

        string getPreviousHash();

        ~BlockchainBlock();



        
};

#endif