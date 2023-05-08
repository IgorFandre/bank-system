#include "Executable.h"

Executable::Executable()
    : mode_(Mode::BankMenu)
    , system_date()
    , bank_name_()
    , bank_(nullptr)
    , visitor_(new Visitor())
    , worker_visitor_(new WorkerVisitor())
    , accounts_(dynamic_cast<DataBaseAccounts *>(new JsonDBAccounts()))
    , banks_(dynamic_cast<DataBaseBanks *>(new JsonDBBanks()))
    , clients_(dynamic_cast<DataBaseClients *>(new JsonDBClients()))
    , workers_(dynamic_cast<DataBaseWorkers *>(new JsonDBWorkers()))
    , out_(dynamic_cast<Show *>(new ConsoleShow()))
    , in_(dynamic_cast<Get *>(new ConsoleGet())) {
  DateSetter::StartSession(system_date);
}

Executable::~Executable() {
  DateSetter::FinishSession();
  if (bank_) {
    banks_->WriteBank(*bank_);
  }
}

void Executable::Start() {
  while (true) {
    if (mode_ == Mode::MainMenu) {
      MainMenu();
    }
    if (mode_ == Mode::WorkerSession) {
      WorkerSession();
    }
    if (mode_ == Mode::VisitorSession) {
      VisitorSession();
    }
    if (mode_ == Mode::BankMenu) {
      BankMenu();
    }
    if (mode_ == Mode::Stop) {
      return;
    }
  }
}

void Executable::BankMenu() {
  std::string message = "Choose what do you want to do:\n"
                        "1 - Exit\n"
                        "2 - Create new bank\n"
                        "3 - Show all banks\n"
                        "4 - Go to bank\n"
                        "5 - Update system time";
  int64_t choose;
  Builder::GetNumber(1, 4, choose, out_, in_, message);
  if (choose == 2) {
    Bank new_bank = Builder::BuildBank(out_, in_, banks_);
    banks_->WriteBank(new_bank);
    message =
        "What sudo password do you want to set? (write it without spaces)";
    std::string bank_password;
    Builder::GetFilledString(bank_password, out_, in_, message);
    workers_->AddNewBank(new_bank.GetName(), bank_password);
  } else if (choose == 3) {
    ShowExistingBanks();
  } else if (choose == 4) {
    Builder::GetFilledString(bank_name_, out_, in_, "Enter bank name:");
    while ((!banks_->FindBank(bank_name_)) && bank_name_ != "!") {
      out_->Output("Error! We don't find this bank. To go back write '!'");
      bank_name_ = "";
      Builder::GetFilledString(bank_name_, out_, in_, "Enter bank name:");
    }
    if (bank_name_ == "!") {
      bank_name_ = "";
    } else {
      if (bank_) {
        banks_->WriteBank(*bank_);
      }
      bank_ = banks_->GetBank(bank_name_);
      mode_ = Mode::MainMenu;
    }
  } else if (choose == 5) {
    system_date =
        std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
  } else {
    mode_ = Mode::Stop;
  }
}

void Executable::ShowExistingBanks() const {
  out_->Output("Existing banks:");
  for (const auto &bank : banks_->GetBanks()) {
    out_->Output("- " + bank->GetName());
  }
  if (dynamic_cast<ConsoleShow *>(out_.get()) != nullptr) {
    out_->Output("");
  }
}

void Executable::MainMenu() {
  std::string message = "Choose what do you want to do:\n"
                        "1 - Exit\n"
                        "2 - Enter as a visitor\n"
                        "3 - Enter as a worker\n"
                        "4 - Make request\n"
                        "5 - Create a visitor\n"
                        "6 - Create a worker";
  int64_t choose;
  Builder::GetNumber(1, 6, choose, out_, in_, message);
  if (choose == 1) {
    mode_ = Mode::BankMenu;
  } else if (choose == 2) {
    mode_ = Mode::VisitorSession;
  } else if (choose == 3) {
    mode_ = Mode::WorkerSession;
  } else if (choose == 4) {
    MakeRequest();
  } else if (choose == 5) {
    Client cl = Builder::BuildClient(out_, in_, bank_->GetClientID());
    clients_->WriteClient(bank_name_, cl);
    out_->Output("Thank you! Your id is :");
    out_->Output(static_cast<int64_t>(cl.GetID()));
    out_->Output("Please write it down and don't lose.");
  } else {
    Worker w = Builder::BuildWorker(out_, in_, bank_->GetWorkerID());

    message = "Please write sudo password";
    std::string bank_password;
    Builder::GetFilledString(bank_password, out_, in_, message);

    if (!workers_->WriteWorker(bank_name_, bank_password, w)) {
      out_->Output("Something went wrong! Please try again later");
    }
  }
}

