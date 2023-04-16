#pragma once

#include "Account.h"
#include "CreditAccount.h"
#include "DebitAccount.h"
#include "DepositAccount.h"

class AccountFabric {

 public:

  AccountFabric() = default;
  virtual ~AccountFabric() = default;
  virtual Account* MakeAccount(size_t id, int64_t money, const Date& system_date) = 0;

};


class CreditFabric : public AccountFabric {

  int64_t credit_limit_;
  int64_t bank_fee_;

 public:

  CreditFabric(int64_t credit_limit, int64_t bank_fee);
  ~CreditFabric() override = default;
  Account* MakeAccount(size_t id, int64_t money, const Date& system_date) override;

};


class DebitFabric : public AccountFabric {

 public:

  DebitFabric() = default;
  ~DebitFabric() override = default;
  Account* MakeAccount(size_t id, int64_t money, const Date& system_date) override;

};


class DepositFabric : public AccountFabric {

  Date finish_;

 public:

  explicit DepositFabric(const Date& finish);
  ~DepositFabric() override = default;
  Account* MakeAccount(size_t id, int64_t money, const Date& system_date) override;

};