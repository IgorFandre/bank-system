#include "Visitor.h"

Visitor::Visitor() : bank_name_(), client_(), in_{false} {}

bool Visitor::MakeVisit(std::string bank_name, size_t user_id, int64_t pas, std::unique_ptr<DataBaseClients>& clients) {
  Client* client = clients->GetClient(bank_name, user_id);
  if (!client->CheckPassword(pas)) {
    return false;
  }
  bank_name_ = bank_name;
  client_ = *client;
  in_ = true;
  delete client;
  return in_;
}

void Visitor::ChangePassportData(std::unique_ptr<Show>& out, std::unique_ptr<Get>& in) {
  client_.ChangePassport(Builder::BuildPassport(out, in));
}

void Visitor::Exit() {
  in_ = false;
}

bool Visitor::OpenAccount(std::unique_ptr<Show>& out, std::unique_ptr<Get>& in, int64_t cred_lim, int64_t bank_fee,
                          std::unique_ptr<DataBaseAccounts>& accounts, size_t acc_id, const Date& system_date) {
  if (in_) {
    Account* account = Builder::BuildAccount(out, in, system_date, acc_id, cred_lim, bank_fee);
    if (client_.GetStatus() == Status::Unconfirmed && dynamic_cast<CreditAccount*>(account) != nullptr) {
      return false;
    }
    Logger logger(bank_name_, Logger::OperationType::OpenAccount);
    std::string log = "ID: " + std::to_string(client_.GetID()) + " (" + Date::StringDate(system_date)
        + "): Opened account " + std::to_string(account->GetAccountId()) + " ( "
        + std::to_string(static_cast<int>(account->GetType())) + " type ) with "
        + std::to_string(account->GetBalance()) + " rubles";
    logger.AddLog(log);
    accounts->WriteAccount(bank_name_, client_.GetID(), account);
  }
  return in_;
}

bool Visitor::MakeTransaction(size_t acc_id_1, size_t cl_id_2, size_t acc_id_2,
                     int64_t money, std::unique_ptr<DataBaseAccounts>& accounts, const Date& system_date) {
  if (money < 0) {
    return false;
  }
  if (in_) {
    Account* account_1 = accounts->GetAccount(bank_name_, client_.GetID(), acc_id_1);
    Account* account_2 = accounts->GetAccount(bank_name_, cl_id_2, acc_id_2);
    if (account_1 == nullptr || account_2 == nullptr) {
      return false;
    }
    if (client_.GetStatus() == Status::Unconfirmed && money > 50'000) {
      return false;
    }
    if (!account_1->Transaction(-money, system_date) || !account_2->Transaction(money, system_date)) {
      delete account_1;
      delete account_2;
      return false;
    }
    accounts->WriteAccount(bank_name_, client_.GetID(), account_1);
    accounts->WriteAccount(bank_name_, cl_id_2, account_2);
    Logger logger(bank_name_, Logger::OperationType::Transaction);
    std::string log = "ID: " + std::to_string(client_.GetID()) + " (" + Date::StringDate(system_date) + "): "
        + std::to_string(money) + " rubles from account " + std::to_string(acc_id_1) + " to account "
        + std::to_string(acc_id_2) + " (user id " + std::to_string(cl_id_2) + " )";
    logger.AddLog(log);
  }
  return in_;
}