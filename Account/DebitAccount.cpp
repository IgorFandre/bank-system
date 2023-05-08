#include "DebitAccount.h"
#include "Account.h"

DebitAccount::DebitAccount(size_t id, const BigInteger &money, Date open_date,
                           Date last_date)
    : Account(id, money, Account::Type::Debit, open_date, last_date) {}

std::shared_ptr<Account> DebitAccount::DeepCopy() const {
  return std::shared_ptr<Account>(
      new DebitAccount(Account::account_id_, Account::account_money_,
                          open_date_, last_usage_date_));
}