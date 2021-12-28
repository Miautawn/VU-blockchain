#include "utility.hpp"

RandomInt random_generator;

bool yes_or_no(string text)
{
  string option;
  while(option != "y" && option != "n")
  {
    cout<<text + " y/n: ";
    cin>>option;
  }
  return option == "y";
}

string get_time() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %OH:%OM:%OS");
    string str = oss.str();

    return str;
}


string read_from_file(string filename) {

    string input = "";
    ifstream input_file(filename);
    if(input_file) {

        stringstream buffer;
        buffer << input_file.rdbuf();
        input = buffer.str();
    } else cout<<"File not found :(   Aborting..."<<endl;

    return input;

}

void perform_transactions(vector<BlockchainTransaction> &transaction_pool,
                        vector<BlockchainTransaction> transactions,
                        vector<BlockchainUser> &users) {

    for(BlockchainTransaction transaction : transactions) {

        string sender_pub_key = transaction.getSender();
        string recipient_pub_key = transaction.getRecipient();
    
        for(int i = 0; i<users.size(); i++) {
            if(sender_pub_key == users[i].getPubKey()) {
                int old_balance = users[i].getBalance();
                int new_balance = old_balance - transaction.getSum();

                users[i].setBalance(new_balance);
            }

            if(recipient_pub_key == users[i].getPubKey()) {
                int old_balance = users[i].getBalance();
                int new_balance = old_balance + transaction.getSum();

                users[i].setBalance(new_balance);
            }
        }

        for(int i = 0; i<transaction_pool.size(); i++) {
            if(transaction_pool[i].getIndex() == transaction.getIndex()) {
                transaction_pool.erase(transaction_pool.begin() + i);
                break;
            }
            
        }
    }

}


// Merkle Root Hash
string create_merkle(vector<BlockchainTransaction> transactions)
{

    bc::hash_list merkle = {};

    for(int i = 0; i<transactions.size(); i++) {

        char char_array[65];
        strcpy(char_array, transactions[i].getTransactionID().c_str());
        
        bc::hash_digest temp_hash = bc::hash_literal(char_array);
        merkle.push_back(temp_hash);
    }

    // Stop if hash list is empty or contains one element
    if (merkle.empty()) return bc::encode_base16(bc::null_hash);
    else if (merkle.size() == 1) return bc::encode_base16(merkle[0]);


    // While there is more than 1 hash in the list, keep looping...
    while (merkle.size() > 1) {

        // If number of hashes is odd, duplicate last hash in the list.
        if (merkle.size() % 2 != 0) merkle.push_back(merkle.back());

        // List size is now even.
        assert(merkle.size() % 2 == 0);

        // New hash list.
        bc::hash_list new_merkle;

        // Loop through hashes 2 at a time.
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            // Join both current hashes together (concatenate).
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<decltype(concat_data.begin())>(concat_data.begin());

            concat.write_hash(*it);
            concat.write_hash(*(it + 1));

            // Hash both of the hashes.
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);

            // Add this to the new list.
            new_merkle.push_back(new_root);
        }

        // This is the new list.
        merkle = new_merkle;
    }
    // Finally we end up with a single item.
    return bc::encode_base16(merkle[0]);
}


BlockchainBlock mine_block(int &miner_id,
                            string previous_block_hash,
                            BlockchainBlock* previous_block_ptr,
                            string version,
                            int difficulty_target,
                            vector<vector<BlockchainTransaction>> candidate_pools) {

    int max_attemps = 100000;

    while(true) {

        bool success_flag = false;
        for(int i = 0; i<candidate_pools.size(); i++) {

            //creating the master string which will be used to mine this block
            string master_string = "";
            string master_hash = "";

            //constructing merkel tree
            string merkel_root_hash = create_merkle(candidate_pools[i]);

            //nonce of the block
            int nonce = 0;

            for(int j = 0; j < max_attemps; j++) {

                
                //generate a random nonce
                nonce = random_generator.rnd(0, 999999);

                //combine the header elements
                master_string = to_string(nonce) + 
                                previous_block_hash + 
                                version + merkel_root_hash + 
                                to_string(difficulty_target);

                //produce a candidate hash
                master_hash = my_hash(master_string);

                //check the candidate hash
                for(int i = 0; i<difficulty_target; i++) {
                    if(master_hash[i] != '0') break;
                    if(i == difficulty_target - 1) {
                        success_flag = true;
                    }
                }

                if(success_flag) {

                    //select the winer miner
                    miner_id = i + 1;

                    //get time-stamp
                    string time_stamp = get_time();

                    // return the block
                    return BlockchainBlock(previous_block_hash, previous_block_ptr,
                                                        master_hash, time_stamp,
                                                        version, nonce, difficulty_target,
                                                        candidate_pools[i], merkel_root_hash);
                }
            }
        }

        cout<<"All candidates failed... decreasing the difficulty..."<<endl;
        difficulty_target--;
    }
}

void log_block(int winer_miner_id, int block_number, BlockchainBlock* block) {

    vector<BlockchainTransaction> block_transactions = block->getBody();

    string filename = "logs/block-" + to_string(block_number) + ".txt";
    ofstream output(filename);

    output<< "BLOCK: "<<block_number<<endl;
    output<<"The Winer Miner: "<<winer_miner_id<<endl;
    output<<string(50, '-')<<endl<<endl;

    output<<"BLOCK HASH: "<<block->getHash()<<endl;
    output<<"PREVIOUS BLOCK HASH: "<<block->getPreviousHash()<<endl;
    output<<"TIMESTAMP: "<<block->getTimeStamp()<<endl;
    output<<"NUMBER OF TRANSACTIONS: "<<block_transactions.size()<<endl;
    output<<"DIFFICULTY: "<<block->getDifficultyTarget()<<endl;
    output<<"MERKEL ROOT HASH: "<<block->getMerkelHash()<<endl;
    output<<"VERSION: "<<block->getVersion()<<endl;
    output<<"NONCE: "<<block->getNonce()<<endl;

    output<<string(50, '-')<<endl<<endl;
    output<< "BLOCK TRANSACTIONS"<<endl;
    output<<endl;
    output<<endl;

    for(BlockchainTransaction transaction : block_transactions) {
        output<<"ID: "<<transaction.getTransactionID()<<endl;
        output<<"SENDER PUBLIC KEY: "<<transaction.getSender()<<endl;
        output<<"RECIPIENT PUBLIC KEY: "<<transaction.getRecipient()<<endl;
        output<<"SUM: "<<transaction.getSum()<<endl;
        output<<endl;
    }


}



