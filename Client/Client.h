#ifndef BANK_SYSTEM_CLIENT_CLIENT_H_
#define BANK_SYSTEM_CLIENT_CLIENT_H_


#include "../IOSystem/IOInterface.h"

enum class Status {
  Confirmed,
  Unconfirmed,
  Blocked
};

struct Passport {

  int number;
  int series;

  std::string name;
  std::string surname;
  std::string address;

 public:

  Passport() : number{-1}, series{-1}, name{""}, surname{""}, address{""} {}
  Passport(int number, int series, const std::string& name, const std::string& surname, const std::string& address)
        : number{number}, series{series}, name{name}, surname{surname}, address{address}
  {}
  Passport(const Passport&) = default;
  Passport& operator=(const Passport&) = default;
  friend bool operator==(const Passport&, const Passport&) = default;

  Status GetPassportStatus() const {
    return (address != "" && number >= 0 && series >= 0) ? Status::Confirmed : Status::Unconfirmed;
  }

};


class Client {

  size_t user_id_;
  int64_t user_password_;
  Passport passport_;
  Status status_;

 public:

  Client() : user_id_(SIZE_T_MAX), user_password_(INT64_MAX), passport_(), status_{passport_.GetPassportStatus()}
  {}
  Client(size_t user_id, int64_t user_password, const Passport& passport)
        : user_id_{user_id}, user_password_{user_password}, passport_{passport}, status_{passport.GetPassportStatus()}
  {}

  Client(const Client&) = default;
  Client& operator=(const Client&) = default;
  friend bool operator==(const Client&, const Client&) = default;

  size_t GetID() const { return user_id_; }
  bool CheckPassword(int64_t pass) const { return pass == user_password_; }
  Status GetStatus() const { return status_; }

  void ChangePassport(const Passport& passport) {
    passport_ = passport;
  }

  void ChangeStatus(bool block = false) {
    if (block) {
      status_ = Status::Blocked;
    } else {
      status_ = passport_.GetPassportStatus();
    }
  }

};


#endif //BANK_SYSTEM_CLIENT_CLIENT_H_
