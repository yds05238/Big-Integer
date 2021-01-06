#!/bin/bash
echo "Generating executable with optimization profile flags..."
g++ -O3 -fprofile-generate -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bignum.cpp normal_bignum.cpp -o bignum

echo "Generating files required for optimization profile..."
time bignum e < one-liners | bignum d

echo "Generating new executable that uses opt. profiles..."
g++ -O3 -fprofile-use -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bignum.cpp normal_bignum.cpp -o bignum -pg