#include "DepositAccount.h"
#include "Account.h"

DepositAccount::DepositAccount(size_t id, const BigInteger &money, Date finish,
                               Date open_date, Date last_date)
    : Account(id, money, Account::Type::Deposit, open_date, last_date),
      finish_date_(finish), reduce_money_(last_usage_date_ >= finish_date_) {}

void DepositAccount::Update(const Date &system_date) {
  Account::Update(system_date);
  if (last_usage_date_ >= finish_date_) {
    reduce_money_ = true;
  }
}

bool DepositAccount::Transaction(const BigInteger &money,
                                 const Date &system_date) {
  Update(system_date);
  if (reduce_money_ || money >= 0) {
    return Account::Transaction(money, system_date);
  }
  return false;
}

std::shared_ptr<Account> DepositAccount::DeepCopy() const {
  return std::shared_ptr<Account>(
      new DepositAccount(Account::account_id_, Account::account_money_,
                         finish_date_, open_date_, last_usage_date_));
}