#pragma once

#include <iostream>

class Worker {
 public:
  Worker(size_t worker_id, int64_t worker_password);

  [[nodiscard]] bool CheckPassword(int64_t password) const;

  [[nodiscard]] inline size_t GetId() const { return worker_id_; }
  [[nodiscard]] inline int64_t GetPassword() const { return worker_password_; }

 private:
  size_t worker_id_;
  int64_t worker_password_;
};