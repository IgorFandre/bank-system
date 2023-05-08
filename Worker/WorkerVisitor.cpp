#include "WorkerVisitor.h"

WorkerVisitor::WorkerVisitor() : bank_name_(), worker_(0, ""), in_(false) {}

bool WorkerVisitor::MakeVisit(const std::string &bank_name,
                              const Worker &worker,
                              const std::string &password) {
  if (worker.CheckPassword(password)) {
    worker_ = worker;
    bank_name_ = bank_name;
    in_ = true;
  }
  return in_;
}

void WorkerVisitor::Exit(const Date &system_date) {
  in_ = false;

  Logger logger(bank_name_, Logger::OperationType::WorkerOperation);
  std::string log = "ID: " + std::to_string(worker_.GetId()) + " (" +
                    Date::StringDate(system_date) + "): Exit";
  logger.AddLog(log);
}

void WorkerVisitor::CheckOldestRequest(std::unique_ptr<Show> &out,
                                       const Date &system_date) {
  Request last = Request::ReadLastRequest(bank_name_);
  if (last.user_id == 0) { // if no requests (if user_id == 0)
    out->Output("Requests not found");
  } else {
    out->Output(static_cast<int64_t>(last.user_id));
    out->Output(last.text);
  }

  Logger logger(bank_name_, Logger::OperationType::WorkerOperation);
  std::string log = "ID: " + std::to_string(worker_.GetId()) + " (" +
                    Date::StringDate(system_date) + "): Checked request";
  logger.AddLog(log);
}

bool WorkerVisitor::BlockUser(size_t user_id,
                              std::unique_ptr<DataBaseClients> &clients,
                              const Date &system_date) {
  std::shared_ptr<Client> client = clients->GetClient(bank_name_, user_id);
  if (client == nullptr) {
    return false;
  }
  client->ChangeStatus(true);
  clients->WriteClient(bank_name_, *client);

  Logger logger(bank_name_, Logger::OperationType::WorkerOperation);
  std::string log = "ID: " + std::to_string(worker_.GetId()) + " (" +
                    Date::StringDate(system_date) + "): Blocked user with ID " +
                    std::to_string(user_id);
  logger.AddLog(log);

  return true;
}
bool WorkerVisitor::RestoreUser(size_t user_id,
                                std::unique_ptr<DataBaseClients> &clients,
                                const Date &system_date) {
  std::shared_ptr<Client> client = clients->GetClient(bank_name_, user_id);
  if (client == nullptr) {
    return false;
  }
  client->ChangeStatus();
  clients->WriteClient(bank_name_, *client);

  Logger logger(bank_name_, Logger::OperationType::WorkerOperation);
  std::string log = "ID: " + std::to_string(worker_.GetId()) + " (" +
                    Date::StringDate(system_date) +
                    "): Restored user with ID " + std::to_string(user_id);
  logger.AddLog(log);

  return true;
}
bool WorkerVisitor::CancelTransaction(
    size_t cl_id_1,
    size_t acc_id_1,
    size_t cl_id_2,
    size_t acc_id_2,
    const BigInteger &money,
    std::unique_ptr<DataBaseAccounts> &accounts,
    const Date &system_date) {

  Logger logger(bank_name_, Logger::OperationType::WorkerOperation);
  std::string log = "ID: " + std::to_string(worker_.GetId()) + " (" +
                    Date::StringDate(system_date) + "): " + money.toString() +
                    " rubles from account " + std::to_string(acc_id_1) +
                    " (user ID " + std::to_string(cl_id_1) + " ) to account " +
                    std::to_string(acc_id_2) + " (user ID " +
                    std::to_string(cl_id_1) + " )";
  logger.AddLog(log);
  return false;
}