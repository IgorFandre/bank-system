#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../../../BigInteger/biginteger.h"

TEST(TEST_BIGINT, hard_test) {
  BigInteger b, k;
  b = 0, k = 1234567;
  std::ostringstream oss;
  oss << b << ' ' << k;
  ASSERT_EQ(oss.str(), "0 1234567");

  BigInteger a = b;
  a = -a;
  std::string testString = a.toString() + " " + (-k).toString();
  ASSERT_EQ(testString, "0 -1234567");

  a = 999, b = 1000;
  a = a += a;
  testString = a.toString();
  ASSERT_EQ(testString, "1998");

  ++a %= a /= a *= a -= b++;
  std::ostringstream oss2;
  oss2 << 5 + a << ' ' << 1 - b;
  ASSERT_EQ(oss2.str(), "5 -1000");

  std::ostringstream oss3;
  oss3 << (a = (bool(a) ? -1 : -2));
  ASSERT_EQ(oss3.str(), "-2");

  std::istringstream iss("26 5");
  iss >> a >> b;
  std::ostringstream oss4;
  oss4 << b << ' ' << a << ' ';
  ASSERT_EQ(oss4.str(), "5 26 ");

  oss4 << a + b << ' ' << a - b << ' ' << a * b << ' ' << a / b << ' ' << a % b
       << '\n';
  oss4 << b + a << ' ' << b - a << ' ' << b * a << ' ' << b / a << ' ' << b % a;
  ASSERT_EQ(oss4.str(), "5 26 31 21 130 5 1\n31 -21 130 0 5");

  std::vector<BigInteger> v;
  for (size_t i = 0; i < 1000; ++i) {
    v.push_back(1000 - i);
  }
  std::sort(v.begin(), v.end());

  std::ostringstream oss5;
  oss5 << v[0] << ' ' << v[500] << ' ' << v[999] << ' ';

  oss5 << (a != b) << ' ' << (a < b) << ' ' << (a > b) << ' ';
  oss5 << (a <= b) << ' ' << (a >= b);
  ASSERT_EQ(oss5.str(), "1 501 1000 1 0 1 0 1") ;

  std::istringstream iss2("1000000000000000000000000000000000 -1000000");
  iss2 >> a >> b;
  std::ostringstream oss6;
  oss6 << b << a;
  ASSERT_EQ(oss6.str(), "-10000001000000000000000000000000000000000");

  std::istringstream iss3(
      "453234523460009834520987234598234502345987029345436345634563 "
      "234523452034623049872345234520983475325345234232578");
  BigInteger c, d;
  iss3 >> c >> d;

  std::istringstream iss4(
      "-23534576554950000000000000009999990000999900000 "
      "8888888888884444444444433333333333332222222222222111112222777777777");
  BigInteger e, f;
  iss4 >> e >> f;

  std::ostringstream oss7;

  oss7 << a + b << ' ' << c + d << ' ' << e + f;

  ASSERT_EQ(oss7.str(),
      "999999999999999999999999999000000 "
      "453234523694533286555610284470579736866970504670781579867141 "
      "8888888888884444444420898756778383332222222222212111122221777877777");

  std::ostringstream oss8;
  oss8 << a - b << ' ' << c - d << ' ' << e - f;
  ASSERT_EQ(oss8.str(),
      "1000000000000000000000000001000000 "
      "453234523225486382486364184725889267825003554020091111401985 "
      "-8888888888884444444467967909888283332222222222232111102223777677777");

  std::ostringstream oss9;
  oss9 << a * b << ' ' << c * d << ' ' << e * f;
  ASSERT_EQ(oss9.str(),
      "-1000000000000000000000000000000000000000 "
      "106294125023108851855435239407742287054686671354449187194200406809777590"
      "661604024572718537860109672117737393414 "
      "-20919623604389540188197773859359374498269402609449282996221204314912334"
      "5328234038901116544451103777729999222300000");

  std::ostringstream oss10;
  oss10 << a / b << ' ' << c / d << ' ' << e / f;
  ASSERT_EQ(oss10.str(), "-1000000000000000000000000000 1932576548 0");

  std::ostringstream oss11;
  oss11 << a % b << ' ' << c % d << ' ' << e % f;
  ASSERT_EQ(oss11.str(),
      "0 101894444317458440603421824036688159663989325253819 "
      "-23534576554950000000000000009999990000999900000");
}

TEST(TEST_BIGINT, random_test) {
  std::random_device dev;
  std::mt19937 rnd(dev());
  std::uniform_int_distribution<std::mt19937::result_type> number(1,999'999);

  size_t count = 3000;

  for (size_t i = 0; i < count; ++i) {
    int64_t first = number(rnd);
    int64_t second = number(rnd);
    first *= (number(rnd) % 2 == 0 ? -1 : 1);
    second *= (number(rnd) % 2 == 0 ? -1 : 1);
    BigInteger a(first);
    BigInteger b(second);
    ASSERT_TRUE((first + second) == (a + b));
    ASSERT_TRUE((-first + second) == (-a + b));
    ASSERT_TRUE((first + (-second)) == (a + (-b)));
    ASSERT_TRUE((first - second) == (a - b));
    ASSERT_TRUE((-first - second) == (-a - b));
    ASSERT_TRUE((first < 0) == (a < 0));
    ASSERT_TRUE((first > 0) == (a > 0));
    ASSERT_TRUE((first >= 0) == (a >= 0));
    ASSERT_TRUE((first <= 0) == (a <= 0));
    ASSERT_TRUE((first > second) == (a > b));
    ASSERT_TRUE((first >= second) == (a >= b));
    ASSERT_TRUE((first == second) == (a == b));
    ASSERT_TRUE((first < second) == (a < b));
    ASSERT_TRUE((first <= second) == (a <= b));
    ASSERT_TRUE((first * second) == (a * b));
    ASSERT_TRUE((first / second) == (a / b));
    ASSERT_TRUE((first % second) == (a % b));
  }
}

TEST(TEST_BIGINT, long_divide_test) {
  std::random_device dev;
  std::mt19937 rnd(dev());
  std::uniform_int_distribution<std::mt19937::result_type> number(1,9); // distribution in range [1, 9]

  std::string first{};
  std::string second{};
  for (size_t i = 0; i < 30'000; ++i) {
    first += static_cast<char>('0' + number(rnd));
  }
  for (size_t j = 0; j < 5'000; ++j) {
    second += static_cast<char>('0' + number(rnd));
  }
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  BigInteger(first) / BigInteger(second);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [µs]" << std::endl;
  ASSERT_TRUE(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() < 10'000);
}