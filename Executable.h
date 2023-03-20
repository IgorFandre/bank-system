#ifndef BANK_SYSTEM__EXECUTABLE_H_
#define BANK_SYSTEM__EXECUTABLE_H_


#include "Builder/Builder.h"
#include "IOSystem/IOInterface.h"
#include "../Client/Visitor.h"
#include "../Worker/WorkerVisitor.h"

class Executable {

 public:

  Executable(Show* out, Get* in, DataBaseAccounts* accounts, DataBaseBanks* banks, DataBaseClients* clients)
        : mode_(Mode::BankMenu), bank_name_(""), accounts_{accounts}, banks_{banks}, clients_{clients},
          bank_(nullptr), visitor_(nullptr), worker_visitor_(nullptr), out_{out}, in_{in}
  {}

  ~Executable() {
    if (bank_) {
      banks_->WriteBank(*bank_);
      delete bank_;
    }
    if (visitor_) {
      delete visitor_;
    }
    if (worker_visitor_) {
      delete worker_visitor_;
    }
  }

  void Start() {
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

  void BankMenu() {
    std::string message = "Choose what do you want to do:\n"
                          "1 - Create new bank\n"
                          "2 - Go to bank\n"
                          "3 - Exit\n"
                          "4 - New date";
    int64_t choose;
    Builder::GetNumber(1, 4, choose, out_, in_, message);
    if (choose == 1) {
      banks_->WriteBank(Builder::BuildBank(out_, in_, banks_));
    } else if (choose == 4) {
      ++system_date;
    } else if (choose == 2) {
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
          delete bank_;
        }
        bank_ = new Bank(banks_->GetBank(bank_name_));
        mode_ = Mode::MainMenu;
      }
    } else {
      mode_ = Mode::Stop;
    }
  }

  void MainMenu() {
    std::string message = "Choose what do you want to do:\n"
                          "1 - Enter as a visitor\n"
                          "2 - Enter as a worker\n"
                          "3 - Make request\n"
                          "4 - Go to previous Menu\n"
                          "5 - Create a visitor\n"
                          "6 - Create a worker (in progress)";
    int64_t choose;
    Builder::GetNumber(1, 5, choose, out_, in_, message);
    if (choose == 1) {
      mode_ = Mode::VisitorSession;
    } else if (choose == 2) {
      mode_ = Mode::WorkerSession;
    } else if (choose == 3) {
      MakeRequest();
    } else if (choose == 4) {
      mode_ = Mode::BankMenu;
    } else if (choose == 5) {
      clients_->WriteClient(bank_name_, Builder::BuildClient(out_, in_, bank_->GetClientID()));
    } else {
      //Builder::BuildWorker(out_, in_, bank_->)
    }
  }

  void VisitorSession() {
    int64_t id;
    int64_t pas;
    {
      std::string message = "Enter your id (enter -1 to exit) :";
      Builder::GetNumber(-1, 10'000, id, out_, in_, message);
      if (id == -1) {
        mode_ = Mode::MainMenu;
        return;
      }
      message = "Enter your password: ";
      out_->Output(message);
      pas = in_->InputNumber();
    }
    Client client = clients_->GetCLient(bank_name_, id);
    if (client.GetStatus() == Status::Blocked) {
      out_->Output("You are blocked. Please report to the administrator");
      mode_ = Mode::MainMenu;
      return;
    }
    if (visitor_ != nullptr) {
      delete visitor_;
    }
    visitor_ = new Visitor();
    bool visit = visitor_->MakeVisit(bank_name_, id, pas, clients_);
    if (visit) {
      bool flag = true;
      while (flag) {
        std::string message = "Menu:\n"
                              "1 - Exit\n"
                              "2 - Change passport\n"
                              "3 - Open new account\n"
                              "4 - Check my accounts\n"
                              "5 - Make transaction";
        int64_t choose;
        Builder::GetNumber(1, 5, choose, out_, in_, message);
        if (choose == 1) {
          flag = false;
          visitor_->Exit();
        } else if (choose == 2) {
          visitor_->ChangePassportData(in_, out_);
        } else if (choose == 3) {
          visitor_->OpenAccount(in_, out_, bank_->GetCreditLimit(), bank_->GetBankFee(), accounts_, bank_->GetAccountID());
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

  void ShowAccounts(size_t client_id) {
    auto accounts = accounts_->GetUserAccounts(bank_name_, client_id);
    for (auto account : accounts) {
      std::string acc_type = " ( ";
      if (dynamic_cast<CreditAccount*>(account) != nullptr) {
        acc_type += "Credit account (minimum is " + std::to_string(bank_->GetCreditLimit()) + ") )";
      } else if (dynamic_cast<DepositeAccount*>(account) != nullptr) {
        acc_type += "Deposite account )";
      } else {
        acc_type += "Debit account )";
      }
      std::string acc_info = "Id: " + std::to_string(account->GetAccountId()) + "    Money: " + std::to_string(account->GetBalance()) + acc_type;
      out_->Output(acc_info);
    }
    for (auto acc : accounts) {
      delete acc;
    }
  }

  void MakeTransaction() {
    int64_t cl_id_1, acc_id_1, cl_id_2, acc_id_2, money;

    std::string message = "Write your id (write -1 to return):";
    Builder::GetNumber(-1, INT64_MAX, cl_id_1, out_, in_, message);
    if (cl_id_1 == -1) {
      return;
    }

    ShowAccounts(cl_id_1);

    for (auto account : accounts_->GetUserAccounts(bank_name_, cl_id_1)) {
      std::string acc_type = " ( ";
      if (dynamic_cast<CreditAccount*>(account) != nullptr) {
        acc_type += "Credit account (minimum is " + std::to_string(bank_->GetCreditLimit()) + ") )";
      } else if (dynamic_cast<DepositeAccount*>(account) != nullptr) {
        acc_type += "Deposite account )";
      } else {
        acc_type += "Debit account )";
      }
      std::string acc_info = "Id: " + std::to_string(account->GetAccountId()) + "    Money: " + std::to_string(account->GetBalance()) + acc_type;
      out_->Output(acc_info);
    }
    message = "What account do you want to use? (write -1 to return)";
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

    bool done = visitor_->MakeTransaction(static_cast<size_t>(cl_id_1), static_cast<size_t>(acc_id_1),
                                          static_cast<size_t>(cl_id_2), static_cast<size_t>(acc_id_2),
                                          money, accounts_);
    if (done) {
      out_->Output("Everything is ok!");
    } else {
      out_->Output("Something went wrong, please report to the administrator or try again.");
    }
    mode_ = Mode::VisitorSession;
  }

  void WorkerSession() {
    /////
  }

  void MakeRequest() {
    mode_ = Mode::MainMenu;
    std::string message = "What is your id? To return write 0";
    int64_t user_id;
    Builder::GetNumber(0, INT64_MAX, user_id, out_, in_, message);
    if (user_id == 0) {
      return;
    }
    Builder::BuildRequest(out_, in_, bank_name_, user_id).WriteRequest();
  }


 private:

  enum class Mode {
    Stop = 0,
    BankMenu,
    MainMenu,
    VisitorSession,
    WorkerSession,
  };
  Mode mode_;
  std::string bank_name_;
  DataBaseAccounts* accounts_;
  DataBaseBanks* banks_;
  DataBaseClients* clients_;
  Bank* bank_;
  Visitor* visitor_;
  WorkerVisitor* worker_visitor_;
  Show* out_;
  Get* in_;

};


#endif //BANK_SYSTEM__EXECUTABLE_H_
