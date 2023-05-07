#include "Worker.h"

Worker::Worker(size_t worker_id, std::string&& worker_password)
: worker_id_{worker_id}, worker_password_{std::forward<std::string>(worker_password)}
{}

bool Worker::CheckPassword(const std::string& password) const { return worker_password_ == password; }