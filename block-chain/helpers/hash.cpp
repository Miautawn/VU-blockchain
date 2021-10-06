#include "hash.hpp"

// function to convert integer to hex
string integer_to_hex(unsigned int input) {
    stringstream input_stream;
    input_stream << setfill('0') << setw(sizeof(int) * 2)
                 << hex << input;

    return input_stream.str();
}

// hashing function
string my_hash(string input) {

    // initialize the hex variables
    unsigned int HEX[8] = {1399877492, 1818847080, 1949048949, 1747722349, 1869573740, 1768384628, 0740324712, 0544766072};

    const unsigned int input_length = input.length();
    
    // initialize the bitset arrays for the input and their copies
    bitset<32> bit_map[input_length];
    bitset<32> copy;

    // variables for the sum and hex
    int sum = 0;
    string full_hex = "";

    //add the input to bitset array and encode it
    for (int i = 0; i < input_length; i++) {

        
        bit_map[i] = input[i];
        const unsigned long char_value = bit_map[i].to_ulong();
        sum += char_value;

        // create a copy of the char bitset
        copy = bit_map[i];
        
        // reverse the char bitset
        string a = bit_map[i].to_string();
        reverse(a.begin(), a.end());
        bit_map[i] = bitset<32>(a);

        // push the bits to the left and right
        bit_map[i] >>= ((char_value + sum + input_length) % 16);
        copy <<= ((char_value + sum + input_length) % 32);

        // merge the bits of the copy and the char
        bit_map[i] |= copy;


        // shuffle the hex variable with the resulting char
        HEX[i % 8] ^= bit_map[i].to_ulong();
    }


    // make an avelanche effect
    for (int i = 0; i < 4; i++) {
        
        HEX[4+i] ^= HEX[i];
        HEX[i+1] ^= HEX[i+4];

        full_hex += integer_to_hex(HEX[i]);
        full_hex += integer_to_hex(HEX[i+1]);
    }

    return full_hex;
}