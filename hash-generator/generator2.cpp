#include <iostream>
#include <fstream>
#include <random>

using namespace std;

class RandomInt{
    private:
        std::random_device rd;
        std::mt19937 mt;
    public:
        RandomInt() : mt( rd() ) {}

        //skaičiaus generavimas
        int rnd(int low, int high) {
            std::uniform_int_distribution<int> dist(low, high);
            return dist(mt);
        }
};

string gen_random(const int len) {
    
    string tmp_s;
    string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    RandomInt random;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) 
        tmp_s += alphanum[random.rnd(0, alphanum.length() - 1)];
    
    
    return tmp_s;
    
}

string get_different(string input) {

    string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string output = input;
    RandomInt random;

    while(input[0] == output[0]) {
        output[0] = alphanum[random.rnd(0, alphanum.length() - 1)];
    }

    return output;

}


int main() {

    ofstream col("benchmark/stage_4/stage_4__01.txt");

    
    for(int i = 0; i<100000; i++) {

        string str_1;
        string str_2;

        if(i<25000) str_1 = gen_random(10);
        else if(i < 50000) str_1 = gen_random(100);
        else if(i < 75000) str_1 = gen_random(500);
        else str_1 = gen_random(1000);

        str_2 = get_different(str_1);
        col<<str_1<<" "<<str_2<<endl;


    }


    return 0;
}