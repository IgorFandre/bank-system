#pragma once

#include <fstream>

#include "../JsonParser/json.h"
#include "../Filesystem/Filesystem.h"

struct Request {
  using json = nlohmann::json;

  Request() : bank_name(), user_id(0), text() {}
  Request(const std::string& bank_name, size_t user_id, const std::string& text);

  bool operator==(const Request&) const = default;

  void WriteRequest() const;
  static Request ReadLastRequest(const std::string& bank_name);

  std::string bank_name;
  size_t user_id;
  std::string text;

};