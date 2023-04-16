#pragma once

#include <fstream>

#include "../JsonParser/json.h"
#include "../Filesystem/Filesystem.h"

struct Request {
  using json = nlohmann::json;
  std::string bank_name;
  size_t user_id;
  std::string text;

  Request() : bank_name(), user_id(0), text() {}
  Request(const std::string& bank_name, size_t user_id, const std::string& text);

  void WriteRequest() const;
  static Request ReadLastRequest(const std::string& bank_name);
};