#include "biginteger.h"

bool BigInteger::AbsLess(const BigInteger& b) const {
  if (sign_ == Sign::Zero) {
    if (b.sign_ == Sign::Zero) {
      return false;
    }
    return true;
  }
  if (integer_.size() > b.integer_.size()) {
    return false;
  }
  if (integer_.size() < b.integer_.size()) {
    return true;
  }
  for (size_t i = integer_.size(); i > 0; --i) {
    if (integer_[i - 1] < b.integer_[i - 1]) {
      return true;
    }
    if (integer_[i - 1] > b.integer_[i - 1]) {
      return false;
    }
  }
  return false;
}

bool operator<(const BigInteger& b1, const BigInteger& b2) {
  if (static_cast<int>(b1.GetSign()) < static_cast<int>(b2.GetSign())) {
    return true;
  }
  if (static_cast<int>(b1.GetSign()) > static_cast<int>(b2.GetSign())) {
    return false;
  }
  if (b1.GetSign() == BigInteger::Sign::Minus) {
    return b2.AbsLess(b1);
  }
  return b1.AbsLess(b2);
}
bool operator!=(const BigInteger& a, const BigInteger& b) {
  return (a < b) || (b < a);
}
bool operator==(const BigInteger& a, const BigInteger& b) {
  return !(a != b);
}
bool operator<=(const BigInteger& a, const BigInteger& b) {
  return !(b < a);
}
bool operator>(const BigInteger& a, const BigInteger& b) {
  return b < a;
}
bool operator>=(const BigInteger& a, const BigInteger& b) {
  return !(a < b);
}

void BigInteger::AddZeros(size_t nulls) {
  EraseLeadZeros();
  std::reverse(integer_.begin(), integer_.end());
  for (size_t i = 0; i < nulls; ++i) {
    integer_.push_back(0);
  }
  std::reverse(integer_.begin(), integer_.end());
}

void BigInteger::DeleteZeros(size_t nulls) {
  EraseLeadZeros();
  std::reverse(integer_.begin(), integer_.end());
  for (size_t i = 0; i < nulls; ++i) {
    integer_.pop_back();
  }
  std::reverse(integer_.begin(), integer_.end());
}

void BigInteger::Add(const BigInteger& b) {
  int64_t move = 0;
  std::vector<int64_t> new_int;
  size_t n = (integer_.size() > b.integer_.size()) ? integer_.size() : b.integer_.size();
  for (size_t i = 0; i < n; ++i) {
    if (i < integer_.size()) {
      move += integer_[i];
    }
    if (i < b.integer_.size()) {
      move += b.integer_[i];
    }
    new_int.push_back(move % kBase);
    move /= kBase;
  }
  if (move != 0) {
    new_int.push_back(move);
  }
  integer_ = new_int;
}

void BigInteger::Substract(const BigInteger& b) {
  int64_t move = 0;
  std::vector<int64_t> new_int;
  for (size_t i = 0; i < integer_.size(); ++i) {
    if (i < integer_.size()) {
      move += integer_[i];
    }
    if (i < b.integer_.size()) {
      move -= b.integer_[i];
    }
    if (move < 0) {
      new_int.push_back(move + kBase);
      move = -1;
    } else {
      new_int.push_back(move % kBase);
      move /= kBase;
    }
  }
  integer_ = new_int;
  EraseLeadZeros();
}

void BigInteger::Divide(BigInteger b, bool div = true) {
  Sign save_sign = sign_;
  if (b.sign_ == Sign::Minus) {
    b.sign_ = Sign::Plus;
  }
  BigInteger numerator = integer_[integer_.size() - 1];
  BigInteger result = 0;
  for (size_t i = integer_.size(); i > 0; --i) {
    result.integer_.insert(result.integer_.begin(), 0);
    if (numerator >= b) {
      int64_t ans;
      int64_t r = kBase - 1;
      int64_t l = 0;
      while (l <= r) {
        ans = (l + r) / 2;
        if (ans * b <= numerator) {
          if ((ans + 1) * b > numerator) {
            numerator -= ans * b;
            result += ans;
            break;
          }
          l = ans + 1;
        } else {
          r = ans - 1;
        }
      }
    }
    if (i > 1) {
      numerator.AddZeros(1);
      numerator += integer_[i - 2];
      numerator.EraseLeadZeros();
    }
  }
  if (div) {
    integer_ = result.integer_;
  } else {
    integer_ = numerator.integer_;
  }
  sign_ = save_sign;
  EraseLeadZeros();
}

