#include <gtest/gtest.h>
#include "../../../Bank/Bank.h"

TEST(TEST_BANK, check_copy) {
  Bank bank_1{"igor_bank", -10, 5, 1};
  Bank bank_2(bank_1);
  ASSERT_EQ(bank_1.GetName(),             bank_2.GetName());
  ASSERT_EQ(bank_1.GetBankFee(),          bank_2.GetBankFee());
  ASSERT_EQ(bank_1.GetDepositPercent(),   bank_2.GetDepositPercent());
  ASSERT_EQ(bank_1.GetCreditLimit(),      bank_2.GetCreditLimit());
  ASSERT_EQ(bank_1.GetAccountID_CONST(),  bank_2.GetAccountID_CONST());
  ASSERT_EQ(bank_1.GetClientID_CONST(),   bank_2.GetClientID_CONST());
  ASSERT_EQ(bank_1.GetWorkerID_CONST(),   bank_2.GetWorkerID_CONST());
}

TEST(TEST_BANK, check_id_increment) {
  Bank bank{"igor_bank", -100, 8, 11};
  for (int i = 1; i <= 1'000; ++i) {
    ASSERT_EQ(i, bank.GetAccountID());
    ASSERT_EQ(i, bank.GetWorkerID());
    ASSERT_EQ(i, bank.GetClientID());
  }
  ASSERT_EQ(1'000, bank.GetAccountID_CONST());
  ASSERT_EQ(1'000, bank.GetWorkerID_CONST());
  ASSERT_EQ(1'000, bank.GetClientID_CONST());
}