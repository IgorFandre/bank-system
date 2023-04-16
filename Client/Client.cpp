#include "Client.h"

bool Client::CheckPassword(int64_t pass) const {
  return pass == user_password_;
}

void Client::ChangePassport(const Passport& passport) {
  passport_ = passport;
  ChangeStatus();
}

void Client::ChangeStatus(bool block) {
  if (block) {
    status_ = Status::Blocked;
  } else {
    status_ = passport_.GetPassportStatus();
  }
}