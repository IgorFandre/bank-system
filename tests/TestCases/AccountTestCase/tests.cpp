#include <GTest/gtest.h>
#include "../../../Account/AccountFabric.h"

TEST(TEST_ACCOUNT, update_credit_1) {
  Date open{1, 1, 1}, last{2, 2, 2}, sys{2, 2, 3};
  CreditAccount acc{1, 0, 0, 0, open, last};
  acc.Update(sys);
  ASSERT_EQ(acc.GetLastUsageDate(), sys);
  ASSERT_EQ(0, acc.GetBalance());
}

TEST(TEST_ACCOUNT, update_credit_2) {
  Date open{1, 1, 1}, last{2, 2, 2}, sys{2, 2, 5};
  CreditAccount acc{1, -100, -1000, 10, open, last};
  acc.Update(sys);
  ASSERT_EQ(acc.GetLastUsageDate(), sys);
  ASSERT_EQ(-130, acc.GetBalance());
}

TEST(TEST_ACCOUNT, update_debit) {
  Date open{1, 1, 1}, last{2, 2, 2}, sys{2, 2, 3};
  DebitAccount acc{1, 100, open, last};
  acc.Update(sys);
  ASSERT_EQ(acc.GetLastUsageDate(), sys);
}

TEST(TEST_ACCOUNT, update_deposit) {
  Date open{1, 1, 1}, last{2, 2, 2},
        finish{10, 1, 1}, sys{2, 2, 3};
  DepositAccount acc{1, 100, finish, open, last};
  acc.Update(sys);
  ASSERT_EQ(acc.GetLastUsageDate(), sys);

  sys = Date(10, 1, 2);
  acc.Update(sys);
  ASSERT_EQ(acc.GetReduceStatus(), true);
}

TEST(TEST_ACCOUNT, transaction_credit) {
  Date open{1, 1, 1}, last{2, 2, 2}, sys{2, 2, 3};

  CreditAccount acc_1{1, 0, 0, 0, open, last};
  ASSERT_TRUE(acc_1.Transaction(100, sys));
  ASSERT_EQ(acc_1.GetLastUsageDate(), sys);
  ASSERT_EQ(100, acc_1.GetBalance());

  CreditAccount acc_2{1, 0, 0, 0, open, last};
  ASSERT_FALSE(acc_2.Transaction(-100, sys));
  ASSERT_EQ(acc_2.GetLastUsageDate(), sys);
  ASSERT_EQ(0, acc_2.GetBalance());

  CreditAccount acc_3{1, 0, -100, 0, open, last};
  ASSERT_TRUE(acc_3.Transaction(-100, sys));
  ASSERT_EQ(acc_3.GetLastUsageDate(), sys);
  ASSERT_EQ(-100, acc_3.GetBalance());
}

TEST(TEST_ACCOUNT, transaction_debit) {
  Date open{1, 1, 1}, last{2, 2, 2}, sys{2, 2, 3};
  DebitAccount acc_1{1, 0, open, last};
  ASSERT_TRUE(acc_1.Transaction(100, sys));
  ASSERT_EQ(acc_1.GetLastUsageDate(), sys);
  ASSERT_EQ(100, acc_1.GetBalance());

  DebitAccount acc_2{1, 0, open, last};
  ASSERT_FALSE(acc_2.Transaction(-100, sys));
  ASSERT_EQ(acc_2.GetLastUsageDate(), sys);
  ASSERT_EQ(0, acc_2.GetBalance());
}

TEST(TEST_ACCOUNT, transaction_deposit) {
  Date open{1, 1, 1}, last{2, 2, 2},
      finish{10, 1, 1}, sys{2, 2, 3};
  DepositAccount acc{1, 100, finish, open, last};
  acc.Update(sys);
  ASSERT_EQ(acc.GetLastUsageDate(), sys);
  ASSERT_FALSE(acc.Transaction(-10, sys));
  ASSERT_TRUE(acc.Transaction(10, sys));

  sys = Date(10, 1, 2);
  ASSERT_TRUE(acc.Transaction(-10, sys));
  ASSERT_EQ(acc.GetBalance(), 100);
}