void Executable::VisitorSession() {
  int64_t id;
  std::string pas;
  {
    std::string message = "Enter your id (enter -1 to exit) :";
    Builder::GetNumber(-1, 10'000, id, out_, in_, message);
    if (id == -1) {
      mode_ = Mode::MainMenu;
      return;
    }
    message = "Enter your password: ";
    out_->Output(message);
    pas = in_->InputString();
  }
  std::shared_ptr<Client> client = clients_->GetClient(bank_name_, id);
  if (!client) {
    out_->Output("This user doesn't exist. Please, try again or register");
    mode_ = Mode::MainMenu;
    return;
  }
  if (client->GetStatus() == Status::Blocked) {
    out_->Output("You are blocked. Please report to the administrator");
    mode_ = Mode::MainMenu;
    return;
  }
  bool visit = visitor_->MakeVisit(bank_name_, id, pas, clients_);
  if (visit) {
    while (true) {
      std::string message = "Menu:\n"
                            "1 - Exit\n"
                            "2 - Change passport\n"
                            "3 - Open new account\n"
                            "4 - Check my accounts\n"
                            "5 - Make transaction";
      int64_t choose;
      Builder::GetNumber(1, 5, choose, out_, in_, message);
      if (choose == 1) {
        visitor_->Exit();
        mode_ = Mode::MainMenu;
        return;
      } else if (choose == 2) {
        visitor_->ChangePassportData(out_, in_);
      } else if (choose == 3) {
        if (!visitor_->OpenAccount(out_,
                                   in_,
                                   bank_->GetCreditLimit(),
                                   bank_->GetBankFee(),
                                   accounts_,
                                   bank_->GetAccountID(),
                                   system_date)) {
          out_->Output("Something went wrong! Probably you didn't confirmed "
                       "you profile.");
        }
      } else if (choose == 4) {
        ShowAccounts(visitor_->GetID());
      } else {
        MakeTransaction();
      }
    }
  } else {
    mode_ = Mode::MainMenu;
  }
}

void Executable::ShowAccounts(size_t client_id) const {
  auto accounts = accounts_->GetUserAccounts(bank_name_, client_id);
  for (const auto &account : accounts) {
    std::string acc_type = " ( ";
    if (account->GetType() == Account::Type::Credit) {
      acc_type += "Credit account (minimum is " +
                  bank_->GetCreditLimit().toString() + ") )";
    } else if (account->GetType() == Account::Type::Deposit) {
      acc_type += "Deposit account )";
    } else {
      acc_type += "Debit account )";
    }
    std::string acc_info = "Id: " + std::to_string(account->GetAccountId()) +
                           "    Money: " + account->GetBalance().toString() +
                           acc_type;
    out_->Output(acc_info);
  }
}

void Executable::MakeTransaction() {
  int64_t cl_id_1, acc_id_1, cl_id_2, acc_id_2;
  int64_t money;

  cl_id_1 = static_cast<int64_t>(visitor_->GetID());

  ShowAccounts(cl_id_1);

  std::string message = "What account do you want to use? (write -1 to return)";
  Builder::GetNumber(-1, INT64_MAX, acc_id_1, out_, in_, message);
  if (acc_id_1 == -1) {
    return;
  }

  message = "How much money do you want to send? (write -1 to return)";
  Builder::GetNumber(-1, INT64_MAX, money, out_, in_, message);
  if (money == -1) {
    return;
  }

  message = "Write recipient's id (write -1 to return):";
  Builder::GetNumber(-1, INT64_MAX, cl_id_2, out_, in_, message);
  if (cl_id_2 == -1) {
    return;
  }

  message = "Write recipient's account id (write -1 to return):";
  Builder::GetNumber(-1, INT64_MAX, acc_id_2, out_, in_, message);
  if (acc_id_2 == -1) {
    return;
  }

  bool done = visitor_->MakeTransaction(static_cast<size_t>(acc_id_1),
                                        static_cast<size_t>(cl_id_2),
                                        static_cast<size_t>(acc_id_2),
                                        money,
                                        accounts_,
                                        system_date);
  if (done) {
    out_->Output("Everything is ok!");
  } else {
    out_->Output("Something went wrong, please report to the administrator or "
                 "try again.");
  }
  mode_ = Mode::VisitorSession;
}

void Executable::WorkerSession() {
  int64_t worker_id;
  std::string pas;
  {
    std::string message = "Enter your worker id (enter -1 to exit) :";
    Builder::GetNumber(-1, 10'000, worker_id, out_, in_, message);
    if (worker_id == -1) {
      mode_ = Mode::MainMenu;
      return;
    }
    message = "Enter your password: ";
    out_->Output(message);
    pas = in_->InputString();
  }
  std::shared_ptr<Worker> worker = workers_->GetWorker(bank_name_, worker_id);
  if (worker == nullptr) {
    out_->Output("This account doesn't exist");
    mode_ = Mode::MainMenu;
    return;
  } else if (!worker->CheckPassword(pas)) {
    out_->Output("Wrong password!");
    mode_ = Mode::MainMenu;
    return;
  }
  bool visit = worker_visitor_->MakeVisit(bank_name_, *worker, pas);
  if (visit) {
    while (true) {
      std::string message = "Menu:\n"
                            "1 - Exit\n"
                            "2 - Check oldest request\n"
                            "3 - Block user\n"
                            "4 - Restore user\n"
                            "5 - Cancel transaction";
      int64_t choose;
      Builder::GetNumber(1, 5, choose, out_, in_, message);
      if (choose == 1) {
        worker_visitor_->Exit(system_date);
        mode_ = Mode::MainMenu;
        return;
      } else if (choose == 2) {
        worker_visitor_->CheckOldestRequest(out_, system_date);
      } else if (choose == 3) {
        {
          std::string user_delete_id = "Enter user id (enter -1 to return): ";
          out_->Output(user_delete_id);
          int64_t id = in_->InputNumber();
          if (id != -1) {
            if (worker_visitor_->BlockUser(id, clients_, system_date)) {
              out_->Output("User " + std::to_string(id) +
                           " was blocked by you");
            } else {
              out_->Output("Something went wrong!");
            }
          }
        }
        visitor_->OpenAccount(out_,
                              in_,
                              bank_->GetCreditLimit(),
                              bank_->GetBankFee(),
                              accounts_,
                              bank_->GetAccountID(),
                              system_date);
      } else if (choose == 4) {
        {
          std::string user_delete_id = "Enter user id (enter -1 to return): ";
          out_->Output(user_delete_id);
          int64_t id = in_->InputNumber();
          if (id != -1) {
            if (worker_visitor_->RestoreUser(id, clients_, system_date)) {
              out_->Output("User " + std::to_string(id) +
                           " was restored by you");
            } else {
              out_->Output("Something went wrong!");
            }
          }
        }
      } else {
        CancelTransaction();
      }
    }
  } else {
    mode_ = Mode::MainMenu;
  }
}

void Executable::CancelTransaction() {
  int64_t cl_id_1, acc_id_1, cl_id_2, acc_id_2, money;

  std::string message = "Write id to get money from (write -1 to return):";
  Builder::GetNumber(-1, INT64_MAX, cl_id_1, out_, in_, message);
  if (cl_id_1 == -1) {
    return;
  }

  message = "Write his account id (write -1 to return):";
  Builder::GetNumber(-1, INT64_MAX, acc_id_1, out_, in_, message);
  if (acc_id_1 == -1) {
    return;
  }

  message = "How much money? (write -1 to return)";
  Builder::GetNumber(-1, INT64_MAX, money, out_, in_, message);
  if (money == -1) {
    return;
  }

  message = "Write id which gets money (write -1 to return):";
  Builder::GetNumber(-1, INT64_MAX, cl_id_2, out_, in_, message);
  if (cl_id_2 == -1) {
    return;
  }

  message = "Write his account id (write -1 to return):";
  Builder::GetNumber(-1, INT64_MAX, acc_id_2, out_, in_, message);
  if (acc_id_2 == -1) {
    return;
  }

  bool done = worker_visitor_->CancelTransaction(static_cast<size_t>(cl_id_1),
                                                 static_cast<size_t>(acc_id_1),
                                                 static_cast<size_t>(cl_id_2),
                                                 static_cast<size_t>(acc_id_2),
                                                 money,
                                                 accounts_,
                                                 system_date);
  if (done) {
    out_->Output("Everything is ok!");
  } else {
    out_->Output("Something went wrong, please report to the administrator or "
                 "try again.");
  }
  mode_ = Mode::VisitorSession;
}

void Executable::MakeRequest() {
  mode_ = Mode::MainMenu;
  std::string message = "What is your id? To return write 0";
  int64_t user_id;
  Builder::GetNumber(0, INT64_MAX, user_id, out_, in_, message);
  if (user_id == 0) {
    return;
  }
  Builder::BuildRequest(out_, in_, bank_name_, user_id).WriteRequest();
}
