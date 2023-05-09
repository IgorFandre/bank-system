#pragma once

#include "Account.h"

class DebitAccount : public Account {
public:
  explicit DebitAccount(size_t id, const BigInteger &money, Date open_date,
                        Date last_date);
  ~DebitAccount() override = default;

  [[nodiscard]] std::shared_ptr<Account> DeepCopy() const override;

  friend bool operator==(const DebitAccount &, const DebitAccount &) = default;
};