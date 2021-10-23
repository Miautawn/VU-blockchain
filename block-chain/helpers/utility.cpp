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

vector<string> list_dir(string path) {

    vector<string> files = {};
    for (const auto entry : filesystem::directory_iterator(path))
        files.push_back(entry.path());

    return files;
}

void perform_transactions(vector<BlockchainTransaction> transactions, vector<BlockchainUser> &users) {
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
    }

}

string constructMerkelTree(vector<BlockchainTransaction> transactions) {

    vector<string> current_layer = {};
    vector<string> next_layer = {};

    //populate the first layer
    for (BlockchainTransaction element : transactions) {
        current_layer.push_back(element.getTransactionID());
    }

    //how many layers there will be
    int n_loops = ceil(log2(current_layer.size()));

    for(int i = 0; i<n_loops; i++) {
    
        //balance the tree
        if(current_layer.size() % 2 != 0) current_layer.push_back(current_layer.back());

        for(int j = 0; j<current_layer.size(); j+=2) {
            next_layer.push_back( my_hash(my_hash(current_layer[j] + current_layer[j+1])) );
        }

        current_layer.clear();
        current_layer = next_layer;
        next_layer.clear();
       
    }

    return current_layer[0];
}

BlockchainBlock mine_block(string previous_block_hash,
                            BlockchainBlock* previous_block_ptr,
                            string version,
                            int difficulty_target,
                            vector<BlockchainTransaction> transactions) {

    //creating the master string which will be used to mine this block
    string master_string = "";
    string master_hash = "";

    //constructing merkel tree
    string merkel_root_hash = constructMerkelTree(transactions);

    //mining the block
    int nonce = 0;
    bool success_flag = false;
    while(!success_flag) {
        
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

    }

    //get time-stamp
    string time_stamp = get_time();

    // return the block
    return BlockchainBlock(previous_block_hash, previous_block_ptr,
                                    master_hash, time_stamp,
                                    version, nonce, difficulty_target,
                                    transactions, merkel_root_hash);
}

void log_block(int block_number, BlockchainBlock* block, vector<BlockchainTransaction> block_transactions) {

    string filename = "logs/block-" + to_string(block_number) + ".txt";
    ofstream output(filename);

    output<< "BLOCK: "<<block_number<<endl;
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



