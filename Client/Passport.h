#pragma once

#include "../IOSystem/IOInterface.h"

enum class Status {
  Confirmed = 1,
  Unconfirmed = 0,
  Blocked = -1
};

struct Passport {

 private:

  int number_;
  int series_;

  std::string name_;
  std::string surname_;
  std::string address_;

 public:

  Passport() : number_{-1}, series_{-1} {}
  Passport(int number, int series, std::string&& name, std::string&& surname, std::string&& address)
      : number_{number}, series_{series}, name_{std::forward<std::string>(name)},
        surname_{std::forward<std::string>(surname)}, address_{std::forward<std::string>(address)}
  {}
  Passport(const Passport&) = default;
  Passport& operator=(const Passport&) = default;
  friend bool operator==(const Passport&, const Passport&) = default;

  [[nodiscard]] inline Status GetPassportStatus() const {
    return (address_ != "0" && !address_.empty() && number_ >= 0 && series_ >= 0) ? Status::Confirmed : Status::Unconfirmed;
  }

  [[nodiscard]] inline int GetNumber() const { return number_; }
  [[nodiscard]] inline int GetSeries() const { return series_; }
  [[nodiscard]] inline std::string GetName() const { return name_; }
  [[nodiscard]] inline std::string GerSurname() const { return surname_; }
  [[nodiscard]] inline std::string GetAddress() const { return address_; }
};