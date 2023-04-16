#include "Date.h"

Date::Date(int year, int month, int day)
    : date_(std::chrono::year(year), std::chrono::month(month), std::chrono::day(day))
{}

Date& Date::operator++() {
  date_ = std::chrono::year_month_day(date_.year(), date_.month(), date_.day() + std::chrono::days(1));
  return *this;
}

int64_t Date::operator-(const Date& d) const {
  auto x_1 = std::chrono::sys_days(date_);
  auto x_2 = std::chrono::sys_days(d.date_);
  return std::chrono::duration_cast<std::chrono::days>(x_1 - x_2).count();
}

Date& Date::operator+=(const Date& d) {
  date_ = std::chrono::year_month_day(date_.year() + std::chrono::years(d.GetYear()),
                                      date_.month() + std::chrono::months(d.GetMonth()),
                                      date_.day() + std::chrono::days(d.GetDay()));
  return *this;
}

Date& Date::operator=(const std::chrono::year_month_day& d) {
  date_ = d;
  return *this;
}

Date Date::operator+(const Date& date) const {
  Date copy = *this;
  copy += date;
  return copy;
}

bool Date::operator==(const Date& d) const {
  return (date_ == d.date_);
}

bool Date::operator!=(const Date& d) const {
  return (date_ != d.date_);
}

std::strong_ordering Date::operator<=>(const Date& d) const {
  if (GetYear() != d.GetYear()) {
    return (GetYear() <=> d.GetYear());
  }
  if (GetMonth() != d.GetMonth()) {
    return (GetMonth() <=> d.GetMonth());
  }
  return GetDay() <=> d.GetDay();
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
  return (os << d.GetDay() << " " << d.GetMonth() << " " << d.GetYear());
}

std::string Date::StringDate(const Date& d) {
  std::string res = (std::to_string(d.GetDay()).size() == 1 ? "0" : "") + std::to_string(d.GetDay()) + ".";
  res += (std::to_string(d.GetMonth()).size() == 1 ? "0" : "") + std::to_string(d.GetMonth()) + ".";
  res += std::to_string(d.GetYear());
  return res;
}