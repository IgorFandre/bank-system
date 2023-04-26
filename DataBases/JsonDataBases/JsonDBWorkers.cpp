#include "JsonDBWorkers.h"

void JsonDBWorkers::AddNewBank(const std::string& bank_name, const std::string& sudo_pas) {
  std::string working_path = "Data/" + bank_name;
  Filesystem::CheckDirectory(working_path);
  working_path += "/workers.json";
  Filesystem::CheckFile(working_path);
  std::ofstream f_out(working_path);
  json bank_sudo_pas = json::array({sudo_pas});
  f_out << std::setw(4) << bank_sudo_pas;
  f_out.close();
}

bool JsonDBWorkers::WriteWorker(const std::string& bank_name, const std::string& sudo_pas, const Worker& worker) {
  json worker_info = json::array({worker.GetId(), worker.GetPassword()});

  /*      Worker's indexes in json:
  *
  * 0 - Worker id
  * 1 - Worker password
  *
  */

  std::string working_path = "Data/" + bank_name;
  Filesystem::CheckDirectory(working_path);
  working_path += "/workers.json";
  if (!Filesystem::CheckFileForReadingJson(working_path)) {
    std::cerr << "Not found worker file or it is harmed" << std::endl;
    return false;
  }
  std::ifstream f_in(working_path);
  json workers;
  f_in >> workers;
  f_in.close();
  if (workers.empty()) {
    std::cerr << "Not found worker file or it is harmed" << std::endl;
    return false;
  }
  if (workers[0] != sudo_pas) {
    return false;
  }
  bool found = false;
  for (size_t i = 1; i < workers.size(); ++i) {
    if (workers[i][0] == worker.GetId()) {
      found = true;
      workers[i] = worker_info;
      break;
    }
  }
  if (!found) {
    workers.push_back(worker_info);
  }
  std::fstream clear_file(working_path, std::ios::out);
  clear_file.close();
  std::ofstream f_out(working_path);
  f_out << std::setw(4) << workers;
  f_out.close();
  return true;
}

bool JsonDBWorkers::DeleteWorker(const std::string& bank_name, const std::string& sudo_pas, size_t worker_id) {
  std::string working_path = "Data/" + bank_name;
  Filesystem::CheckDirectory(working_path);
  working_path += "/workers.json";
  if (!Filesystem::CheckFileForReadingJson(working_path)) {
    return true;
  }
  std::ifstream f_in(working_path);
  json workers;
  f_in >> workers;
  if (workers.empty()) {
    return true;
  }
  if (workers[0] != sudo_pas) {
    return false;
  }
  bool found = false;
  for (size_t i = 1; i < workers.size(); ++i) {
    if (workers[i][0] == worker_id) {
      found = true;
      workers.erase(i);
      break;
    }
  }
  if (!found) {
    return false;
  }
  std::fstream clear_file(working_path, std::ios::out);
  clear_file.close();
  std::ofstream f_out(working_path);
  f_out << std::setw(4) << workers;
  f_out.close();
  return true;
}
Worker* JsonDBWorkers::GetWorker(const std::string& bank_name, size_t worker_id) {
  std::string working_path = "Data/" + bank_name;
  Filesystem::CheckDirectory(working_path);
  working_path += "/workers.json";
  if (!Filesystem::CheckFileForReadingJson(working_path)) {
    return nullptr;
  }
  std::fstream f(working_path);
  json workers;
  f >> workers;
  if (workers.empty()) {
    return nullptr;
  }
  for (size_t i = 1; i < workers.size(); ++i) {
    if (workers[i][0] == worker_id) {
      return new Worker(worker_id, workers[i][1]);
    }
  }
  f.close();
  return nullptr;
}