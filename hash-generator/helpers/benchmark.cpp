#include "benchmark.hpp"

void benchmark() {

    cout<<"<STARTING THE BENCHMARK>"<<endl;
    cout<<"\nSTAGE 1 - INPUT/OUTPUT SHAPE TEST"<<endl<<endl;

    vector<string> stage_files = list_dir("./benchmark/stage_1");

    bool pass_flag = true;
    vector<string> hash_history = {};
    for (int i = 0; i<stage_files.size(); i++) {

        

        string hash = dj_hash(read_from_file(stage_files[i]));
        int hash_length = hash.length();
        hash_history.push_back(hash);

        cout<<stage_files[i]<<" hash size: "<<hash_length;
        if(hash_length == 64) cout<<"...OK"<<endl;
        else { cout<<"...FAIL"<<endl; pass_flag = false; }

        cout<<"HASH: "<<hash<<endl;
    }
    cout<<endl;

    if(pass_flag) cout<<"All output shapes are OK, continuing..."<<endl<<endl;
    else { cout<<"There was an error with the hash shape, aborting..."<<endl; return; }

    cout<<"Reruning the hashing, to verify deterministic property..."<<endl<<endl;
    for (int i = 0; i<stage_files.size(); i++) {

        string hash = dj_hash(read_from_file(stage_files[i]));

        cout<<stage_files[i]<<" file hash: ";
        if(hash == hash_history[i]) cout<<"...OK"<<endl;
        else { cout<<"...FAIL"<<endl; pass_flag = false; }
    }

    if(pass_flag) cout<<"All outputs are the same, continuing..."<<endl<<endl;
    else { cout<<"There was a missmatch between the outputs, aborting..."<<endl; return; }

    cout<<"\nSTAGE 2 - SPEED TEST"<<endl<<endl;

    fstream speed_input("./benchmark/stage_2/konstitucija.txt");
    Timer timer;
    double full_time = 0;
    string line;

    while(getline(speed_input, line)) {
        timer.reset();
        dj_hash(line);
        full_time += timer.current_time();
    }

    cout<<"Time taken: "<<full_time<<" seconds"<<endl;

    cout<<"\nSTAGE 3 - UNKNOWN TEST"<<endl<<endl;


}