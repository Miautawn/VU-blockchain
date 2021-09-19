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

    cout<<"\nSTAGE 3 - COLLISION TEST"<<endl<<endl;

    fstream collision_input("./benchmark/stage_3/stage_3__01.txt");

    string str_1;
    string str_2;
    int collision_count = 0;
    int identical_count = 0;
    for(int i = 0; i<100000; i++) {
        collision_input >> str_1;
        collision_input >> str_2;

        if(str_1 != str_2) {
            if(dj_hash(str_1) == dj_hash(str_2)) collision_count += 1;
        } else identical_count += 1;
        
    }

    cout<<"Total identical pairs: "<<identical_count<<" out of 100000"<<endl;
    cout<<"Total collission count: "<<collision_count<<" out of "<<100000 - identical_count<<endl;
    cout<<"Continuing..."<<endl;

    cout<<"\nSTAGE 3 - similarity TEST"<<endl<<endl;

    fstream similarity_input("./benchmark/stage_4/stage_4__01.txt");

    string hash_1;
    string hash_2;
    float hex_min = 100.0;
    float hex_avg = 0.0;
    float hex_max = 0.0;
    float bit_min = 100;
    float bit_avg = 0.0;
    float bit_max = 0.0;

    for(int i = 0; i<100000; i++) {
        similarity_input >> str_1;
        similarity_input >> str_2;

        hash_1 = dj_hash(str_1);
        hash_2 = dj_hash(str_2);

        
        float hex_similarity = 0;
        float bit_similarity = 0;
        int equal_count_hex = 0;
        int equal_count_bit = 0;

        //checking the similarity on hex and bit level
        for(int i = 0; i<64; i++) {
            if(hash_1[i] == hash_2[i]) equal_count_hex++;

            bitset<8> bitset_1(hash_1[i]);
            bitset<8> bitset_2(hash_2[i]);
            equal_count_bit += (bitset_1 & bitset_2).count();
        }
        
 
        //calculating the results
        hex_similarity = equal_count_hex / 64.0;
        bit_similarity = equal_count_bit / 512.0;

        hex_min = (hex_similarity < hex_min) ? hex_similarity : hex_min; 
        hex_max = (hex_similarity > hex_max) ? hex_similarity : hex_max;
        hex_avg += hex_similarity;

        bit_min = (bit_similarity < bit_min) ? bit_similarity : bit_min;
        bit_max = (bit_similarity > bit_max) ? bit_similarity : bit_max;
        bit_avg += bit_similarity;

    }

    cout<<"Hex min similarity: "<<hex_min<<"%"<<endl;
    cout<<"Hex avg similarity: "<<hex_avg / 100000<<"%"<<endl;
    cout<<"Hex max similarity: "<<hex_max<<"%"<<endl;
    cout<<endl;
    cout<<"Bit min similarity: "<<bit_min<<"%"<<endl;
    cout<<"Bit avg similarity: "<<bit_avg / 100000<<"%"<<endl;
    cout<<"Bit max similarity: "<<bit_max<<"%"<<endl;

    cout<<"\nBENCHMARK COMPLETE..."<<endl;
    cout<<"Writing the results to output file...."<<endl;
    cout<<"DONE..."<<endl;


}