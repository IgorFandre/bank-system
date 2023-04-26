#include "Account.h"
#include "DebitAccount.h"

DebitAccount::DebitAccount(size_t id, int64_t money, Date open_date, Date last_date)
    : Account(id, money, Account::Type::Debit, open_date, last_date)
{}

Account* DebitAccount::DeepCopy() const {
  return new DebitAccount(Account::account_id_, Account::account_money_, open_date_, last_usage_date_);
}