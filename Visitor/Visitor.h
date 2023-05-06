#pragma once

#include "../Builder/Builder.h"
#include "VisitorInterface.h"
#include "../DataBases/Interfaces/DataBaseClients.h"
#include "../Logger/Logger.h"


class Visitor : public VisitorInterface {
 public:
  Visitor();
  ~Visitor() override = default;

  bool MakeVisit(std::string bank_name, size_t user_id, int64_t pas, std::unique_ptr<DataBaseClients>&) override;
  void ChangePassportData(std::unique_ptr<Show>& out, std::unique_ptr<Get>& in) override;
  void Exit() override;
  bool OpenAccount(std::unique_ptr<Show>& out, std::unique_ptr<Get>& in, int64_t cred_lim, int64_t bank_fee,
                   std::unique_ptr<DataBaseAccounts>& accounts, size_t acc_id, const Date& system_date) override;
  bool MakeTransaction(size_t acc_id_1, size_t cl_id_2, size_t acc_id_2,
                       int64_t money, std::unique_ptr<DataBaseAccounts>& accounts,
                       const Date& system_date) override;

  [[nodiscard]] inline size_t GetID() const { return client_.GetID(); }
  [[nodiscard]] inline bool CheckPassword(int64_t pass) const { return client_.CheckPassword(pass); }
  [[nodiscard]] inline Status GetStatus() const { return client_.GetStatus(); }

 private:
  std::string bank_name_;
  Client client_;
  bool in_;

};