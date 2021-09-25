# Hash generator by Martynas Jašinskas
Here you can find the files dedicated to my personal hashing algorithm.
- [Algorithm](#hash-algorithm)
- [Benchmark](#hash-benchmark)
- - [INPUT/OUTPUT SHAPE TEST](#stage-1---inputoutput-shape-test)
- - [SPEED TEST](#stage-2---speed-test)
- - [COLLISION TEST](#stage-3---collision-test)
- - [SIMILARITY TEST](#stage-4---similarity-test)
- [Results](#results-and-conclusions)


## Hash algorithm
Here is the pseudocode for the algorithm.


```
FUNCTION my_hash(input: string): string {
  HEX <- [8]                                    //initialize an integer array with 8 elements
  
  bit_map <- bitset<32>[input.length]           //initialize 32 bit bitset array with [input.length] elements.
  bit_map_copy <- null
  
  sum <- 0                                      //initialize the sum variable
  full_hex <- ""                                //initialize the final hex string
  
  FOR i = 0 TO input.length
    bit_map[i] <- input[i]                      //put the input char bits to a specific bit_map index
    bit_value <- int(input[i])                  //take that input numeric value
    
    sum <- sum + bit_value
    copy <- bit_map[i]
    
    bit_map[i] <- REVERSE(bit_map[i])           //reverse the bit_map element
    
    bit_map[i] <- bit_map[i] RIGHT_SHIFT ((bit_value + sum + input.length) % 16)
    copy <- copy LEFT_SHIFT ((bit_value + sum + input.length) % 32)
    
    bit_map[i] <- bit_map[i] BITWISE_OR copy      //merge the bit_map element and it's copy
    
    HEX[i % 8] <- HEX[i % 8] XOR int(bit_map[i])  //modify the HEX elements with this bit_map element
    
    
  FOR i = 0 TO 4                                  //produce an avalanche effect
    HEX[i + 4] <- HEX[i + 4] XOR HEX[i]
    HEX[i + 1] <- HEX[i + 1] XOR HEX[i + 4]
    
    full_hex <- full_hex + TO_HEX(HEX[i])
    full_hex <- full_hex + TO_HEX([HEX[i + 1]])
    
  RETURN full_hex

}
```

___

## Hash benchmark
To test this hashing generator, 6 good hashing-function requirements were benchmarked:
1. Hashing generator insensitivity to input size  
2. Output hash size stability - it should always output 64 character hash
3. Deterministic property
4. Hash calculation time complexity and speed
5. Collision resistance
6. Hash dissimilarities - avalanche effect

The benchmark described obove is written in the ```helpers\benchmark.cpp``` file and it consits of the following stages:
### STAGE 1 - INPUT/OUTPUT SHAPE TEST
During this stage, the 1-3 requirements described above are tested.

The data for this test can be found in the ```benchmark\stage_1``` folder. There are 7 text files:
* The first 2 files consist of a single letter
* The second pair consits of two randomly generated 5000 character long strings
* The third pair has identical 7500 long string except for a single chracter in the middle
* The final file is empty


Using these files, the properties of input size insensitivity and output size stability were tested by making sure that no matter the input lenght, the resulting hash would allways be 64 characters long.
```
STAGE 1 - INPUT/OUTPUT SHAPE TEST

./benchmark/stage_1/stage_1__01.txt hash size: 64...OK
HASH: 52f44ef451f247f051f247f04cb90ff14cb90ff123148656231486561b1c4af4
./benchmark/stage_1/stage_1__02.txt hash size: 64...OK
HASH: 5363a7745065ae705065ae704d2ee6714d2ee67122836fd622836fd61b1c4af4
./benchmark/stage_1/stage_1__03.txt hash size: 64...OK
HASH: 6410ed82f0a4e300f0a4e3003b36d7ae3b36d7ae1a44f2911a44f29159ebba7b
./benchmark/stage_1/stage_1__07.txt hash size: 64...OK
HASH: 53706f7450766670507666704d3d2e714d3d2e712290a7d62290a7d61b1c4af4
./benchmark/stage_1/stage_1__06.txt hash size: 64...OK
HASH: f96f6e961393603e1393603e76db63c276db63c2083654d5083654d5e0f45c8c
./benchmark/stage_1/stage_1__04.txt hash size: 64...OK
HASH: dacfe6dadbddab9edbddab9ed316bb87d316bb87d0325ab4d0325ab47343fb0a
./benchmark/stage_1/stage_1__05.txt hash size: 64...OK
HASH: e6c50cb7ff20f507ff20f5073f76f41f3f76f41ff2c025e4f2c025e46b86bff7
```

The produced hashes for each of the input file was then saved as history in order to test the deterministic property by runing the same process again and checking whether the hashes match
```
All output shapes are OK, continuing...

Reruning the hashing, to verify deterministic property...

./benchmark/stage_1/stage_1__01.txt file hash: ...OK
./benchmark/stage_1/stage_1__02.txt file hash: ...OK
./benchmark/stage_1/stage_1__03.txt file hash: ...OK
./benchmark/stage_1/stage_1__07.txt file hash: ...OK
./benchmark/stage_1/stage_1__06.txt file hash: ...OK
./benchmark/stage_1/stage_1__04.txt file hash: ...OK
./benchmark/stage_1/stage_1__05.txt file hash: ...OK
All outputs are the same, continuing...
```
___

### STAGE 2 - SPEED TEST
The speed of the this hashing algorithm was measured to check the 4'th requirement - time complexity. By definition it is **O(n)**. The speed of the hash generator was measured by hashing each line of the ```helpers\stage_2\konstitucija.txt``` file excluding the IO parts of the process.

The process was repeasted for 5000 epochs and the average was taken.  
Other popular hashing algorithms were tested this way as well.
```
STAGE 2 - SPEED TEST

Number of episodes: 500
DJ hash    avg time: 15.8976 ms
md5        avg time: 1.16586 ms
SHA1       avg time: 1.72137 ms
SHA256     avg time: 2.24886 ms
```
___
### STAGE 3 - COLLISION TEST
This test was performed in order to check collision rate for this hash algorithm. It was done by taking pairs of randomly generated strings of varying length (across pairs). The file consists of:
* **25000** pairs of **10** character long strings
* **25000** pairs of **100** character long strings
* **25000** pairs of **500** character long strings
* **25000** of **1000** character long strings

First, pairs are checked whether they are identical and if not, their hashes are checked.
```
STAGE 3 - COLLISION TEST

Total identical pairs: 0 out of 100000
Total collission count: 0 out of 100000
Continuing...
```
___
### STAGE 4 - SIMILARITY TEST
This test was done to see whether the algorithm produces simmilar hashed. A good hash should produce very different looking hashes, even if inputs differ by a single bit (avalnche effect).

The data consist of pairs of identical strings except for one character. The string also vary in length (across pairs). The file structure is exact to the one used in the previous stage.

Similarity is meassure across characters of the hash output and the bits themselves.

```
STAGE 3 - SIMILARITY TEST

Hex min similarity: 0%
Hex avg similarity: 9.52592%
Hex max similarity: 100%

Bit min similarity: 54.8828%
Bit avg similarity: 68.2698%
Bit max similarity: 100%
```
___

## Results and conclusions
