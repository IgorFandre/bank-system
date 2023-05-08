#ifndef BANK_SYSTEM_ACCOUNT_CREDITACCOUNT_H_
#define BANK_SYSTEM_ACCOUNT_CREDITACCOUNT_H_


#include "Account.h"

class CreditAccount : public Account {

  int64_t credit_limit_;
  int64_t bank_fee_;

 public:

  CreditAccount(size_t id, int64_t money = 0, int64_t limit = 0, int64_t fee = 0)
        : Account(id, money), credit_limit_{limit}, bank_fee_{fee}
  {}

  void Update() override {
    if (account_money_ < 0 && system_date != last_usage_date_) {
      account_money_ -= bank_fee_ * (system_date - last_usage_date_);
    }
    Account::Update();
  }

  bool Transaction(int64_t money) override {
    Update();
    if (account_money_ + money < credit_limit_) {
      return false;
    }
    account_money_ += money;
    return true;
  }

};


#endif //BANK_SYSTEM_ACCOUNT_CREDITACCOUNT_H_
