#include "JsonDBBanks.h"

BigInteger JsonDBBanks::GetBigintFromJson(const json& str) {
  std::string dirty_string = str.dump();
  return BigInteger{dirty_string.substr(1, dirty_string.size() - 2)};
}

void JsonDBBanks::WriteBank(const Bank& bank) {
  std::string working_path = "Data/" + bank.GetName();
  Filesystem::CheckDirectory(working_path);
  working_path += "/bank_info.json";
  Filesystem::CheckFile(working_path);
  std::ofstream f_out(working_path);
  json bank_info = json::array({bank.GetName(), bank.GetCreditLimit().toString(),
                                bank.GetBankFee().toString(), bank.GetDepositPercent(),
                                bank.GetAccountID_CONST(), bank.GetClientID_CONST(),
                                bank.GetWorkerID_CONST()});

  /*      Bank information indexes in json:
  *
  * 0 - Bank name
  * 1 - Credit limit
  * 2 - Bank fee
  * 3 - Deposite percent
  * 4 - Generator integer for accounts
  * 5 - Generator integer for visitors
  * 6 - Generator integer for workers
  *
  */

  f_out << std::setw(4) << bank_info;
  f_out.close();
}

bool JsonDBBanks::FindBank(const std::string& bank_name) {
  std::string working_path = "Data/" + bank_name + "/bank_info.json";
  if (!std::filesystem::exists(working_path)) {
    return false;
  }
  return true;
}

std::shared_ptr<Bank> JsonDBBanks::GetBank(const std::string& bank_name) {
  if (FindBank(bank_name)) {
    std::string working_path = "Data/" + bank_name + "/bank_info.json";
    json bank_info;
    std::ifstream f_in(working_path);
    f_in >> bank_info;
    if (bank_info.size() != 7) {
      std::cerr << "Data lost or broken ( Data/" + bank_name + "/bank_info.json ) !!! Can't parse info." << std::endl;
      return {nullptr};
    }
    return std::make_shared<Bank>(bank_info[0], GetBigintFromJson(bank_info[1]), GetBigintFromJson(bank_info[2]),
                    bank_info[3], bank_info[4], bank_info[5], bank_info[6]);
  }
  return {nullptr};
}

std::vector<std::shared_ptr<Bank>> JsonDBBanks::GetBanks() {
  std::vector<std::shared_ptr<Bank>> res;
  for (auto& dir : std::filesystem::directory_iterator("Data")) {
    std::string bank_name = dir.path().string().substr(5);
    std::shared_ptr<Bank> cur(std::move(GetBank(bank_name)));
    if (cur) {
      res.push_back(cur);
    } else {
      std::cerr << "Data/" + bank_name + "/bank_info.json not found !!!" << std::endl;
    }
  }
  return res;
}
