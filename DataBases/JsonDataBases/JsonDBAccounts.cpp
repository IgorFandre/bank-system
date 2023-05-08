#include "JsonDBAccounts.h"

BigInteger JsonDBAccounts::GetBigintFromJson(const json &str) {
  std::string dirty_string = str.dump();
  return BigInteger{dirty_string.substr(1, dirty_string.size() - 2)};
}

void JsonDBAccounts::WriteAccount(const std::string &bank_name, size_t user_id,
                                  std::shared_ptr<Account> account) {
  if (!account) {
    std::cerr << "Invalid pointer in WriteAccount json" << std::endl;
    return;
  }
  if (account->GetType() == Account::Type::Empty) {
    std::cerr << "You've just posted cringe (Empty account)" << std::endl;
  }
  Date d1 = account->GetOpenDate();
  Date d2 = account->GetLastUsageDate();
  json account_info = json::array({account->GetType(), account->GetAccountId(),
                                   account->GetBalance().toString(),
                                   d1.GetYear(), d1.GetMonth(), d1.GetDay(),
                                   d2.GetYear(), d2.GetMonth(), d2.GetDay()});

  /*      Debit account indexes in json:
   *
   * 0 - Account::Type::Debit
   * 1 - Accounts id
   * 2 - Account balance
   * [3 : 5] - Open date_ (year, month, day)
   * [6 : 8] - Last usage date_ (year, month, day)
   * 9 - Credit limit (minimum balance)
   * 10 - Bank fee in case balance < 0
   *
   */

  if (account->GetType() == Account::Type::Deposit) {
    auto *acc(dynamic_cast<DepositAccount *>(account.get()));

    /*      Deposit account indexes in json:
     *
     * 0 - Account::Type::Deposit
     * 1 - Accounts id
     * 2 - Account balance
     * [3 : 5] - Open date_ (year, month, day)
     * [6 : 8] - Last usage date_ (year, month, day)
     * [9 : 11] - Finish deposite date_ (year, month, day)
     *
     */

    Date d3 = acc->GetFinishDate();
    account_info.push_back(d3.GetYear());
    account_info.push_back(d3.GetMonth());
    account_info.push_back(d3.GetDay());
  } else if (account->GetType() == Account::Type::Credit) {

    /*      Credit account indexes in json:
     *
     * 0 - Account::Type::Credit
     * 1 - Accounts id
     * 2 - Account balance
     * [3 : 5] - Open date_ (year, month, day)
     * [6 : 8] - Last usage date_ (year, month, day)
     * 9 - Credit limit (minimum balance)
     * 10 - Bank fee in case balance < 0
     *
     */

    auto *acc(dynamic_cast<CreditAccount *>(account.get()));
    account_info.push_back(acc->GetCreditLimit().toString());
    account_info.push_back(acc->GetBankFee().toString());
  }
  std::string working_path = "Data/" + bank_name;
  Filesystem::CheckDirectory(working_path);
  working_path += "/Accounts";
  Filesystem::CheckDirectory(working_path);
  working_path += "/" + std::to_string(user_id);
  Filesystem::CheckDirectory(working_path);
  working_path += "/accounts.json";
  json accounts;
  if (Filesystem::CheckFileForReadingJson(working_path)) {
    std::ifstream f_in(working_path);
    f_in >> accounts;
    bool found = false;
    for (size_t i = 0; i < accounts.size(); ++i) {
      if (accounts[i][0] == account_info[0] &&
          accounts[i][1] == account_info[1]) {
        found = true;
        accounts[i] = account_info;
        break;
      }
    }
    if (!found) {
      accounts.push_back(account_info);
    }
  } else {
    accounts.push_back(account_info);
  }
  std::fstream clear_file(working_path, std::ios::out);
  clear_file.close();
  std::ofstream f_out(working_path);
  f_out << std::setw(4) << accounts;
  f_out.close();
}

