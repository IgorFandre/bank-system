#pragma once

#include "Account.h"

class DepositAccount : public Account {

  Date finish_date_;
  bool reduce_money_;

 public:

  DepositAccount(size_t id, int64_t money, Date finish, Date open_date, Date last_date);
  ~DepositAccount() override = default;

  void Update(const Date& system_date) override;
  bool Transaction(int64_t money, const Date& system_date) override;
  Account* DeepCopy() override;

  [[nodiscard]] inline Date GetFinishDate() const {
    return finish_date_;
  }

  [[nodiscard]] inline bool GetReduceStatus() const {
    return reduce_money_;
  }

};