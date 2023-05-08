#pragma once

#include "Account.h"

class DepositAccount : public Account {
public:
  DepositAccount(size_t id, const BigInteger &money, Date finish,
                 Date open_date, Date last_date);
  ~DepositAccount() override = default;

  void Update(const Date &system_date) override;
  bool Transaction(const BigInteger &money, const Date &system_date) override;

  [[nodiscard]] std::shared_ptr<Account> DeepCopy() const override;

  [[nodiscard]] inline Date GetFinishDate() const { return finish_date_; }

  [[nodiscard]] inline bool GetReduceStatus() const { return reduce_money_; }

  friend bool operator==(const DepositAccount &,
                         const DepositAccount &) = default;

private:
  Date finish_date_;
  bool reduce_money_;
};