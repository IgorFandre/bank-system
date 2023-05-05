#pragma once

#include "Account.h"
#include "CreditAccount.h"
#include "DebitAccount.h"
#include "DepositAccount.h"

class AccountFabric {
 public:
  AccountFabric() = default;
  virtual ~AccountFabric() = default;
  virtual std::shared_ptr<Account> MakeAccount(size_t id, int64_t money, const Date& system_date) = 0;

};


class CreditFabric : public AccountFabric {
 public:
  CreditFabric(int64_t credit_limit, int64_t bank_fee);
  ~CreditFabric() override = default;
  std::shared_ptr<Account> MakeAccount(size_t id, int64_t money, const Date& system_date) override;

 private:
  int64_t credit_limit_;
  int64_t bank_fee_;

};


class DebitFabric : public AccountFabric {
 public:
  DebitFabric() = default;
  ~DebitFabric() override = default;
  std::shared_ptr<Account> MakeAccount(size_t id, int64_t money, const Date& system_date) override;

};


class DepositFabric : public AccountFabric {
 public:
  explicit DepositFabric(const Date& finish);
  ~DepositFabric() override = default;
  std::shared_ptr<Account> MakeAccount(size_t id, int64_t money, const Date& system_date) override;

 private:
  Date finish_;

};