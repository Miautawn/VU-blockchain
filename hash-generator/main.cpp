#include "main.hpp"


int main() {

    // benchmark();

    string input;
    string filename;
    int selection = 0;
    while(selection < 1 || selection > 3) {
        cout<<"1. Read from console"<<endl;
        cout<<"2. Read from file"<<endl;
        cout<<"3. Perform benchmark"<<endl;
        cout<<"Enter your selection: ";
        cin>>selection;
        cout<<endl;
    }

    switch(selection) {
        case 1: 
        cout<<"Enter the input: ";
        cin.ignore();
        getline(cin, input);
        break;

        case 2:
        
        cout<<"Input the name of the txt file: ";
        cin >> filename;
        input = read_from_file(filename);
        break;

        case 3:
        benchmark();
        break;
    }

    cout<<my_hash(input)<<endl;

    return 0;

}




