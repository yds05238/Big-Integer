#include <iostream>
#include <algorithm>
#include <vector>
#include "bigint.hpp"

//
// A Bigint is just a std::vector containing digits in the range 0-9, following the decimal
// convention that a number other than 0 has no leading 0's.  Oddly, that one rule made the
// code unexpectedly complicated; it would have been easier to just allow numbers like 0002!
//

Bigint::Bigint() {
}

Bigint::Bigint(const Bigint& b) {
	digits = b.digits;
}

Bigint::Bigint(int d) {
	digits.push_back(d);
}

const Bigint BZero(0);
const Bigint BOne(1);

Bigint::Bigint(std::string s) {
	for(auto c: s)
		digits.push_back(c-'0');
}

std::vector<int> Bigint::as_vec() {
	return digits;
}

std::string Bigint::to_string() {
	std::string s;
	for(auto d: digits) {
		s += std::to_string(d);
	}
	return s;
}

bool Bigint::operator<(Bigint b) {
	int alen = digits.size();
	int blen = b.digits.size();
	int aindex = 0, bindex = 0;
	if(alen > blen) {
		return false;
	}
	if(blen > alen) {
		return true;
	}
	while(alen-- > 0) {
		if(digits[aindex] > b.digits[bindex]) {
			return false;
		}
		if(digits[aindex++] < b.digits[bindex++]) {
			return true;
		}
	}
	return false;
}

bool Bigint::operator>(Bigint b) {
	return b<*this;
}

bool Bigint::operator==(Bigint b) {
	return ! (*this<b || b<*this);
}

bool Bigint::operator<=(Bigint b) {
	return ! (*this>b);
}

bool Bigint::operator>=(Bigint b) {
	return ! (*this<b);
}

bool Bigint::operator!=(Bigint b) {
	return ! (*this==b);
}

Bigint Bigint::operator+(Bigint b) {
	Bigint res;
	int alen = digits.size();
	int blen = b.digits.size();
	int aindex = 0, bindex = 0;
	while(alen > blen) {
		res.digits.push_back(digits[aindex++]);
		--alen;
	}
	while(blen > alen) {
		res.digits.push_back(b.digits[bindex++]);
		--blen;
	}
	while(alen-- > 0) {
		res.digits.push_back(digits[aindex++] + b.digits[bindex++]);
	}
	int rlen = res.digits.size();
	int carry = 0;
	while(rlen > 0) {
		carry += res.digits[--rlen];
		res.digits[rlen] = carry%10;
		carry /= 10;
	}
	while(carry > 0) {
		res.digits.emplace(res.digits.begin(), carry%10);
		carry /= 10;
	}
	return res;
}

Bigint Bigint::operator-(Bigint b) {
	Bigint res;
	int alen = digits.size();
	int blen = b.digits.size();
	if(*this < b) {
		return BZero;
	}
	int borrow = 0;
	int zeros = 0;
	while(alen > 0 && blen > 0) {
		int d = digits[--alen]-b.digits[--blen]-borrow;
		borrow = 0;
		if(d < 0) {
			d += 10;
			borrow = 1;
		}
		if(d == 0) {
			++zeros;
		} else {
			while(zeros--) {
				res.digits.emplace(res.digits.begin(), 0);
			}
			zeros = 0;
			res.digits.emplace(res.digits.begin(), d);
		}
	}
	while(alen > 0) {
		int d = digits[--alen]-borrow;
		borrow = 0;
		if(d < 0) {
			d += 10;
			borrow = 1;
		}
		if(d == 0) {
			++zeros;
		} else {
			while(zeros--) {
				res.digits.emplace(res.digits.begin(), 0);
			}
			zeros = 0;
			res.digits.emplace(res.digits.begin(), d);
		}
	}
	if(res.digits.size() == 0) {
		return BZero;
	}
	return res;
}

// Helper procedure to multiple a Bigint by an integer.  This could be just a single
// digit, but in fact it will sometimes be 10 in my code.  We multiple all the digits
// first, then sweep from low to high digit applying the carries.
Bigint Bigint::operator*(int d) {
	if(d == 0) {
		return BZero;
	}
	if(d == 1) {
		return *this;
	}
	Bigint res;
	int alen = digits.size();
	int aindex = 0;
	while(alen--) {
		res.digits.push_back(digits[aindex++] * d);
	}
	int carry = 0;
	while(aindex-- > 0) {
		carry += res.digits[aindex];
		res.digits[aindex] = carry%10;
		carry /= 10;
    }
	while(carry > 0) {
		res.digits.emplace(res.digits.begin(), carry%10);
		carry /= 10;
	}
	return res;
}

Bigint Bigint::operator*(Bigint b) {
	int blen = b.digits.size();
	Bigint tmp = *this;
	Bigint res = BZero;
	while(blen > 0) {
		int d = b.digits[--blen];
		if(d == 1) {
			res = res + tmp;
		} else if(d != 0) {
			res = res + tmp*d;
		}
		if(blen > 0) {
			tmp = tmp*10;
		}
	}
	return res;
}

Bigint Bigint::operator/(Bigint b) {
	if(b > *this) {
		return BZero;
	}
	if(b == *this) {
		return BOne;
	}
	if(b == BZero) {
		std::cout << "Error: Divide by 0" << std::endl;
		exit(1);
	}
	Bigint res;
	Bigint tmp;
	int alen = digits.size();
	int blen = b.digits.size();
	int aindex = 0;
	bool placed_first = false;
	while(aindex < blen) {
		int d = digits[aindex++];
		if(d != 0 || placed_first) {
			tmp.digits.push_back(d);
			placed_first = true;
		}
	}
	if(!placed_first) {
		tmp = BZero;
	}
	bool first = true;
	do {
		int d = 0;
		if(b > tmp && aindex < alen) {
			d = digits[aindex++];
			if(d != 0 || tmp != BZero) {
				if(tmp == BZero) {
					tmp.digits[0] = d;	
				} else {
					tmp.digits.push_back(d);
				}
			}
		}
		d = 0;
		while(b <= tmp) {
			++d;
			tmp = tmp-b;
		}
		if(d != 0 || !first) {
			first = false;
			res.digits.push_back(d);
		}
	}
	while(aindex < alen);
	if(res.digits.size() == 0) {
		return BZero;
	}
	return res;
}

Bigint Bigint::operator%(Bigint b) {
	return *this - (*this/b)*b;
}

Bigint Bigint::expmod(Bigint exp, Bigint mod) {
	if(exp == BZero) {
		return BOne;
	}
	Bigint two = Bigint(2);
	Bigint res = BOne;
	Bigint tmp = *this;
	while(exp > 0) {
		if(exp % two == BOne) {
			res = res*tmp;
			res = res % mod;
		}
		tmp = tmp*tmp % mod;
		exp = exp/two;

	}
	return res;
}

Bigint Bigint::gcd(Bigint b) {
	if (b == BZero)
		return *this;
	return b.gcd(*this % b);
}

Bigint Bigint::encrypt(std::string rsa_n, std::string rsa_e) {
	return expmod(Bigint(rsa_e), Bigint(rsa_n)).to_string();
}

Bigint Bigint::decrypt(std::string rsa_n, std::string rsa_d) {
	return expmod(Bigint(rsa_d), Bigint(rsa_n));
}
