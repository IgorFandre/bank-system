#pragma once

#include "Account.h"

class CreditAccount : public Account {
public:
  CreditAccount(size_t id,
                const BigInteger &money,
                const BigInteger &limit,
                const BigInteger &fee,
                Date open_date,
                Date last_date);
  ~CreditAccount() override = default;

  void Update(const Date &system_date) override;
  bool Transaction(const BigInteger &money, const Date &system_date) override;

  [[nodiscard]] const BigInteger &GetCreditLimit() const;
  [[nodiscard]] const BigInteger &GetBankFee() const;

  [[nodiscard]] std::shared_ptr<Account> DeepCopy() const override;

  friend bool operator==(const CreditAccount &,
                         const CreditAccount &) = default;

private:
  BigInteger credit_limit_;
  BigInteger bank_fee_;
};