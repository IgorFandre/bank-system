#ifndef BANK_SYSTEM_ACCOUNT_DEPOSITEACCOUNT_H_
#define BANK_SYSTEM_ACCOUNT_DEPOSITEACCOUNT_H_


#include "Account.h"

class DepositeAccount : public Account {

  Date finish_date_;
  bool reduce_money_;

 public:

  DepositeAccount(size_t id, int64_t money, Date finish)
        : Account(id, money), finish_date_(finish)
  {}

  void Update() override {
    Account::Update();
    if (last_usage_date_ >= finish_date_) {
      reduce_money_ = true;
    }
  }

  bool Transaction(int64_t money) override {
    if (reduce_money_ || money >= 0) {
      return Account::Transaction(money);
    }
    return false;
  }

};


#endif //BANK_SYSTEM_ACCOUNT_DEPOSITEACCOUNT_H_
