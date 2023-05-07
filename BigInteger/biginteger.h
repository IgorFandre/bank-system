#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class BigInteger {
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
 public:
  enum class Sign {
    Minus = -1,
    Zero = 0,
    Plus = 1,
  };

  Sign GetSign() const {
    return sign_;
  }

  BigInteger() : sign_{Sign::Zero} {}
  explicit BigInteger(std::string);
  BigInteger(int64_t);
  BigInteger(size_t, bool);
  BigInteger(size_t, char);
  BigInteger(const BigInteger&);
  BigInteger(const std::vector<int64_t>&, Sign);

  explicit operator int() const;
  explicit operator bool() const;
  explicit operator double() const;

  BigInteger operator-() const;

  BigInteger& operator=(const BigInteger&) = default;
  friend bool operator<(const BigInteger&, const BigInteger&);

  BigInteger& operator+=(const BigInteger&);
  BigInteger& operator-=(const BigInteger&);
  BigInteger& operator*=(const BigInteger&);
  BigInteger& operator/=(const BigInteger&);
  BigInteger& operator%=(const BigInteger&);
  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger operator--(int);
  BigInteger& operator--();
  std::string toString() const;
  void Abs();
  void AddZeros(size_t);
  void DeleteZeros(size_t);

  static int GetBaseSymbols() { return kBaseSymbols; }
  static int64_t GetBase() { return kBase; }
 private:
  bool AbsLess(const BigInteger&) const;
  void Clear();
  void Substract(const BigInteger&);
  void Add(const BigInteger&);
  void EraseLeadZeros();
  void Divide(BigInteger, bool);
  static constexpr int64_t kBase = 1e9;
  static constexpr int kBaseSymbols = 9;
  std::vector<int64_t> integer_;
  Sign sign_;
};

BigInteger operator*(BigInteger, const BigInteger&);
BigInteger operator+(BigInteger, const BigInteger&);
BigInteger operator/(BigInteger, const BigInteger&);
BigInteger operator-(BigInteger, const BigInteger&);
BigInteger operator%(BigInteger, const BigInteger&);

bool operator!=(const BigInteger&, const BigInteger&);
bool operator==(const BigInteger&, const BigInteger&);
bool operator>(const BigInteger&, const BigInteger&);
bool operator<=(const BigInteger&, const BigInteger&);
bool operator>=(const BigInteger&, const BigInteger&);

BigInteger operator ""_bi(unsigned long long);
BigInteger operator ""_bi(const char*);

std::istream& operator>>(std::istream&, BigInteger&);

#endif //BIGINTEGER_H_
