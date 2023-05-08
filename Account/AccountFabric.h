#pragma once

#include "Account.h"
#include "CreditAccount.h"
#include "DebitAccount.h"
#include "DepositAccount.h"

class AccountFabric {
public:
  AccountFabric() = default;
  virtual ~AccountFabric() = default;
  virtual std::shared_ptr<Account>
  MakeAccount(size_t id, const BigInteger &money, const Date &system_date) = 0;
};

class CreditFabric : public AccountFabric {
public:
  CreditFabric(const BigInteger &credit_limit, const BigInteger &bank_fee);
  ~CreditFabric() override = default;
  std::shared_ptr<Account> MakeAccount(size_t id,
                                       const BigInteger &money,
                                       const Date &system_date) override;

private:
  const BigInteger &credit_limit_;
  const BigInteger &bank_fee_;
};

class DebitFabric : public AccountFabric {
public:
  DebitFabric() = default;
  ~DebitFabric() override = default;
  std::shared_ptr<Account> MakeAccount(size_t id,
                                       const BigInteger &money,
                                       const Date &system_date) override;
};

class DepositFabric : public AccountFabric {
public:
  explicit DepositFabric(const Date &finish);
  ~DepositFabric() override = default;
  std::shared_ptr<Account> MakeAccount(size_t id,
                                       const BigInteger &money,
                                       const Date &system_date) override;

private:
  Date finish_;
};