#pragma once

#include <iostream>
#include <chrono>

struct Date {

 private:

  std::chrono::year_month_day date_;

 public:

  Date() = default;
  Date(int year, int month, int day);

  [[nodiscard]] inline int GetYear() const { return static_cast<int>(date_.year()); }
  [[nodiscard]] inline int GetMonth() const { return static_cast<int>(date_.month().operator unsigned int()); }
  [[nodiscard]] inline int GetDay() const { return static_cast<int>(date_.day().operator unsigned int()); }

  Date& operator++();
  int64_t operator-(const Date& date) const;
  Date& operator+=(const Date& date);
  Date operator+(const Date& date) const;

  Date& operator=(const Date&) = default;
  Date& operator=(const std::chrono::year_month_day&);
  bool operator==(const Date&) const;
  bool operator!=(const Date&) const;
  std::strong_ordering operator<=>(const Date& date) const;

  static std::string StringDate(const Date&);

  friend std::ostream& operator<<(std::ostream&, const Date&);

};