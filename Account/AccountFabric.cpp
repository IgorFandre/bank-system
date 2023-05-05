#include "AccountFabric.h"

CreditFabric::CreditFabric(int64_t credit_limit, int64_t bank_fee)
    : credit_limit_{credit_limit}, bank_fee_{bank_fee}
{}
std::shared_ptr<Account> CreditFabric::MakeAccount(size_t id, int64_t money, const Date& system_date) {
  return std::shared_ptr<Account>{new CreditAccount(id, money, credit_limit_, bank_fee_, system_date, system_date)};
}


std::shared_ptr<Account> DebitFabric::MakeAccount(size_t id, int64_t money, const Date& system_date) {
return std::shared_ptr<Account>{new DebitAccount(id, money, system_date, system_date)};
}


DepositFabric::DepositFabric(const Date& finish) : finish_{finish} {}
std::shared_ptr<Account> DepositFabric::MakeAccount(size_t id, int64_t money, const Date& system_date) {
  return std::shared_ptr<Account>{new DepositAccount(id, money, finish_, system_date, system_date)};
}