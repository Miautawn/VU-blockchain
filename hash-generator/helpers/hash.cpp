#include "hash.hpp"

string integer_to_hex(int input) {
    stringstream input_stream;
    input_stream << setfill('0') << setw(sizeof(int) * 2)
                 << hex << input;

    return input_stream.str();
}

string dj_hash(string input) {

    int HEX[8] = {1399877492, 1818847080, 1949048949, 1747722349, 1869573740, 1768384628, 0740324712, 0544766072};

    int input_length = input.length();
    // unsigned char base_array[input_length];

    int sum = 0;

    for (int i = 0; i < input_length; i++) {
        // base_array[i] = input[i];
        sum += int(input[i]);
    }

    cout<<"suma: "<<sum<<endl;

    string full_hex = "";

    for (int i = 0; i < 8; i++) {

        full_hex += integer_to_hex( (HEX[i] | sum) );

    }

    return full_hex;
}