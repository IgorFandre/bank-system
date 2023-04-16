#include "JsonDBClients.h"

std::string JsonDBClients::GetClientsFileName(size_t id) {
  return "clients" + std::to_string(((id - 1) / 20) * 20) + "_"
      + std::to_string(((id - 1) / 20) * 20 + 20) + ".json";
}

void JsonDBClients::WriteClient(const std::string& bank_name, const Client& client) {
  const Passport* passport = client.GetPassport();
  json passport_info = json::array({passport->GetNumber(), passport->GetSeries(), passport->GetName(),
                                    passport->GerSurname(), passport->GetAddress()});

  /*      Passport's indexes in json:
  *
  * 0 - Passport number
  * 1 - Passport series
  * 2 - Name
  * 3 - Surname
  * 4 - Address
  *
  */

  json client_info = json::array({client.GetID(), client.GetPassword(),
                                  client.GetStatus(), passport_info});

  /*      Client's indexes in json:
  *
  * 0 - User id
  * 1 - User password
  * 2 - User status
  * 3 - Passport array (check prev list)
  *
  */

  std::string working_path = "Data/" + bank_name;
  Filesystem::CheckDirectory(working_path);
  working_path += "/Clients";
  Filesystem::CheckDirectory(working_path);
  working_path += "/" + GetClientsFileName(client.GetID());
  json clients;
  if (Filesystem::CheckFileForReadingJson(working_path)) {
    std::ifstream f_in(working_path);
    f_in >> clients;
    f_in.close();
    bool found = false;
    for (size_t i = 0; i < clients.size(); ++i) {
      if (clients[i][0] == client_info[0]) {
        found = true;
        clients[i] = client_info;
        break;
      }
    }
    if (!found) {
      clients.push_back(client_info);
    }
  } else {
    clients.push_back(client_info);
  }
  std::fstream clear_file(working_path, std::ios::out);
  clear_file.close();
  std::ofstream f_out(working_path);
  f_out << std::setw(4) << clients;
  f_out.close();
}

void JsonDBClients::WriteClients(const std::string& bank_name, const std::vector<Client>& clients) {
  for (const auto& client : clients) {
    WriteClient(bank_name, client);
  }
}

void JsonDBClients::DeleteClient(const std::string& bank_name, size_t user_id) {
  std::string working_path = "Data/" + bank_name + "/Clients/" + GetClientsFileName(user_id);
  if (!std::filesystem::exists(working_path) || !Filesystem::CheckFileForReadingJson(working_path)) {
    return;
  }
  json clients;
  std::ifstream f_in(working_path);
  f_in >> clients;
  for (size_t i = 0; i < clients.size(); ++i) {
    if (clients[i][0] == user_id) {
      clients.erase(i);
      std::fstream clear_file(working_path, std::ios::out);
      clear_file.close();
      std::ofstream f_out(working_path);
      f_out << std::setw(4) << clients;
      f_out.close();
      return;
    }
  }
  f_in.close();
}

Client* JsonDBClients::GetClient(const std::string& bank_name, size_t user_id) {
  std::string working_path = "Data/" + bank_name + "/Clients/" + GetClientsFileName(user_id);
  if (!std::filesystem::exists(working_path) || !Filesystem::CheckFileForReadingJson(working_path)) {
    return nullptr;
  }
  json clients;
  std::ifstream f_in(working_path);
  f_in >> clients;
  f_in.close();
  for (size_t i = 0; i < clients.size(); ++i) {
    if (clients[i][0] == user_id) {
      Passport pass(clients[i][3][0], clients[i][3][1], clients[i][3][2],
                    clients[i][3][3], clients[i][3][4]);
      return new Client(user_id, clients[i][1], pass);
    }
  }
  return nullptr;
}