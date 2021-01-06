echo "Removing old files..."
rm -rf ./bigint 
rm -rf ./bigint.gcda
rm -rf ./main.gcda
rm -rf ./main.gcda
rm -rf ./normal_bigint.gcda
rm -rf ./encoded
rm -rf ./encoded2
rm -rf ./gmon.out

echo "Generating executable with optimization profile flags..."
g++ -O3 -fprofile-generate -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint -lpthread

echo "Generating files required for optimization profile..."
time echo "The quick brown fox jumps over the lazy dog" | bigint e | bigint d
time bigint e < one-liners2 > encoded2 
time bigint d < encoded2
time bigint e < one-liners | bigint d 

echo "Generating new executable that uses opt. profiles..."
g++ -O3 -fprofile-use -fprofile-correction -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint -lpthread

# # No Optimization Profile 
# g++ -O3 -Wall -Wpedantic -std=c++17 -march=native -flto -pipe main.cpp bigint.cpp normal_bigint.cpp -o bigint -lpthread