void JsonDBAccounts::WriteAccounts(
    const std::string &bank_name, size_t user_id,
    const std::vector<std::shared_ptr<Account>> &accounts) {
  for (size_t i = 0; i < accounts.size(); ++i) {
    WriteAccount(bank_name, user_id, std::shared_ptr<Account>(accounts[i]));
  }
}

void JsonDBAccounts::DeleteClientAccounts(const std::string &bank_name,
                                          size_t user_id) {
  std::string working_path = "Data/" + bank_name + "/Accounts/" +
                             std::to_string(user_id) + "/accounts.json";
  if (std::filesystem::exists(working_path)) {
    std::filesystem::remove(working_path);
  }
}

std::shared_ptr<Account>
JsonDBAccounts::GetAccount(const std::string &bank_name, size_t user_id,
                           size_t account_id) {
  std::string working_path = "Data/" + bank_name + "/Accounts/" +
                             std::to_string(user_id) + "/accounts.json";
  if (Filesystem::CheckFileForReadingJson(working_path)) {
    json accounts;
    std::ifstream f_in(working_path);
    f_in >> accounts;
    for (size_t i = 0; i < accounts.size(); ++i) {
      if (accounts[i][1] == account_id) {
        Date open_date(accounts[i][3], accounts[i][4], accounts[i][5]);
        Date last_date(accounts[i][6], accounts[i][7], accounts[i][8]);
        if (accounts[i][0] == Account::Type::Credit) {
          return std::shared_ptr<Account>{dynamic_cast<Account *>(
              new CreditAccount(account_id, GetBigintFromJson(accounts[i][2]),
                                GetBigintFromJson(accounts[i][9]),
                                GetBigintFromJson(accounts[i][10]), open_date,
                                last_date))};
        } else if (accounts[i][0] == Account::Type::Deposit) {
          Date finish_date(accounts[i][9], accounts[i][10], accounts[i][11]);
          return std::shared_ptr<Account>{dynamic_cast<Account *>(
              new DepositAccount(account_id, GetBigintFromJson(accounts[i][2]),
                                 finish_date, open_date, last_date))};
        } else {
          return std::shared_ptr<Account>{dynamic_cast<Account *>(
              new DebitAccount(account_id, GetBigintFromJson(accounts[i][2]),
                               open_date, last_date))};
        }
      }
    }
  }
  return {nullptr};
}

std::vector<std::shared_ptr<Account>>
JsonDBAccounts::GetUserAccounts(const std::string &bank_name, size_t user_id) {
  std::string working_path = "Data/" + bank_name + "/Accounts/" +
                             std::to_string(user_id) + "/accounts.json";
  if (!std::filesystem::exists(working_path)) {
    return {};
  }
  std::vector<std::shared_ptr<Account>> res;
  json accounts;
  std::ifstream f_in(working_path);
  f_in >> accounts;
  for (size_t i = 0; i < accounts.size(); ++i) {
    Date open_date(accounts[i][3], accounts[i][4], accounts[i][5]);
    Date last_date(accounts[i][6], accounts[i][7], accounts[i][8]);
    if (accounts[i][0] == Account::Type::Credit) {
      res.push_back(
          std::shared_ptr<Account>{dynamic_cast<Account *>(new CreditAccount(
              accounts[i][1], GetBigintFromJson(accounts[i][2]),
              GetBigintFromJson(accounts[i][9]),
              GetBigintFromJson(accounts[i][10]), open_date, last_date))});
    } else if (accounts[i][0] == Account::Type::Deposit) {
      Date finish_date(accounts[i][9], accounts[i][10], accounts[i][11]);
      res.push_back(std::shared_ptr<Account>{dynamic_cast<Account *>(
          new DepositAccount(accounts[i][1], GetBigintFromJson(accounts[i][2]),
                             finish_date, open_date, last_date))});
    } else {
      res.push_back(std::shared_ptr<Account>{dynamic_cast<Account *>(
          new DebitAccount(accounts[i][1], GetBigintFromJson(accounts[i][2]),
                           open_date, last_date))});
    }
  }
  return res;
}