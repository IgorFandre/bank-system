#include "Request.h"

Request::Request(const std::string &bank_name, size_t user_id,
                 const std::string &text)
    : bank_name(bank_name), user_id(user_id), text(text) {}

void Request::WriteRequest() const {
  std::string working_path = "Data/" + bank_name;
  Filesystem::CheckDirectory(working_path);
  working_path += "/requests.json";
  json requests;
  if (Filesystem::CheckFileForReadingJson(working_path)) {
    std::ifstream f_in(working_path);
    f_in >> requests;
  }
  requests.push_back({user_id, text});
  std::ofstream f_out(working_path);
  f_out << std::setw(4) << requests;
  f_out.close();
}

Request Request::ReadLastRequest(const std::string &bank_name) {
  std::string working_path = "Data/" + bank_name + "/requests.json";
  if (!Filesystem::CheckFileForReadingJson(working_path)) {
    return Request(bank_name, 0, "");
  }
  std::ifstream f_in(working_path);
  json requests;
  f_in >> requests;
  std::filesystem::remove(working_path);
  Filesystem::CheckFile(working_path);
  Request res{bank_name, requests[0][0], requests[0][1]};
  requests.erase(requests.begin());
  if (!requests.empty()) {
    std::ofstream f_out(working_path);
    f_out << std::setw(4) << requests;
  }
  return res;
}