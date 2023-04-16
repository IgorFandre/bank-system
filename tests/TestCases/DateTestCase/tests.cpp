#include <GTest/gtest.h>
#include "../../../Date/DateSetter.h"

TEST(TEST_DATE, date_comparison) {
  ASSERT_EQ(Date(2022, 11, 1), Date(2022, 11, 1));
  ASSERT_EQ(Date(2022, 11, 1) > Date(2022, 10, 31), true);
  ASSERT_EQ(Date(2022, 10, 31) < Date(2022, 11, 1), true);
  ASSERT_EQ(Date(2021, 11, 1) == Date(2022, 11, 1), false);
  ASSERT_EQ(Date(2021, 11, 3) != Date(2021, 11, 3), false);
}

TEST(TEST_DATE, arithmetic_operations) {
  Date first{1, 1, 1};
  ASSERT_EQ(++first, Date(1, 1, 2));

  first = Date{1, 1, 1};
  Date second{1, 2, 1};
  ASSERT_EQ(second - first, 31);

  first = Date{1, 1, 1};
  second = Date{1, 2, 1};
  first += second;
  ASSERT_EQ(first, Date(2, 3, 2));

  first = Date{1, 1, 1};
  second = Date{1, 2, 1};
  ASSERT_EQ(first + second, Date(2, 3, 2));
}

TEST(TEST_DATE, string_date) {
  Date first(1999, 2, 1);
  ASSERT_EQ(Date::StringDate(first), "01.02.1999");

  Date second(2001, 10, 1);
  ASSERT_EQ(Date::StringDate(second), "01.10.2001");

  Date third(2002, 1, 30);
  ASSERT_EQ(Date::StringDate(third), "30.01.2002");

  Date fourth(2003, 11, 12);
  ASSERT_EQ(Date::StringDate(fourth), "12.11.2003");
}

TEST(TEST_DATE, real_date) {
  Date date{};
  DateSetter::StartSession(date);
  ASSERT_EQ(Date::StringDate(date), "16.04.2023"); // Enter current date in format "00.00.0000"
}