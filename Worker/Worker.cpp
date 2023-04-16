#include "Worker.h"

Worker::Worker(size_t worker_id, int64_t worker_password)
: worker_id_{worker_id}, worker_password_{worker_password}
{}

[[nodiscard]] bool Worker::CheckPassword(int64_t password) const { return worker_password_ == password; }
