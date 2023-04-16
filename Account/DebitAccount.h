#pragma once

#include "Account.h"

class DebitAccount : public Account {

 public:

  explicit DebitAccount(size_t id, int64_t money, Date open_date, Date last_date);
  ~DebitAccount() override = default;

  Account* DeepCopy() override;

};