void BigInteger::EraseLeadZeros() {
  while (!integer_.empty() && integer_.back() == 0) {
    integer_.pop_back();
  }
  if (integer_.empty()) {
    sign_ = Sign::Zero;
  }
}

void BigInteger::Abs() {
  sign_ = Sign(abs(int(sign_)));
}

void BigInteger::Clear() {
  sign_ = Sign::Zero;
  integer_.clear();
}

BigInteger::BigInteger(std::string str) : integer_() {
  if (str.empty()) {
    sign_ = Sign::Zero;
    return;
  }
  if (str[0] == '-') {
    sign_ = Sign::Minus;
    str.erase(str.begin());
  } else {
    sign_ = Sign::Plus;
  }
  int idx = static_cast<int>(str.size());
  while (idx - kBaseSymbols > 0) {
    integer_.push_back(stoi(str.substr(idx - kBaseSymbols, kBaseSymbols)));
    idx -= kBaseSymbols;
  }
  if (stoi(str.substr(0, idx)) != 0) {
    integer_.push_back(
        stoi(str.substr(0, idx)));
  }
  EraseLeadZeros();
}
BigInteger::BigInteger(int64_t n) {
  if (n < 0) {
    sign_ = Sign::Minus;
  } else if (n > 0) {
    sign_ = Sign::Plus;
  } else {
    sign_ = Sign::Zero;
  }
  if (n < 0) {
    n *= -1;
  }
  while (n != 0) {
    integer_.push_back(n % kBase);
    n /= kBase;
  }
}
BigInteger::BigInteger(size_t n, bool sign) {
  if (n == 0) {
    sign_ = Sign::Zero;
  } else if (sign) {
    sign_ = Sign::Plus;
  } else {
    sign_ = Sign::Minus;
  }
  do {
    integer_.push_back(static_cast<int64_t>(n) % kBase);
    n /= kBase;
  } while (n != 0);
}
BigInteger::BigInteger(size_t n, char sign) : integer_() {
  if (n == 0) {
    sign_ = Sign::Zero;
  } else if (sign == '+') {
    sign_ = Sign::Plus;
  } else {
    sign_ = Sign::Minus;
  }
  do {
    integer_.push_back(static_cast<int64_t>(n) % kBase);
    n /= kBase;
  } while (n != 0);
}
BigInteger::BigInteger(const BigInteger& b) {
  integer_ = b.integer_;
  sign_ = b.sign_;
}
BigInteger::BigInteger(const std::vector<int64_t>& numbers, Sign sign) {
  sign_ = sign;
  integer_ = numbers;
}
BigInteger::operator int() const {
  if (sign_ == Sign::Zero) {
    return 0;
  }
  int bigint = static_cast<int>(integer_[integer_.size() - 1]);
  for (size_t i = integer_.size() - 2; i > 0; --i) {
    bigint *= static_cast<int>(kBase);
    bigint += static_cast<int>(integer_[i]);
  }
  if (sign_ == Sign::Minus) {
    bigint *= -1;
  }
  return bigint;
}
BigInteger::operator double() const {
  if (sign_ == Sign::Zero) {
    return 0;
  }
  auto bigint = static_cast<double>(integer_[integer_.size() - 1]);
  for (size_t i = integer_.size() - 2; i > 0; --i) {
    bigint *= static_cast<double>(kBase);
    bigint += static_cast<double>(integer_[i]);
  }
  if (sign_ == Sign::Minus) {
    bigint *= -1;
  }
  return bigint;
}
BigInteger::operator bool() const {
  return static_cast<bool>(sign_);
}
BigInteger& BigInteger::operator+=(const BigInteger& b) {
  if (b.sign_ == Sign::Zero) {
    return *this;
  }
  if (sign_ == Sign::Zero) {
    *this = b;
    return *this;
  }
  if (sign_ == b.sign_) {
    Add(b);
  } else {
    if (!AbsLess(b)) {
      Substract(b);
    } else {
      BigInteger new_this = b;
      new_this.Substract(*this);
      *this = new_this;
    }
  }
  return *this;
}
BigInteger& BigInteger::operator-=(const BigInteger& b) {
  *this += (-b);
  return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger& b) {
  if (b.sign_ == Sign::Zero || sign_ == Sign::Zero) {
    Clear();
    return *this;
  }
  if (b.integer_.size() == 1 && b.integer_[0] == 1) {
    sign_ = Sign(static_cast<int>(sign_) * static_cast<int>(b.sign_));
    return *this;
  }
  BigInteger multiply = 0;
  size_t size = integer_.size() + b.integer_.size();
  for (size_t i = 0; i < size + 2; ++i) {
    multiply.integer_.push_back(0);
  }
  for (size_t i = 0; i < integer_.size(); ++i) {
    for (size_t j = 0; j < b.integer_.size(); ++j) {
      multiply.integer_[i + j] += (integer_[i] * b.integer_[j]) % kBase;
      multiply.integer_[i + j + 1] += (integer_[i] * b.integer_[j]) / kBase;
      if (multiply.integer_[i + j] >= kBase) {
        multiply.integer_[i + j + 1] += multiply.integer_[i + j] / kBase;
        multiply.integer_[i + j] = multiply.integer_[i + j] % kBase;
      }
      if (multiply.integer_[i + j + 1] >= kBase) {
        multiply.integer_[i + j + 2] += multiply.integer_[i + j + 1] / kBase;
        multiply.integer_[i + j + 1] = multiply.integer_[i + j + 1] % kBase;
      }
    }
  }
  integer_ = multiply.integer_;
  sign_ = Sign(static_cast<int>(sign_) * static_cast<int>(b.sign_));
  EraseLeadZeros();
  return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger& b) {
  sign_ = Sign(static_cast<int>(sign_) * static_cast<int>(b.sign_));
  Divide(b, true);
  return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& b) {
  Divide(b, false);
  return *this;
}
BigInteger BigInteger::operator-() const {
  BigInteger copy = *this;
  copy.sign_ = Sign(static_cast<int>(sign_) * (-1));
  return copy;
}
BigInteger& BigInteger::operator++() {
  *this += 1;
  return *this;
}
BigInteger BigInteger::operator++(int) {
  BigInteger copy = *this;
  *this += 1;
  return copy;
}
BigInteger& BigInteger::operator--() {
  *this -= 1;
  return *this;
}
BigInteger BigInteger::operator--(int) {
  BigInteger copy = *this;
  *this -= 1;
  return copy;
}
BigInteger operator*(BigInteger b1, const BigInteger& b2) {
  return (b1 *= b2);
}
BigInteger operator+(BigInteger b1, const BigInteger& b2) {
  return (b1 += b2);
}
BigInteger operator/(BigInteger b1, const BigInteger& b2) {
  return (b1 /= b2);
}
BigInteger operator-(BigInteger b1, const BigInteger& b2) {
  return (b1 -= b2);
}
BigInteger operator%(BigInteger b1, const BigInteger& b2) {
  return (b1 %= b2);
}
std::string BigInteger::toString() const {
  std::string res;
  if (sign_ == BigInteger::Sign::Zero || integer_.empty()) {
    return "0";
  }
  if (sign_ == BigInteger::Sign::Minus) {
    res = "-";
  }
  res += std::to_string(integer_[integer_.size() - 1]);
  for (size_t i = integer_.size() - 1; i > 0; --i) {
    std::string num = std::to_string(integer_[i - 1]);
    res += std::string(kBaseSymbols - num.size(), '0') + num;
  }
  return res;
}
std::ostream& operator<<(std::ostream& out, const BigInteger& b) {
  out << b.toString();
  return out;
}
std::istream& operator>>(std::istream& in, BigInteger& b) {
  std::string s;
  in >> s;
  b = BigInteger(s);
  return in;
}
BigInteger operator ""_bi(unsigned long long number) {
  return {number, true};
}
BigInteger operator ""_bi(const char* str) {
  return BigInteger(std::string(str));
}