#ifndef BANK_SYSTEM_ACCOUNT_ACCOUNTFABRIC_H_
#define BANK_SYSTEM_ACCOUNT_ACCOUNTFABRIC_H_


#include "Account.h"
#include "CreditAccount.h"
#include "DebitAccount.h"
#include "DepositeAccount.h"

class AccountFabric {

 public:

  AccountFabric() {}
  virtual Account* MakeAccount(size_t id, int64_t money) = 0;

};


class CreditFabric : public AccountFabric {

  int64_t credit_limit_;
  int64_t bank_fee_;

 public:

  CreditFabric(int64_t credit_limit, int64_t bank_fee)
        : credit_limit_{credit_limit}, bank_fee_{bank_fee}
  {}
  Account* MakeAccount(size_t id, int64_t money) override {
    return new CreditAccount(id, money, credit_limit_, bank_fee_);
  }

};


class DebitFabric : public AccountFabric {

 public:

  DebitFabric() {}
  Account* MakeAccount(size_t id, int64_t money) override {
    return new DebitAccount(id, money);
  }

};


class DepositeFabric : public AccountFabric {

  Date finish_;

 public:

  DepositeFabric(const Date& finish) : finish_{finish} {}
  Account* MakeAccount(size_t id, int64_t money) {
    return new DepositeAccount(id, money, finish_);
  }

};


#endif //BANK_SYSTEM_ACCOUNT_ACCOUNTFABRIC_H_
