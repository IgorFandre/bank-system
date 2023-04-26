#include <gtest/gtest.h>
#include "DBAccountTestCase.h"

DataBaseAccounts* DBACCOUNT_TEST_CASE::account_bd = nullptr;
std::string DBACCOUNT_TEST_CASE::bank_name = "impossible_name_for_bank";

void DBACCOUNT_TEST_CASE::SetUpTestSuite() {
  account_bd = new JsonDBAccounts();
}

void DBACCOUNT_TEST_CASE::TearDownTestSuite() {
  delete account_bd;
  account_bd = nullptr;
  std::string data = "Data";
  if (std::filesystem::exists(data) && std::filesystem::is_empty(data)) {
    std::filesystem::remove(data);
  }
}

void DBACCOUNT_TEST_CASE::TearDown() {
  std::filesystem::remove_all("Data/" + bank_name);
}

TEST_F(DBACCOUNT_TEST_CASE, functional_test_write_read) {
  Date open{2000, 1, 1},
       last{2022, 3, 3},
       finish{2025, 1, 2};
  auto* acc_1 = new DebitAccount(1, 1000, open, last);
  auto* acc_2 = new DepositAccount(2, 1000, finish, open, last);

  account_bd->WriteAccount(bank_name, 1, acc_1);
  account_bd->WriteAccount(bank_name, 1, acc_2);

  acc_1 = new DebitAccount(1, 1000, open, last);
  acc_2 = new DepositAccount(2, 1000, finish, open, last);

  auto* got_acc_1 = dynamic_cast<DebitAccount*>(account_bd->GetAccount(bank_name, 1, 1));
  ASSERT_TRUE(got_acc_1 != nullptr && (*acc_1) == (*got_acc_1));
  delete got_acc_1;

  auto* got_acc_2 = dynamic_cast<DepositAccount*>(account_bd->GetAccount(bank_name, 1, 2));
  ASSERT_TRUE(got_acc_2 != nullptr && (*acc_2 == *got_acc_2));
  delete got_acc_2;

  account_bd->DeleteClientAccounts(bank_name, 1);
}

TEST_F(DBACCOUNT_TEST_CASE, functional_test_delete) {
  Date open{2000, 1, 1},
      last{2022, 3, 3};
  size_t user_id = 1000 - 7,
         acc_id = 1000 - 8;
  auto* acc = new DebitAccount(acc_id, 1000, open, last);

  account_bd->WriteAccount(bank_name, user_id, acc);

  acc = new DebitAccount(acc_id, 1000, open, last);

  auto* got_acc_1 = dynamic_cast<DebitAccount*>(account_bd->GetAccount(bank_name, user_id, acc_id));
  ASSERT_TRUE(got_acc_1 != nullptr && (*acc) == (*got_acc_1));
  delete got_acc_1;

  account_bd->DeleteClientAccounts(bank_name, user_id);

  auto* got_acc_2 = dynamic_cast<DepositAccount*>(account_bd->GetAccount(bank_name, user_id, acc_id));
  ASSERT_TRUE(got_acc_2 == nullptr);
  delete got_acc_2;
}

TEST_F(DBACCOUNT_TEST_CASE, little_performance_test) {
  Date open{2000, 1, 1},
      last{2022, 3, 3},
      finish{2025, 1, 2};
  size_t user_id = 100;
  size_t account_id_cnt = 1;
  for (int i = 0; i < 100; ++i) {
    account_bd->WriteAccount(bank_name, user_id, new DebitAccount(i + 1, 1000 + i, open, last));
  }
  for (int i = 0; i < 1000; ++i) {
    account_bd->WriteAccount(bank_name, user_id + i, new DepositAccount(1000 + i + 1, 1000 + i, finish, open, last));
  }
  for (int i = 0; i < 100; ++i) {
    Account* acc_1 = new DebitAccount(account_id_cnt++, 1000 + i, open, last);
    Account* acc_2 = account_bd->GetAccount(bank_name, user_id, i + 1);
    ASSERT_TRUE((*dynamic_cast<DebitAccount*>(acc_1)) == (*dynamic_cast<DebitAccount*>(acc_2)));
    delete acc_1;
    delete acc_2;
  }
  for (int i = 0; i < 1000; ++i) {
    Account* acc_1 = new DepositAccount(1000 + i + 1, 1000 + i, finish, open, last);
    Account* acc_2 = account_bd->GetAccount(bank_name, user_id + i, 1000 + i + 1);
    ASSERT_TRUE((*dynamic_cast<DepositAccount*>(acc_1)) == (*dynamic_cast<DepositAccount*>(acc_2)));
    delete acc_1;
    delete acc_2;
  }
}