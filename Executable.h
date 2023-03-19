#ifndef BANK_SYSTEM__EXECUTABLE_H_
#define BANK_SYSTEM__EXECUTABLE_H_


#include "Bank/Bank.h"
#include "Builder/Builder.h"
#include "DataBases/Interfaces/DataBaseBanks.h"
#include "IOSystem/IOInterface.h"


class Executable {

 public:

  Executable(Show* out, Get* in, DataBaseBanks* data_base_banks)
        : out_{out}, in_{in}, banks_{data_base_banks}
  {}

  void BankMenu() {
    std::string message = "Choose what do you want to do:\n"
                          "1 - Create new bank\n"
                          "2 - Go to bank";
    int64_t choose;
    Builder::GetNumber(1, 2, choose, out_, in_, message);
    if (choose == 1) {
      AddBank();
    } else {
      MainMenu();
    }
  }

  void AddBank() {
    banks_->WriteBank(Builder::BuildBank(out_, in_, banks_));
  }

  void MainMenu() {
    std::string message = "Choose what do you want to do:\n"
                          "1 - Enter as a visitor\n"
                          "2 - Enter as a worker\n"
                          "3 - Make request\n"
                          "4 - Create a visitor\n"
                          "5 - Create a worker";
    int64_t choose;
    Builder::GetNumber(1, 5, choose, out_, in_, message);
    /// to be continued...
  }



 private:

  DataBaseBanks* banks_;
  Show* out_;
  Get* in_;

};


#endif //BANK_SYSTEM__EXECUTABLE_H_
