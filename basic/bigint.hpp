class Bigint {
 public:
  Bigint();
  Bigint(const Bigint&);
  Bigint(int);
  Bigint(std::string);
  std::string to_string();
  void check(std::string);
  bool operator<(Bigint);
  bool operator>(Bigint);
  bool operator==(Bigint);
  bool operator<=(Bigint);
  bool operator>=(Bigint);
  bool operator!=(Bigint);
  Bigint operator+(Bigint);
  Bigint operator-(Bigint);
  Bigint operator*(int);
  Bigint operator*(Bigint);
  Bigint operator/(Bigint);
  Bigint operator%(Bigint);
  Bigint expmod(Bigint, Bigint);
  Bigint gcd(Bigint);
  Bigint encrypt(std::string, std::string);
  Bigint decrypt(std::string, std::string);
  std::vector<int> as_vec();

 private:
  std::vector<int> digits;
  void append_digit(int);
};