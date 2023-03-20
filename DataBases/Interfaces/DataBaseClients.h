#ifndef BANK_SYSTEM_DATABASES_INTERFACES_DATABASECLIENTS_H_
#define BANK_SYSTEM_DATABASES_INTERFACES_DATABASECLIENTS_H_


#include "../../Client/Client.h"

class DataBaseClients {

 public:

  DataBaseClients() = default;
  virtual ~DataBaseClients() = default;

  DataBaseClients(const DataBaseClients&) = delete;
  void operator=(const DataBaseClients&) = delete;

  virtual void WriteClient(const std::string& bank_name, const Client& client) = 0;
  virtual void WriteClients(const std::string& bank_name, const std::vector<Client>& clients) = 0;
  virtual void DeleteClient(const std::string& bank_name, size_t user_id) = 0;
  virtual Client GetCLient(const std::string& bank_name, size_t user_id) = 0;
  virtual std::vector<Client> GetAllClients(const std::string& bank_name) = 0;

};

#endif //BANK_SYSTEM_DATABASES_INTERFACES_DATABASECLIENTS_H_
