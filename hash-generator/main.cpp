#include "main.hpp"


bool yes_or_no(string text)
{
  string option;
  while(option != "y" && option != "n")
  {
    cout<<text + " y/n: ";
    cin>>option;
  }
  cin.ignore();
  return option == "y";
}

int main() {

    string input;

    if(yes_or_no("Do you want to read from file?")) {

        // reading from file
        string file_name;
        cout<<"Input the name of the txt file: ";
        cin >> file_name;

        ifstream input_file(file_name);
        if(input_file) {

            stringstream buffer;
            buffer << input_file.rdbuf();
            input = buffer.str();

        } else cout<<"File not found :(   Aborting..."<<endl;

       
    
    } else {

        // reading from the console
        cout<<"Enter your phrase: ";
        getline(cin, input);
    }

    cout<< dj_hash(input) << endl;
}




