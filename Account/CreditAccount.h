#pragma once

#include "Account.h"

class CreditAccount : public Account {

  int64_t credit_limit_;
  int64_t bank_fee_;

 public:

  explicit CreditAccount(size_t id, int64_t money, int64_t limit, int64_t fee, Date open_date, Date last_date);
  ~CreditAccount() override = default;

  void Update(const Date& system_date) override;
  bool Transaction(int64_t money, const Date& system_date) override;

  [[nodiscard]] int64_t GetCreditLimit() const;
  [[nodiscard]] int64_t GetBankFee() const;

  [[nodiscard]] Account* DeepCopy() const override;

  friend bool operator==(const CreditAccount&, const CreditAccount&) = default;
};