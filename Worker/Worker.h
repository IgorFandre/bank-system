#ifndef BANK_SYSTEM_WORKER_WORKER_H_
#define BANK_SYSTEM_WORKER_WORKER_H_


#include <iostream>

class Worker {

  size_t worker_id_;
  int64_t worker_password_;

 public:

  Worker(size_t worker_id, int64_t worker_password)
        : worker_id_{worker_id}, worker_password_{worker_password}
  {}

  bool CheckPassword(int64_t password) const { return worker_password_ == password; }
  size_t GetId() const { return worker_id_; }

};


#endif //BANK_SYSTEM_WORKER_WORKER_H_
