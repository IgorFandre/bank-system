#ifndef BANK_SYSTEM_ACCOUNT_DEBITACCOUNT_H_
#define BANK_SYSTEM_ACCOUNT_DEBITACCOUNT_H_


#include "Account.h"

class DebitAccount : public Account {

 public:

  DebitAccount(size_t id, int64_t money)
        : Account(id, money)
  {}

};


#endif //BANK_SYSTEM_ACCOUNT_DEBITACCOUNT_H_
