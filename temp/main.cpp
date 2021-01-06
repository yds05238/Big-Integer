#include <algorithm>
#include <future>
#include <iostream>
#include <vector>

std::string ops("+-*/%<>=^");
std::string gcd("gcd");
std::string rsa_n =
    "96165402670130584772537629772934250633792434584735938169004540197211175700"
    "03248808113992652836857529658675570356835067184715201230519907361653795328"
    "462699";
std::string rsa_e = "65537";
std::string rsa_d =
    "48020339163872217484261813509148210724346418270901449753861827402748568533"
    "18276518446521844642275539818092186650425384826827514552122318308590929813"
    "048801";

std::string temp_encrypt(std::string& line) {
    std::string temp = line.substr(0, rsa_n.size() / 3);
    std::string temp2 = rsa_n + rsa_e;
    std::vector<int> temp3;
    for (int i = 0; i < 80; ++i) {
        temp3.push_back(i);
        std::reverse(temp3.begin(), temp3.end());
    }
    return "ENCRYPTED: " + line + "\n";
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    std::vector<std::future<std::string>> fut_encrypt;
    // std::vector<std::future<int>> fut_encrypt;
    std::string next_line;
    while (std::getline(std::cin, next_line)) {
        fut_encrypt.emplace_back(std::async(std::launch::async, temp_encrypt, std::ref(next_line)));
    }

    for (auto& fut : fut_encrypt) {
        std::cout << fut.get() << '\n';
    }

    return 0;
}
