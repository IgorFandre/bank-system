#include "CreditAccount.h"
#include "Account.h"

CreditAccount::CreditAccount(size_t id,
                             const BigInteger &money,
                             const BigInteger &limit,
                             const BigInteger &fee,
                             Date open_date,
                             Date last_date)
    : Account(id, money, Account::Type::Credit, open_date, last_date)
    , credit_limit_{limit}
    , bank_fee_{fee} {}

void CreditAccount::Update(const Date &system_date) {
  if (account_money_ < 0 && system_date != last_usage_date_) {
    account_money_ -= bank_fee_ * (system_date - last_usage_date_);
  }
  Account::Update(system_date);
}

bool CreditAccount::Transaction(const BigInteger &money,
                                const Date &system_date) {
  Update(system_date);
  if (account_money_ + money < credit_limit_) {
    return false;
  }
  account_money_ += money;
  return true;
}

const BigInteger &CreditAccount::GetCreditLimit() const {
  return credit_limit_;
}

const BigInteger &CreditAccount::GetBankFee() const { return bank_fee_; }

std::shared_ptr<Account> CreditAccount::DeepCopy() const {
  return std::shared_ptr<Account>(new CreditAccount(Account::account_id_,
                                                    Account::account_money_,
                                                    credit_limit_,
                                                    bank_fee_,
                                                    open_date_,
                                                    last_usage_date_));
}