#include "Client.h"

Client::Client()
      : user_id_(), user_password_(), passport_(), status_{passport_.GetPassportStatus()} {
}

Client::Client(size_t user_id, std::string&& user_password, const Passport& passport)
      : user_id_{user_id}, user_password_{user_password}, passport_{passport}, status_{passport.GetPassportStatus()} {
}

bool Client::CheckPassword(const std::string& pass) const {
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