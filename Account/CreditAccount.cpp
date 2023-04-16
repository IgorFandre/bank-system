#include "Account.h"
#include "CreditAccount.h"

CreditAccount::CreditAccount(size_t id, int64_t money, int64_t limit, int64_t fee, Date open_date, Date last_date)
    : Account(id, money, Account::Type::Credit, open_date, last_date), credit_limit_{limit}, bank_fee_{fee}
{}

void CreditAccount::Update(const Date& system_date) {
  if (account_money_ < 0 && system_date != last_usage_date_) {
    account_money_ -= bank_fee_ * (system_date - last_usage_date_);
  }
  Account::Update(system_date);
}

bool CreditAccount::Transaction(int64_t money, const Date& system_date) {
  Update(system_date);
  if (account_money_ + money < credit_limit_) {
    return false;
  }
  account_money_ += money;
  return true;
}

int64_t CreditAccount::GetCreditLimit() const {
  return credit_limit_;
}

int64_t CreditAccount::GetBankFee() const {
  return bank_fee_;
}

Account* CreditAccount::DeepCopy() {
  return new CreditAccount(Account::account_id_, Account::account_money_, credit_limit_,
                           bank_fee_, open_date_, last_usage_date_);
}