#include "../../../Logger/Logger.h"
#include "LoggerTestCase.h"

std::string LOGGER_TEST_CASE::bank_name = "impossible_name_for_bank";

void LOGGER_TEST_CASE::SetUpTestSuite() {
  assert(!std::filesystem::exists("Data/" + bank_name));
}

void LOGGER_TEST_CASE::TearDownTestSuite() {
  std::string data = "Data";
  if (std::filesystem::exists(data) && std::filesystem::is_empty(data)) {
    std::filesystem::remove(data);
  }
}

void LOGGER_TEST_CASE::TearDown() {
  std::filesystem::remove_all("Data/" + bank_name);
}

TEST_F(LOGGER_TEST_CASE, check_exeption) {
  ASSERT_THROW(Logger("", Logger::OperationType::OpenAccount),
               std::invalid_argument);
}

TEST_F(LOGGER_TEST_CASE, worker_logs) {
  Logger log(bank_name, Logger::OperationType::WorkerOperation);
  ASSERT_EQ(log.GetWorkingFile(), "Data/" + bank_name + "/WorkerLogs/logs.txt");
  ASSERT_TRUE(std::filesystem::exists(log.GetWorkingFile()));
}

TEST_F(LOGGER_TEST_CASE, accounts_logs) {
  Logger log(bank_name, Logger::OperationType::OpenAccount);
  ASSERT_EQ(log.GetWorkingFile(),
            "Data/" + bank_name + "/VisitorLogs/accounts_logs.txt");
  ASSERT_TRUE(std::filesystem::exists(log.GetWorkingFile()));
  std::string start_message = "Types of accounts:\n"
                              "1 - Credit account\n"
                              "2 - Deposit account\n"
                              "3 - Debit account\n\n";
  std::ifstream i_file(log.GetWorkingFile());
  std::stringstream buffer;
  buffer << i_file.rdbuf();
  ASSERT_EQ(buffer.str(), start_message);
  i_file.close();
}

TEST_F(LOGGER_TEST_CASE, transaction_logs) {
  Logger log(bank_name, Logger::OperationType::Transaction);
  ASSERT_EQ(log.GetWorkingFile(),
            "Data/" + bank_name + "/VisitorLogs/transaction_logs.txt");
  ASSERT_TRUE(std::filesystem::exists(log.GetWorkingFile()));
}

TEST_F(LOGGER_TEST_CASE, write_logs) {
  Logger log(bank_name, Logger::OperationType::WorkerOperation);
  log.AddLog("Worker 1 killed the visitor");
  std::ifstream i_file(log.GetWorkingFile());
  std::stringstream buffer_1;
  buffer_1 << i_file.rdbuf();
  ASSERT_EQ(buffer_1.str(), "Worker 1 killed the visitor\n");
  i_file.close();

  log.AddLog("Worker 2 is eating cookies right now");
  i_file.open(log.GetWorkingFile());
  std::stringstream buffer_2;
  buffer_2 << i_file.rdbuf();
  ASSERT_EQ(
      buffer_2.str(),
      "Worker 1 killed the visitor\nWorker 2 is eating cookies right now\n");
  i_file.close();
}