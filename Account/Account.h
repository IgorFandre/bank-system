#pragma once

#include <iostream>

#include "../Date/Date.h"

class Account {
 public:
  enum class Type {
    Empty = 0,
    Credit,
    Deposit,
    Debit,
  };

  explicit Account(size_t id, int64_t money, Type type, Date open_date, Date last_date);
  Account(const Account&) = default;
  virtual ~Account() = default;

  virtual void Update(const Date& system_date);
  virtual bool Transaction(int64_t money, const Date& system_date);

  [[nodiscard]] size_t GetAccountId() const;
  [[nodiscard]] int64_t GetBalance() const;
  [[nodiscard]] Date GetOpenDate() const;
  [[nodiscard]] Date GetLastUsageDate() const;
  [[nodiscard]] Type GetType() const;

  [[nodiscard]] virtual Account* DeepCopy() const = 0;

  friend bool operator==(const Account&, const Account&) = default;

 protected:
  size_t account_id_;
  int64_t account_money_;
  Date open_date_;
  Date last_usage_date_;
  Type type_;
};