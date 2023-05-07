#pragma once

#include "../IOSystem/IOInterface.h"
#include "Passport.h"

class Client {
 public:
  Client();
  Client(size_t user_id, std::string&& user_password, const Passport& passport);

  Client(const Client&) = default;
  Client& operator=(const Client&) = default;

  friend bool operator==(const Client&, const Client&) = default;

  [[nodiscard]] bool CheckPassword(const std::string& pass) const;
  void ChangePassport(const Passport& passport);
  void ChangeStatus(bool block = false);

  [[nodiscard]] inline size_t GetID() const { return user_id_; }
  [[nodiscard]] inline Status GetStatus() const { return status_; }
  [[nodiscard]] inline const std::string& GetPassword() const { return user_password_; }
  [[nodiscard]] inline const Passport* GetPassport() const { return &passport_; }

 private:
  size_t user_id_;
  std::string user_password_;
  Passport passport_;
  Status status_;

};