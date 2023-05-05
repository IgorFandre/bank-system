#pragma once

#include "../IOSystem/IOInterface.h"
#include "Passport.h"

class Client {
 public:
  Client() : user_id_(SIZE_T_MAX), user_password_(INT64_MAX), passport_(), status_{passport_.GetPassportStatus()}
  {}
  Client(size_t user_id, int64_t user_password, const Passport& passport)
        : user_id_{user_id}, user_password_{user_password}, passport_{passport}, status_{passport.GetPassportStatus()}
  {}

  Client(const Client&) = default;
  Client& operator=(const Client&) = default;

  friend bool operator==(const Client&, const Client&) = default;

  [[nodiscard]] bool CheckPassword(int64_t pass) const;
  void ChangePassport(const Passport& passport);
  void ChangeStatus(bool block = false);

  [[nodiscard]] inline size_t GetID() const { return user_id_; }
  [[nodiscard]] inline Status GetStatus() const { return status_; }
  [[nodiscard]] inline int64_t GetPassword() const { return user_password_; }
  [[nodiscard]] inline const Passport* GetPassport() const { return &passport_; }

 private:
  size_t user_id_;
  int64_t user_password_;
  Passport passport_;
  Status status_;

};