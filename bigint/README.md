## Complete BigInt Library 

Fast BigInt library with more functionalities added for easier/wider use. Adds 
additional features to the fast bigint library. 

### Usage

-  With Profiler enabled 
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

