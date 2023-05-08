#include "DateSetter.h"

void DateSetter::StartSession(Date &system_date, bool write) {
  auto time_now = std::chrono::system_clock::now();
  auto day_time_now = std::chrono::system_clock::to_time_t(time_now);

  system_date = std::chrono::floor<std::chrono::days>(time_now);

  if (!write) {
    return;
  }

  std::string working_path = "app_usage.txt";
  std::ofstream f_out(working_path, std::ios::app);
  f_out << "Started session:"
        << "\t" << std::ctime(&day_time_now);
  f_out.close();
}

void DateSetter::FinishSession(bool write) {
  auto time_now = std::chrono::system_clock::now();
  auto day_time_now = std::chrono::system_clock::to_time_t(time_now);

  if (!write) {
    return;
  }

  std::string working_path = "app_usage.txt";
  std::ofstream f_out(working_path, std::ios::app);
  f_out << "Ended session:"
        << "\t\t" << std::ctime(&day_time_now) << "\n";
  f_out.close();
}