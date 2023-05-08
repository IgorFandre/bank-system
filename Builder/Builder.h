#pragma once

#include "../Account/AccountFabric.h"
#include "../Account/CreditAccount.h"
#include "../Account/DebitAccount.h"
#include "../Account/DepositAccount.h"
#include "../Bank/Bank.h"
#include "../Client/Client.h"
#include "../DataBases/Interfaces/DataBaseBanks.h"
#include "../Request/Request.h"
#include "../Worker/Worker.h"

class Builder {
public:
  static void GetFilledString(std::string &to_fill,
                              std::unique_ptr<Show> &out,
                              std::unique_ptr<Get> &in,
                              const std::string &message);

  static void GetNumber(int64_t b1,
                        int64_t b2,
                        int64_t &num,
                        std::unique_ptr<Show> &out,
                        std::unique_ptr<Get> &in,
                        const std::string &message);

  static void GetBigInteger(const BigInteger &b1,
                            const BigInteger &b2,
                            BigInteger &num,
                            std::unique_ptr<Show> &out,
                            std::unique_ptr<Get> &in,
                            const std::string &message);

  static std::shared_ptr<Account> BuildAccount(std::unique_ptr<Show> &out,
                                               std::unique_ptr<Get> &in,
                                               const Date &system_date,
                                               size_t account_id,
                                               const BigInteger &cred_lim,
                                               const BigInteger &bank_fee);

  static Bank BuildBank(std::unique_ptr<Show> &out,
                        std::unique_ptr<Get> &in,
                        std::unique_ptr<DataBaseBanks> &banks);

  static Client
  BuildClient(std::unique_ptr<Show> &out, std::unique_ptr<Get> &in, size_t id);

  static Passport BuildPassport(std::unique_ptr<Show> &out,
                                std::unique_ptr<Get> &in);

  static Request BuildRequest(std::unique_ptr<Show> &out,
                              std::unique_ptr<Get> &in,
                              const std::string &bank_name,
                              size_t id);

  static Worker
  BuildWorker(std::unique_ptr<Show> &out, std::unique_ptr<Get> &in, size_t id);
};