#include "Account.h"

Account::Account(size_t id, const BigInteger &money, Type type, Date open_date,
                 Date last_date)
    : account_id_{id}, account_money_{money}, open_date_{open_date},
      last_usage_date_{last_date}, type_(type) {}

void Account::Update(const Date &system_date) {
  last_usage_date_ = system_date;
}

bool Account::Transaction(const BigInteger &money, const Date &system_date) {
  Update(system_date);
  if (account_money_ + money < 0) {
    return false;
  }
  account_money_ += money;
  return true;
}

size_t Account::GetAccountId() const { return account_id_; }

const BigInteger &Account::GetBalance() const { return account_money_; }

Date Account::GetOpenDate() const { return open_date_; }

Date Account::GetLastUsageDate() const { return last_usage_date_; }

Account::Type Account::GetType() const { return type_; }