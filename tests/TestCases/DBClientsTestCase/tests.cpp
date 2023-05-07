#include <gtest/gtest.h>
#include "DBClientsTestCase.h"

std::shared_ptr<DataBaseClients> DBCLIENTS_TEST_CASE::clients_bd(nullptr);
std::string DBCLIENTS_TEST_CASE::bank_name = "impossible_name_for_bank";

void DBCLIENTS_TEST_CASE::SetUpTestSuite() {
  clients_bd.reset(new JsonDBClients());
}

void DBCLIENTS_TEST_CASE::TearDownTestSuite() {
  std::string data = "Data";
  if (std::filesystem::exists(data) && std::filesystem::is_empty(data)) {
    std::filesystem::remove(data);
  }
}

void DBCLIENTS_TEST_CASE::TearDown() {
  std::filesystem::remove_all("Data/" + bank_name);
}

TEST_F(DBCLIENTS_TEST_CASE, functional_test_write_read) {
  Passport passport{1, 1, "a", "b", "c"};
  Client cl_1{1, "1234", passport};
  Client cl_2{2, "1234", passport};

  clients_bd->WriteClient(bank_name, cl_1);
  clients_bd->WriteClient(bank_name, cl_2);

  std::shared_ptr<Client> got_cl_1 = clients_bd->GetClient(bank_name, 1);
  ASSERT_TRUE(got_cl_1 != nullptr && cl_1 == *got_cl_1);

  std::shared_ptr<Client> got_cl_2 = clients_bd->GetClient(bank_name, 2);
  ASSERT_TRUE(got_cl_2 != nullptr && cl_2 == *got_cl_2);
}

TEST_F(DBCLIENTS_TEST_CASE, functional_test_delete) {
  Passport passport{1, 1, "a", "b", "c"};
  Client cl{1, "1234", passport};

  clients_bd->WriteClient(bank_name, cl);

  std::shared_ptr<Client> got_cl_1 = clients_bd->GetClient(bank_name, 1);
  ASSERT_TRUE(got_cl_1.get() != nullptr && cl == *got_cl_1);

  clients_bd->DeleteClient(bank_name, 1);

  std::shared_ptr<Client> got_cl_2 = clients_bd->GetClient(bank_name, 1);
  ASSERT_TRUE(got_cl_2.get() == nullptr);
}

TEST_F(DBCLIENTS_TEST_CASE, little_performance_test) {
  for (int i = 1; i <= 1000; ++i) {
    Passport passport{i, i * 10, "a", "b", "c"};
    Client cl(i, "1234", passport);
    clients_bd->WriteClient(bank_name, cl);
  }
  for (int i = 1; i <= 1000; ++i) {
    Passport passport{i, i * 10, "a", "b", "c"};
    Client cl(i, "1234", passport);
    std::shared_ptr<Client> got_cl = clients_bd->GetClient(bank_name, i);
    ASSERT_TRUE(got_cl.get() != nullptr && cl == *got_cl);
  }
}