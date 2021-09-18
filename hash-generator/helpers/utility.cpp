#include "utility.hpp"

bool yes_or_no(string text) {
  string option;
  while(option != "y" && option != "n")
  {
    cout<<text + " y/n: ";
    cin>>option;
  }
  cin.ignore();
  return option == "y";
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


