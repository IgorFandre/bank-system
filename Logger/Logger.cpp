#include "Logger.h"

Logger::Logger(const std::string& bank, OperationType op) {
  working_file_ = "Data/" + bank;
  Filesystem::CheckDirectory(working_file_);
  if (op == OperationType::WorkerOperation) {
    working_file_ += "/WorkerLogs/";
    Filesystem::CheckDirectory(working_file_);
    working_file_ += "logs.txt";
    Filesystem::CheckFile(working_file_);
  } else {
    working_file_ += "/VisitorLogs/";
    Filesystem::CheckDirectory(working_file_);
    if (op == OperationType::OpenAccount) {
      working_file_ += "accounts_logs.txt";
    } else {
      working_file_ += "transaction_logs.txt";
    }
    if (!Filesystem::CheckFile(working_file_) && op == OperationType::OpenAccount) {
      std::string start_message = "Types of accounts:\n"
                                  "1 - Credit account\n"
                                  "2 - Deposit account\n"
                                  "3 - Debit account\n\n";
      std::ofstream f_in(working_file_);
      f_in << start_message;
      f_in.close();
    }
  }
}

void Logger::AddLog(const std::string& log) {
  std::ofstream f_logs(working_file_, std::ios::app);
  f_logs << log << "\n";
  f_logs.close();
}