#pragma once

#include "../Bank/Bank.h"
#include "../IOSystem/IOInterface.h"
#include "../DataBases/Interfaces/DataBaseAccounts.h"
#include "../DataBases/Interfaces/DataBaseClients.h"

class VisitorInterface {
 public:
  VisitorInterface() = default;
  virtual ~VisitorInterface() = default;

  virtual bool MakeVisit(std::string bank_name, size_t user_id, int64_t pas,
                         std::unique_ptr<DataBaseClients>& clients) = 0;
  virtual void ChangePassportData(std::unique_ptr<Show>& out, std::unique_ptr<Get>& in) = 0;
  virtual void Exit() = 0;
  virtual bool OpenAccount(std::unique_ptr<Show>& out, std::unique_ptr<Get>& in, int64_t cred_lim,
                           int64_t bank_fee, std::unique_ptr<DataBaseAccounts>& accounts,
                           size_t acc_id, const Date& system_date) = 0;
  virtual bool MakeTransaction(size_t acc_id_1, size_t cl_id_2, size_t acc_id_2,
                               int64_t money, std::unique_ptr<DataBaseAccounts>& accounts,
                               const Date& system_date) = 0;

};