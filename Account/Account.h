#pragma once

#include <iostream>
#include <memory>

#include "../BigInteger/biginteger.h"
#include "../Date/Date.h"

class Account {
 public:
  enum class Type {
    Empty = 0,
    Credit,
    Deposit,
    Debit,
  };

  explicit Account(size_t id, const BigInteger& money, Type type, Date open_date, Date last_date);
  Account(const Account&) = default;
  virtual ~Account() = default;

  virtual void Update(const Date& system_date);
  virtual bool Transaction(const BigInteger& money, const Date& system_date);

  [[nodiscard]] size_t GetAccountId() const;
  [[nodiscard]] const BigInteger& GetBalance() const;
  [[nodiscard]] Date GetOpenDate() const;
  [[nodiscard]] Date GetLastUsageDate() const;
  [[nodiscard]] Type GetType() const;

  [[nodiscard]] virtual std::shared_ptr<Account> DeepCopy() const = 0;

  friend bool operator==(const Account&, const Account&) = default;

 protected:
  size_t account_id_;
  BigInteger account_money_;
  Date open_date_;
  Date last_usage_date_;
  Type type_;
};