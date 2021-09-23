# DJ Hash
Here you can find the files dedicated to "DJ hash" - my personal hashing algorithm.
- [Algorithm](#hash-algorithm)
- [Benchmark](#hash-benchmark)
- - [INPUT/OUTPUT SHAPE TEST](#stage-1---inputoutput-shape-test)
- - [SPEED TEST](#stage-2---speed-test)
- - [COLLISION TEST](#stage-3---collision-test)
- - [SIMILARITY TEST](#stage-4---similarity-test)
- [Results](#results-and-conclusions)


## Hash algorithm
1. take input
2. use magic to hash it
3. return the hash

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
HASH: 53706f776c69676b742c2077682c206f6f6f6e6f696768770781a9cb0593ec7b
./benchmark/stage_1/stage_1__02.txt hash size: 64...OK
HASH: 53706f746c69676c742c2075682c206d6f6f6e6c696768740781a9ee0593ec7e
./benchmark/stage_1/stage_1__03.txt hash size: 64...OK
HASH: 5375ff7f6c6dff7f742dff7f682dff7f6f6fff7f6967ff7f0785ffff0597ff3f
./benchmark/stage_1/stage_1__07.txt hash size: 64...OK
HASH: 53706f746c696768742c2075682c206d6f6f6e6c696768740781a9ca0593ec3a
./benchmark/stage_1/stage_1__06.txt hash size: 64...OK
HASH: 53796ff66c696fee742d29f7682d29ef6f6f6fee696f69f60789a9ce059bedfe
./benchmark/stage_1/stage_1__04.txt hash size: 64...OK
HASH: 53766f766c6f677e742e2677682e267f6f6f6e7e69676e760787afde0597ee3e
./benchmark/stage_1/stage_1__05.txt hash size: 64...OK
HASH: 53796ff76c696fef742d29f7682d29ef6f6f6fef696f69f70789a9cf059bedff
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
```
STAGE 2 - SPEED TEST

Time taken: 0.00378237 seconds
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
Total collission count: 163 out of 100000
Continuing...
```
___
### STAGE 4 - SIMILARITY TEST
This test was done to see whether the algorithm produces simmilar hashed. A good hash should produce very different looking hashes, even if inputs differ by a single bit (avalnche effect).

The data consist of pairs of identical strings except for one character. The string also vary in length (across pairs). The file structure is exact to the one used in the previous stage.

Similarity is meassure across characters of the hash output and the bits themselves.

```
STAGE 3 - similarity TEST

Hex min similarity: 51.5625%
Hex avg similarity: 83.9772%
Hex max similarity: 98.4375%

Bit min similarity: 83.0078%
Bit avg similarity: 95.5411%
Bit max similarity: 99.8047%

BENCHMARK COMPLETE...
Writing the results to output file....
DONE...
```
___

## Results and conclusions
