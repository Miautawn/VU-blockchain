#include "main.hpp"


int main() {

    BlockchainUser user = generate_user("aloha");


    cout<<user.getName()<<" "<<user.getBalance()<<endl;

    
    return 0;

}




