#pragma once

#include <typeinfo>

#include "../Builder/Builder.h"
#include "../Date/DateSetter.h"
#include "../IOSystem/IOInterface.h"
#include "../IOSystem/IOIostream.h"
#include "../Visitor/Visitor.h"
#include "../Worker/WorkerVisitor.h"
#include "../DataBases/JsonDataBases/JsonDBAccounts.h"
#include "../DataBases/JsonDataBases/JsonDBBanks.h"
#include "../DataBases/JsonDataBases/JsonDBClients.h"
#include "../DataBases/JsonDataBases/JsonDBWorkers.h"

class Executable {

 public:

  Executable();
  ~Executable();

  void Start();
  void BankMenu();
  void MainMenu();
  void VisitorSession();
  void ShowAccounts(size_t client_id);
  void MakeTransaction();
  void WorkerSession();
  void CancelTransaction();
  void MakeRequest();

 private:

  enum class Mode {
    Stop = 0,
    BankMenu,
    MainMenu,
    VisitorSession,
    WorkerSession,
  };
  Mode mode_;
  Date system_date;
  std::string bank_name_;
  std::unique_ptr<DataBaseAccounts> accounts_;
  std::unique_ptr<DataBaseBanks> banks_;
  std::unique_ptr<DataBaseClients> clients_;
  std::unique_ptr<DataBaseWorkers> workers_;
  std::unique_ptr<Show> out_;
  std::unique_ptr<Get> in_;
  Bank* bank_;
  Visitor* visitor_;
  WorkerVisitor* worker_visitor_;

};