#include <algorithm>
#include <iostream>
#include <vector>

#include "bigint.hpp"

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

bool is_digit(const char value) { return std::isdigit(value); }
bool is_numeric(const std::string& value) {
  return std::all_of(value.begin(), value.end(), is_digit);
}

std::string to_numeric(std::string next_line) {
  std::string nlad("");
  for (auto c : next_line) {
    int d = ((int)c & 0xFF);
    nlad += (d / 100) % 10 + '0';
    nlad += (d / 10) % 10 + '0';
    nlad += d % 10 + '0';
  }
  return nlad;
}

std::string to_chars(Bigint to_numeric) {
  std::string nlas("");
  int d_to_go = to_numeric.as_vec().size() % 3;
  if (d_to_go == 0) d_to_go = 3;
  int index = 0;
  int next_d = 0;
  int size = (to_numeric.as_vec().size() + 2) / 3;
  for (int n = 0; n < size; n++) {
    do {
      next_d = next_d * 10 + to_numeric.as_vec()[index++];
    } while (--d_to_go);
    nlas += (char)next_d;
    next_d = 0;
    d_to_go = 3;
  }
  return nlas;
}

int main(int argc, char** argv) {
  std::string op;
  std::string num1;
  std::string num2;
  std::string num3;
  if (argc != 4 && (argc != 5 || *argv[1] != '^') &&
      (argc != 2 || (*argv[1] != 'e' && *argv[1] != 'd'))) {
    std::cout
        << "Run as bigint -op number1 number2, or bigint -help, "
           "where:\n	op is one of + - * / %% gcd encrypt decrypt\n	"
           "number1 and number2 are positive integers of arbitrary length\n"
        << std::endl;
    return 0;
  }
  op = std::string(argv[1]);
  if (op[0] != 'd' && op[0] != 'e') {
    num1 = std::string(argv[2]);
    if (!is_numeric(num1)) {
      std::cout << "Error: " << num1 << " is not an unsigned integer.\n"
                << std::endl;
      return 1;
    }
    num2 = std::string(argv[3]);
    if (!is_numeric(num2)) {
      std::cout << "Error: " << num2 << " is not an unsigned integer.\n"
                << std::endl;
      return 1;
    }
    if (argc == 5) {
      num3 = std::string(argv[4]);
      if (!is_numeric(num3)) {
        std::cout << "Error: " << num3 << " is not an unsigned integer.\n"
                  << std::endl;
        return 1;
      }
    } else if (op[0] == '^') {
      std::cout << "Error: Modular exponentiation requires an exponent and a "
                   "modulus!\n"
                << std::endl;
      return 1;
    }
  }
  int counter = 3;
  switch (op[0]) {
    case '+':
      std::cout << (Bigint(num1) + Bigint(num2)).to_string() << std::endl;
      return 0;
    case '-':
      std::cout << (Bigint(num1) - Bigint(num2)).to_string() << std::endl;
      return 0;
    case '*':
      std::cout << (Bigint(num1) * Bigint(num2)).to_string() << std::endl;
      return 0;
    case '/':
      std::cout << (Bigint(num1) / Bigint(num2)).to_string() << std::endl;
      return 0;
    case '%':
      std::cout << (Bigint(num1) % Bigint(num2)).to_string() << std::endl;
      return 0;
    case '<':
      std::cout << (Bigint(num1) < Bigint(num2)) << std::endl;
      return 0;
    case '>':
      std::cout << (Bigint(num1) > Bigint(num2)) << std::endl;
      return 0;
    case '=':
      std::cout << (Bigint(num1) == Bigint(num2)) << std::endl;
      return 0;
    case '^':
      std::cout << Bigint(num1).expmod(num2, num3).to_string() << std::endl;
      return 0;
    case 'g':
      std::cout << (Bigint(num1).gcd(Bigint(num2))).to_string() << std::endl;
      return 0;
    case 'e':
      while (!std::cin.eof()) {
        std::string next_line;
        std::getline(std::cin, next_line);
        // Many famous movie lines are too long to encrypt in one chunk, so we
        // do all of them as two lines A line too long for two-chunk encryption
        // is truncated (this only affects one line)
        if (next_line.size() * 3 > rsa_n.size()) {
          std::cout << Bigint(to_numeric(next_line.substr(0, rsa_n.size() / 3)))
                           .encrypt(rsa_n, rsa_e)
                           .to_string()
                    << std::endl;
          std::cout << Bigint(to_numeric(next_line.substr(rsa_n.size() / 3,
                                                          rsa_n.size() / 3)))
                           .encrypt(rsa_n, rsa_e)
                           .to_string()
                    << std::endl;
        } else  // Fits on one line
        {
          std::cout
              << Bigint(to_numeric(next_line)).encrypt(rsa_n, rsa_e).to_string()
              << std::endl;
          std::cout << Bigint(++counter).encrypt(rsa_n, rsa_e).to_string()
                    << std::endl;
        }
      }
      return 0;
    case 'd':
      while (!std::cin.eof()) {
        std::string part1, part2;
        std::getline(std::cin, part1);
        std::getline(std::cin, part2);
        std::cout << to_chars(Bigint(part1).decrypt(rsa_n, rsa_d).to_string());
        Bigint p2 = Bigint(part2).decrypt(rsa_n, rsa_d);
        if (p2 > Bigint(100000)) {
          std::cout << to_chars(p2.to_string());
        }
        std::cout << std::endl;
      }
      return 0;
    default:
      std::cout << "Error: " << op << " is not a supported operator\n"
                << std::endl;
      return 1;
  }
}
