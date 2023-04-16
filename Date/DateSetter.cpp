#include "DateSetter.h"

void DateSetter::StartSession(Date& system_date) {
  auto time_now = std::chrono::system_clock::now();
  auto day_time_now = std::chrono::system_clock::to_time_t(time_now);

  system_date = std::chrono::floor<std::chrono::days>(time_now);

  std::string working_path = "app_usage.txt";
  std::ofstream f_out(working_path, std::ios::app);
  f_out << "Started session:" << "\t" << std::ctime(&day_time_now);
  f_out.close();
}

void DateSetter::FinishSession() {
  auto time_now = std::chrono::system_clock::now();
  auto day_time_now = std::chrono::system_clock::to_time_t(time_now);

  std::string working_path = "app_usage.txt";
  std::ofstream f_out(working_path, std::ios::app);
  f_out << "Ended session:" << "\t\t" << std::ctime(&day_time_now) << "\n";
  f_out.close();
}