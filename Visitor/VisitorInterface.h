#pragma once

#include "../Bank/Bank.h"
#include "../DataBases/Interfaces/DataBaseAccounts.h"
#include "../DataBases/Interfaces/DataBaseClients.h"
#include "../IOSystem/IOInterface.h"

class VisitorInterface {
public:
  VisitorInterface() = default;
  virtual ~VisitorInterface() = default;

  virtual bool MakeVisit(const std::string &bank_name, size_t user_id,
                         const std::string &pas,
                         std::unique_ptr<DataBaseClients> &clients) = 0;
  virtual void ChangePassportData(std::unique_ptr<Show> &out,
                                  std::unique_ptr<Get> &in) = 0;
  virtual void Exit() = 0;
  virtual bool OpenAccount(std::unique_ptr<Show> &out, std::unique_ptr<Get> &in,
                           const BigInteger &cred_lim,
                           const BigInteger &bank_fee,
                           std::unique_ptr<DataBaseAccounts> &accounts,
                           size_t acc_id, const Date &system_date) = 0;
  virtual bool MakeTransaction(size_t acc_id_1, size_t cl_id_2, size_t acc_id_2,
                               const BigInteger &money,
                               std::unique_ptr<DataBaseAccounts> &accounts,
                               const Date &system_date) = 0;
};