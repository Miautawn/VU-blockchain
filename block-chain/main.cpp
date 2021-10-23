#include "main.hpp"


int main() {

    int n_users = 1000;
    int n_transactions = 10000;
    int difficulty_target = 1;
    int block_count = 0;
    string version = "0.1";
    string genesis_previous_hash = "sveiki, kaip sekasi?";
    BlockchainBlock* blockchain_head;


    vector<BlockchainUser> users = {};
    vector<BlockchainTransaction> transactions = {};
    vector<BlockchainTransaction> block_pool = {};
    
    RandomInt number_generator;

    cout<<"GENERATING USERS..."<<endl;
   
    ifstream input_names("generator_files/names.txt");
    string name;
    for(int i = 0; i<n_users; i++) {
        getline(input_names, name);
        users.push_back( generate_user( name ));
    } 

    cout<<"\nVALIDATING PUBLIC KEYS..."<<endl;
    for(int i = 0 ; i < n_users; i++) {
        for(int j = 0; j < n_users; j++) {

            if(users[i].getPubKey() == users[j].getPubKey() && i != j) {
                cout<<"DETECTED PUBLIC KEY COLISION... BREAKING..."<<endl;
                return 0;
            }
        }
    }

    cout<<"\nCREATING A TRANSACTION POOL..."<<endl;

    for(int i = 0; i<n_transactions; i++) {

        //finding a sender with non-zero balance
        int sender_index = number_generator.rnd(0, users.size()); 
        while(users[sender_index].getBalance() <= 0) sender_index = number_generator.rnd(0, users.size()); 

        //the recipient is the sender index neightbour
        int recipient_index = (sender_index > 0) ? sender_index - 1 : sender_index + 1;
        BlockchainTransaction transaction = generate_transaction(users[sender_index], users[recipient_index]);

        transactions.push_back(transaction);
    }

    cout<<"\nMINING A GENESIS BLOCK"<<endl;
    
    for(int i = 0; i<100; i++) { 
        block_pool.push_back(transactions.back());
        transactions.pop_back();
    }

    perform_transactions(block_pool, users);
    blockchain_head = new BlockchainBlock(mine_block(genesis_previous_hash, nullptr,
                                         version, difficulty_target, block_pool));
    log_block(block_count, blockchain_head, block_pool);
    block_pool.clear();
    block_count++;



    while(yes_or_no("\nAr kasti nauja blocka? ")) {

        if(transactions.size() == 0) {
            cout<<"NO MORE TRANSACTIONS! BREAKING..."<<endl;
            break;
        }

        cout<<"\nMINING A BLOCK..."<<endl;
        for(int i = 0; i<100; i++) { 
            if(transactions.size() == 0) break;

            block_pool.push_back(transactions.back());
            transactions.pop_back();
        }

        blockchain_head = new BlockchainBlock(mine_block(blockchain_head->getHash(),
                                                        blockchain_head, version,
                                                        difficulty_target, block_pool));

        cout<<"DONE!... PERFORMING TRANSACTIONS..."<<endl;
        perform_transactions(block_pool, users);
        cout<<"LOGGING THE BLOCK..."<<endl;
        log_block(block_count, blockchain_head, block_pool);
        block_pool.clear();
        block_count++;
    }

 
    
    return 0;



}




