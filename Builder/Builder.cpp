#include "Builder.h"

void Builder::GetFilledString(std::string &to_fill, std::unique_ptr<Show> &out,
                              std::unique_ptr<Get> &in,
                              const std::string &message) {
  while (true) {
    out->Output(message);
    to_fill = in->InputString();
    if (!to_fill.empty()) {
      return;
    }
  }
}

void Builder::GetNumber(int64_t b1, int64_t b2, int64_t &num,
                        std::unique_ptr<Show> &out, std::unique_ptr<Get> &in,
                        const std::string &message) {
  /// get number_ from [b1, b2]
  while (true) {
    out->Output(message);
    num = in->InputNumber();
    if (num <= b2 && num >= b1) {
      return;
    }
  }
}

void Builder::GetBigInteger(const BigInteger &b1, const BigInteger &b2,
                            BigInteger &num, std::unique_ptr<Show> &out,
                            std::unique_ptr<Get> &in,
                            const std::string &message) {
  /// get number_ from [b1, b2]
  while (true) {
    out->Output(message);
    num = BigInteger(std::move(in->InputString()));
    if (num <= b2 && num >= b1) {
      return;
    }
  }
}

std::shared_ptr<Account>
Builder::BuildAccount(std::unique_ptr<Show> &out, std::unique_ptr<Get> &in,
                      const Date &system_date, size_t account_id,
                      const BigInteger &cred_lim, const BigInteger &bank_fee) {
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
    std::string message =
        "How many years do you want to keep money in our bank (from 1 to 10):";
    GetNumber(1, 10, years, out, in, message);

    message = "How much money you are ready to invest:";
    GetNumber(0, INT64_MAX, money, out, in, message);

    return std::shared_ptr<Account>{
        DepositFabric(system_date + Date(static_cast<int>(years), 0, 0))
            .MakeAccount(account_id, money, system_date)};
  }

  BigInteger money = -1;
  std::string message = "How much money you are ready to invest:";
  GetBigInteger(0, BigInteger(std::string(100, '9')), money, out, in, message);

  if (type == 2) {
    /// Debit account
    return DebitFabric().MakeAccount(account_id, money, system_date);
  }

  /// Credit account
  CreditFabric fabric{cred_lim, bank_fee};
  return fabric.MakeAccount(account_id, money, system_date);
}

Bank Builder::BuildBank(std::unique_ptr<Show> &out, std::unique_ptr<Get> &in,
                        std::unique_ptr<DataBaseBanks> &banks) {
  std::string message = "What is the name of your bank?";
  std::string name;
  bool not_found = true;
  while (not_found) {
    GetFilledString(name, out, in, message);
    if (!banks->FindBank(name)) {
      not_found = false;
    }
  }
  message = "What credit limit do you want to set? (not less than 0)";
  BigInteger limit;
  GetBigInteger(0, BigInteger("1" + std::string(100, '0')), limit, out, in,
                message);
  limit *= -1;

  message = "What bank fee do you want to set? (no more than (limit / 5))";
  BigInteger fee;
  GetBigInteger(0, (-limit) / 5 + 1, fee, out, in, message);

  message = "What deposit percent do you want to set? (from 0% to 10'000%)";
  int64_t percent;
  GetNumber(0, 10'000, percent, out, in, message);

  return {std::move(name), limit, fee, static_cast<int>(percent)};
}

Client Builder::BuildClient(std::unique_ptr<Show> &out,
                            std::unique_ptr<Get> &in, size_t id) {
  Passport passport = BuildPassport(out, in);

  std::string password;
  std::string message =
      "What password would you use? (without spaces).\nPlease remember it.";
  GetFilledString(password, out, in, message);

  return {id, std::move(password), passport};
}

Passport Builder::BuildPassport(std::unique_ptr<Show> &out,
                                std::unique_ptr<Get> &in) {
  int number = -2;
  int series = -2;
  std::string name;
  std::string surname;
  std::string address;

  out->Output("Please leave us your passport information:");

  std::string message = "Enter your name (necessary)";
  GetFilledString(name, out, in, message);

  message = "Enter your surname (necessary)";
  GetFilledString(surname, out, in, message);

  message = "Enter your passport number (optional, write -1 to skip)";
  while (!(number >= -1 && number < 10'000)) {
    out->Output(message);
    number = static_cast<int>(in->InputNumber());
  }

  message = "Enter your passport series (optional, write -1 to skip)";
  while (!(series >= -1 && series < 1'000'000)) {
    out->Output(message);
    series = static_cast<int>(in->InputNumber());
  }

  out->Output("Enter your address (without spaces, use commas), (optional, "
              "write 0 to skip):");
  address = in->InputString();

  return {number, series, std::move(name), std::move(surname),
          std::move(address)};
}

Request Builder::BuildRequest(std::unique_ptr<Show> &out,
                              std::unique_ptr<Get> &in,
                              const std::string &bank_name, size_t id) {
  std::string message = "Please describe us your problem in CamelCase.";
  std::string text;
  GetFilledString(text, out, in, message);
  return {bank_name, id, text};
}

Worker Builder::BuildWorker(std::unique_ptr<Show> &out,
                            std::unique_ptr<Get> &in, size_t id) {
  std::string password;
  std::string message =
      "What password would you use? (without spaces).\nPlease remember it.";
  GetFilledString(password, out, in, message);

  out->Output("Thank you! Your id is :");
  out->Output(static_cast<int64_t>(id));
  out->Output("Please write it down and don't lose.");

  return {id, std::move(password)};
}