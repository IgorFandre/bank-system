#pragma once

#include <iostream>
#include <memory>

class Worker {
public:
  Worker(size_t worker_id, std::string &&worker_password);

  [[nodiscard]] bool CheckPassword(const std::string &password) const;

  [[nodiscard]] inline size_t GetId() const { return worker_id_; }
  [[nodiscard]] inline const std::string &GetPassword() const {
    return worker_password_;
  }

private:
  size_t worker_id_;
  std::string worker_password_;
};