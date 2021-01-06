## Basic BigInt Library 

Simple BigInt library with limiited functionalities. The library only uses C++17 STL with little focus put on performance. The original codebase was from Cornell CS4414 Course Prof. Ken.

### Usage

- Compile using shell scripts provided
    - compile.sh: no profiler 
    - compile-pg.sh: profiler enabled

-  Generate performance profiles
    - bigint e < one-liners > encoded
    - gprof bigint > analysis_encrypt.txt

    - bigint d < encoded
    - gprof bigint > analysis_decrypt.txt 


- Basic timed Encrypt + Decrypt 
    - time echo "The quick brown fox jumps over the lazy dog" | bigint e | bigint d

- Separate timed Encrypt + Decrypt
    - time bigint e < one-liners > encoded
    - time bigint d < encoded

- Total timed Encrypt + Decrypt
    - time bigint e < one-liners | bigint d



### Features

