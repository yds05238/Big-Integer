#!/bin/bash
echo "Removing old files..."
rm -rf ./bigint 
rm -rf ./bigint.gcda
rm -rf ./main.gcda
rm -rf ./main.gcda
rm -rf ./normal_bigint.gcda
rm -rf ./encoded

echo "Generating executable with optimization profile flags..."
# g++ -O3 -fprofile-generate -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint -lpthread
g++ -O3 -fprofile-generate -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint -lpthread

echo "Generating files required for optimization profile..."
time bigint e < one-liners | bigint d

echo "Generating new executable that uses opt. profiles..."
g++ -O3 -fprofile-use -fprofile-correction -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint -lpthread



# # No Optimization Profile 
# g++ -O3 -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint -lpthread


