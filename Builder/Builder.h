#ifndef BANK_SYSTEM_BUILDER_BUILDER_H_
#define BANK_SYSTEM_BUILDER_BUILDER_H_


#include "../Account/AccountFabric.h"
#include "../Bank/Bank.h"
#include "../Client/Client.h"
#include "../DataBases/Interfaces/DataBaseBanks.h"
#include "../Request/Request.h"
#include "../Worker/Worker.h"


class Builder {

 public:

  static void GetFilledString(std::string& to_fill, Show* out, Get* in, const std::string& message) {
    while (true) {
      out->Output(message);
      to_fill = in->InputString();
      out->Output("");
      if (!to_fill.empty()) {
        return;
      }
    }
  }

  static void GetNumber(int64_t b1, int64_t b2, int64_t& num, Show* out, Get* in, const std::string& message) {
    /// get number from [b1, b2]
    while (true) {
      out->Output(message);
      num = in->InputNumber();
      out->Output("");
      if (num <= b2 && num >= b1) {
        return;
      }
    }
  }

  static void GetString(std::string& str, Show* out, Get* in, const std::string& message) {
    while (true) {
      out->Output(message);
      str = in->InputString();
      out->Output("");
      if (str.empty()) {
        return;
      }
    }
  }

  static Account* BuildAccount(Show* out, Get* in, size_t account_id, int64_t cred_lim, int64_t bank_fee) {
    int64_t type = 0;
    {
      std::string message = "Choose the type of account you want to create:\n"
                            "1 - Deposit account\n"
                            "2 - Debit account\n"
                            "3 - Credit account";
      GetNumber(1, 3, type, out, in, message);
    }
    if (type == 1) { /// Deposit account
      int64_t years = 0;
      int64_t money = -1;
      std::string message = "How many years do you want to keep money in our bank (from 1 to 10):";
      GetNumber(1, 10, years, out, in, message);

      message = "How much money you are ready to invest:";
      GetNumber(0, INT64_MAX, money, out, in, message);

      return DepositeFabric(system_date
                            + Date(static_cast<int>(years), 0, 0)).MakeAccount(account_id, money);
    }

    int64_t money = -1;
    std::string message = "How much money you are ready to invest:";
    GetNumber(0, INT64_MAX, money, out, in, message);

    if (type == 2) {
      /// Debit account
      return DebitFabric().MakeAccount(account_id, money);
    }

    /// Credit account
    CreditFabric fabric{cred_lim, bank_fee};
    return fabric.MakeAccount(account_id, money);
  }

  static Bank BuildBank(Show* out, Get* in, DataBaseBanks* banks) {
    std::string message = "What is the name of your bank?";
    std::string name;
    bool not_found = true;
    while (not_found) {
      GetFilledString(name, out, in, message);
      if (!banks->FindBank(name)) {
        not_found = false;
      }
    }
    message = "What credit limit do you want to set?";
    int64_t limit;
    GetNumber(-10'000'000'000, 0, limit, out, in, message);

    message = "What bank fee do you want to set? (no more than (limit / 5) )";
    int64_t fee;
    GetNumber(0, (-limit) / 5 + 1, fee, out, in, message);

    message = "What deposite percent do you want to set?";
    int64_t percent;
    GetNumber(0, 10'000, percent, out, in, message);
    return {name, limit, fee, static_cast<int>(percent)};
  }

  static Client BuildClient(Show* out, Get* in, size_t id) {
    Passport passport = BuildPassport(out, in);

    int64_t password;
    std::string message = "What password would you use? (use number from -10^9 to 10^9).\nPlease remember it.";
    GetNumber(-1'000'000'000, 1'000'000'000, password, out, in, message);

    out->Output("Thank you! Your id is :");
    out->Output(static_cast<int64_t>(id));
    out->Output("Please write it down and don't lose.");

    return {id, password, passport};
  }

  static Passport BuildPassport(Show* out, Get* in) {
    int number = -1;
    int series = -1;
    std::string name;
    std::string surname;
    std::string address;

    out->Output("Please leave us your passport information:");

    std::string message = "Enter your name(necessary)";
    GetFilledString(name, out, in, message);

    message = "Enter your surname(necessary)";
    GetFilledString(surname, out, in, message);

    message = "Enter your passport number(optional)";
    while (!(number == 0 || (number >= 1'000 && number < 10'000))) {
      out->Output(message);
      number = static_cast<int>(in->InputNumber());
      out->Output("");
    }

    message = "Enter your passport series(optional)";
    while (!(series == 0 || (series >= 100'000 && series < 1'000'000))) {
      out->Output(message);
      series = static_cast<int>(in->InputNumber());
      out->Output("");
    }

    out->Output("Enter your address(optional)");
    address = in->InputString();
    out->Output("");

    return {number, series, name, surname, address};
  }

  static Request BuildRequest(Show* out, Get* in, const std::string& bank_name, size_t id) {
    std::string message = "Please describe us your problem in CamelCase.";
    std::string text;
    GetFilledString(text, out, in, message);
    return {bank_name, id, text};
  }

  static Worker BuildWorker(Show* out, Get* in, size_t id) {
    int64_t password;
    std::string message = "What password would you use? (use number from -10^9 to 10^9).\nPlease remember it.";
    GetNumber(-1'000'000'000, 1'000'000'000, password, out, in, message);

    out->Output("Thank you! Your id is :");
    out->Output(static_cast<int64_t>(id));
    out->Output("Please write it down and don't lose.");

    return {id, password};
  }


};



#endif //BANK_SYSTEM_BUILDER_BUILDER_H_
