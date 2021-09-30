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


int main() {

    ofstream col("benchmark/stage_3/stage_3__01.txt");

    
    for(int i = 0; i<100000; i++) {

        if(i<25000) col << gen_random(10)<<" "<<gen_random(10)<<endl;
        else if(i < 50000) col << gen_random(100)<<" "<<gen_random(100)<<endl;
        else if(i < 75000) col << gen_random(500)<<" "<<gen_random(500)<<endl;
        else col << gen_random(1000)<<" "<<gen_random(1000)<<endl;

        

    }


    return 0;
}