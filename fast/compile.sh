#!/bin/bash
echo "Generating executable with optimization profile flags..."
g++ -O3 -fprofile-generate -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint

echo "Generating files required for optimization profile..."
time bigint e < one-liners | bigint d

echo "Generating new executable that uses opt. profiles..."
g++ -O3 -fprofile-use -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint