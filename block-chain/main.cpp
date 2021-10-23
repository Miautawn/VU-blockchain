#include "main.hpp"


int main() {

    int n_users = 1000;
    int n_transactions = 10000;
    int block_capacity = 100;
    int difficulty_target = 3;
    int block_count = 0;
    string version = "0.1";
    string genesis_previous_hash = "sveiki, kaip sekasi?";
    BlockchainBlock* blockchain_head;


    vector<BlockchainUser> users = {};
    vector<BlockchainTransaction> transaction_pool = {};
    vector<vector<BlockchainTransaction>> candidate_pools = {};
    
    RandomInt number_generator;

    cout<<"\nGENERATING USERS..."<<endl;
   
    ifstream input_names("generator_files/names.txt");
    string name;
    for(int i = 0; i<n_users; i++) {
        getline(input_names, name);
        users.push_back( generate_user( name ));
    } 

    cout<<"VALIDATING PUBLIC KEYS..."<<endl;
    for(int i = 0 ; i < n_users; i++) {
        for(int j = 0; j < n_users; j++) {

            if(users[i].getPubKey() == users[j].getPubKey() && i != j) {
                cout<<"DETECTED PUBLIC KEY COLISION... BREAKING..."<<endl;
                return 0;
            }
        }
    }

    cout<<"CREATING A TRANSACTION POOL..."<<endl;

    for(int i = 0; i<n_transactions; i++) {

        //finding a sender with non-zero balance
        int sender_index = number_generator.rnd(0, users.size()); 
        while(users[sender_index].getBalance() <= 0) sender_index = number_generator.rnd(0, users.size()); 

        //the recipient is the sender index neightbour
        int recipient_index = (sender_index > 0) ? sender_index - 1 : sender_index + 1;
        BlockchainTransaction transaction = generate_transaction(users[sender_index], users[recipient_index], i);

        transaction_pool.push_back(transaction);
    }

    cout<<"VALIDATING TRANSACTION POOL INTEGRETY..."<<endl;
    for(int i = 0; i<transaction_pool.size(); i++) {

        string current_hash = my_hash(transaction_pool[i].getSender() +
                                    transaction_pool[i].getRecipient() +
                                    to_string(transaction_pool[i].getSum()));

        if(transaction_pool[i].getTransactionID() != current_hash) {
            cout<<"FOUND ILLEGAL TRANSACTION WITH ID: "<<transaction_pool[i].getTransactionID()<<endl;
            transaction_pool.erase(transaction_pool.begin() + i);
        }
    }

    cout<<"\nMINING A GENESIS BLOCK..."<<endl;
    
    candidate_pools = generate_candidate_pools(transaction_pool, block_capacity);
    blockchain_head = new BlockchainBlock(mine_block(genesis_previous_hash, nullptr,
                                         version, difficulty_target, candidate_pools));


    perform_transactions(transaction_pool, blockchain_head->getBody(), users);
    log_block(block_count, blockchain_head);
    candidate_pools.clear();
    block_count++;


    while(yes_or_no("\nAr kasti nauja blocka? ")) {
        if(transaction_pool.size() <= 0) {
            cout<<"NO MORE TRANSACTIONS... ENDING..."<<endl;
            break;
        }

        cout<<"\nMINING A BLOCK..."<<endl;
        candidate_pools = generate_candidate_pools(transaction_pool, block_capacity);
        blockchain_head = new BlockchainBlock(mine_block(blockchain_head->getHash(),
                                                        blockchain_head, version,
                                                        difficulty_target, candidate_pools));

        cout<<"DONE!... PERFORMING TRANSACTIONS..."<<endl;
        perform_transactions(transaction_pool, blockchain_head->getBody(), users);
        cout<<"LOGGING THE BLOCK..."<<endl;
        log_block(block_count, blockchain_head);
        candidate_pools.clear();
        block_count++;
    }

    return 0;



}




