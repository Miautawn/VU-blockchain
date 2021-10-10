#include "block.hpp"

BlockchainBlock::BlockchainBlock(string previous_hash, BlockchainBlock* previous_block_ptr,
                                string hash, string time_stamp,
                                string version, string merkel_root_hash,
                                int nonce, int difficulty_target,
                                vector<BlockchainTransaction> body) : 

                                previous_block{previous_hash, previous_block_ptr},
                                hash{hash}, time_stamp{time_stamp},
                                version{version}, merkel_root_hash{merkel_root_hash},
                                nonce{nonce}, difficulty_target{difficulty_target},
                                body{body} {} 

string BlockchainBlock::getHash() {
    return hash;
}

string BlockchainBlock::getTimeStamp() {
    return time_stamp;
}

string BlockchainBlock::getVersion() {
    return version;
}

string BlockchainBlock::getMerkelHash() {
    return merkel_root_hash;
}

int BlockchainBlock::getNonce() {
    return nonce;
}

int BlockchainBlock::getDifficultyTarget() {
    return difficulty_target;
}

vector<BlockchainTransaction> BlockchainBlock::getBody() {
    return body;
}

string BlockchainBlock::getPreviousHash() {
    return previous_block.getHash();
}

BlockchainBlock::~BlockchainBlock() {
    previous_block.~HashPointer();
}