#ifndef BANK_SYSTEM_ACCOUNT_ACCOUNT_H_
#define BANK_SYSTEM_ACCOUNT_ACCOUNT_H_


#include <iostream>

struct Date {

 private:

  static constexpr int MONTH = 30;
  static constexpr int YEAR = 12;

  int year_ = 0;
  int month_ = 1;
  int day_ = 0;

 public:

  Date() = default;
  Date(int year, int month, int day)
        : year_{year}, month_{month}, day_{day} {

    month_ += day_ / (MONTH + 1);
    day_ %= (MONTH + 1) + 1;

    year_ += month_ / (YEAR + 1);
    (month_ %= (YEAR + 1)) += 1;

    assert(year_ >= 0 && month_ >= 0 && day_ >= 0);
  }

  int GetYear() const { return year_; }
  int GetMonth() const { return month_; }
  int GetDay() const { return day_; }

  Date& operator++() {
    ++day_;
    if (day_ > MONTH) {
      day_ = 1;
      ++month_;
    }
    if (month_ > YEAR) {
      month_ = 1;
      ++year_;
    }
    return *this;
  }

  int64_t operator-(const Date& date) const {
    return (year_ - date.year_) * MONTH * YEAR
            + (month_ - date.month_) * MONTH + day_ - date.day_;
  }

  Date& operator+=(const Date& date) {
    day_ += date.day_;

    month_ += date.month_ + day_ / MONTH;
    day_ %= MONTH;

    year_ += date.year_ + month_ / YEAR;
    month_ %= YEAR;

    return *this;
  }

  Date operator+(const Date& date) const {
    Date copy = *this;
    copy += date;
    return copy;
  }

  Date& operator=(const Date&) = default;
  bool operator==(const Date&) const = default;
  bool operator!=(const Date&) const = default;
  auto operator<=>(const Date& date) const {
    if (year_ != date.year_) {
      return (year_ <=> date.year_);
    }
    if (month_ != date.month_) {
      return month_ <=> date.month_;
    }
    return day_ <=> date.day_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Date& d) {
    return (os << d.year_ << " " << d.month_ << " " << d.day_);
  }

};

Date system_date{};


class Account {

 protected:

  size_t account_id_;
  int64_t account_money_;
  Date open_date_;
  Date last_usage_date_;

 public:

  explicit Account(size_t id, int64_t money = 0)
        : account_id_{id}, account_money_{money}, open_date_{system_date}, last_usage_date_{system_date}
  {}

  virtual void Update() {
    last_usage_date_ = system_date;
  }

  virtual bool Transaction(int64_t money) {
    Update();
    if (account_money_ + money < 0) {
      return false;
    }
    account_money_ += money;
    return true;
  }

  size_t GetAccountId() const {
    return account_id_;
  }

  int64_t GetBalance() const {
    return account_money_;
  };

};


#endif //BANK_SYSTEM_ACCOUNT_ACCOUNT_H_
