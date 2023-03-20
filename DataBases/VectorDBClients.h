#ifndef BANK_SYSTEM_DATABASES_VECTORDBCLIENTS_H_
#define BANK_SYSTEM_DATABASES_VECTORDBCLIENTS_H_


#include <unordered_map>
#include <vector>

#include "DataBaseClients.h"

class VectorDBClients : public DataBaseClients {

 public:

  VectorDBClients() = default;

  VectorDBClients(const VectorDBClients&) = delete;
  void operator=(const VectorDBClients&) = delete;

  void WriteClient(const std::string& bank_name, const Client& client) override {
    clients_[bank_name][client.GetID()] = client;
  }
  void WriteClients(const std::string& bank_name, const std::vector<Client>& clients) override {
    for (auto client : clients) {
      clients_[bank_name][client.GetID()] = client;
    }
  }
  void DeleteClient(const std::string& bank_name, size_t user_id) override {
    if (clients_.contains(bank_name) && clients_[bank_name].contains(user_id)) {
      clients_[bank_name].erase(user_id);
    }
  }
  Client GetCLient(const std::string& bank_name, size_t user_id) override {
    return clients_[bank_name][user_id];
  }
  std::vector<Client> GetAllClients(const std::string& bank_name) override {
    std::vector<Client> clients(clients_[bank_name].size());
    size_t i = 0;
    for (auto elem : clients_[bank_name]) {
      clients[i++] = elem.second;
    }
    return clients;
  }

 private:

  std::unordered_map<std::string, std::unordered_map<size_t, Client>> clients_;

};


#endif //BANK_SYSTEM_DATABASES_VECTORDBCLIENTS_H_
