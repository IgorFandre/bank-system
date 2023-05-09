#include "DBBanksTestCase.h"

std::shared_ptr<DataBaseBanks> DBBANKS_TEST_CASE::banks_bd(nullptr);
std::string DBBANKS_TEST_CASE::bank_name = "impossible_name_for_bank";

void DBBANKS_TEST_CASE::SetUpTestSuite() { banks_bd.reset(new JsonDBBanks()); }

void DBBANKS_TEST_CASE::TearDownTestSuite() {
  std::string data = "Data";
  if (std::filesystem::exists(data) && std::filesystem::is_empty(data)) {
    std::filesystem::remove(data);
  }
}

void DBBANKS_TEST_CASE::TearDown() {
  std::filesystem::remove_all("Data/" + bank_name);
}

TEST_F(DBBANKS_TEST_CASE, functional_test) {
  std::string move_bank_name = bank_name;
  auto bank =
      Bank(std::forward<std::string>(move_bank_name), -100, 10, 10, 2, 2, 4);

  banks_bd->WriteBank(bank);

  std::shared_ptr<Bank> got_bank = banks_bd->GetBank(bank_name);
  ASSERT_EQ(got_bank->GetName(), bank_name);
  ASSERT_EQ(got_bank->GetClientID_CONST(), bank.GetClientID_CONST());
  ASSERT_EQ(got_bank->GetWorkerID_CONST(), bank.GetWorkerID_CONST());
  ASSERT_EQ(got_bank->GetAccountID_CONST(), bank.GetAccountID_CONST());
  ASSERT_EQ(got_bank->GetCreditLimit(), bank.GetCreditLimit());
  ASSERT_EQ(got_bank->GetDepositPercent(), bank.GetDepositPercent());
  ASSERT_EQ(got_bank->GetBankFee(), bank.GetBankFee());

  ASSERT_TRUE(banks_bd->FindBank(bank_name));
}