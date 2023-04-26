#include <gtest/gtest.h>
#include "DBWorkersTestCase.h"

DataBaseWorkers* DBWORKERS_TEST_CASE::workers_bd = nullptr;
std::string DBWORKERS_TEST_CASE::bank_name = "impossible_name_for_bank";
std::string DBWORKERS_TEST_CASE::bank_password = "impossible_password";

void DBWORKERS_TEST_CASE::SetUpTestSuite() {
  workers_bd = new JsonDBWorkers();
}

void DBWORKERS_TEST_CASE::TearDownTestSuite() {
  delete workers_bd;
  workers_bd = nullptr;
  std::string data = "Data";
  if (std::filesystem::exists(data) && std::filesystem::is_empty(data)) {
    std::filesystem::remove(data);
  }
}

void DBWORKERS_TEST_CASE::TearDown() {
  std::filesystem::remove_all("Data/" + bank_name + "_test_1");
  std::filesystem::remove_all("Data/" + bank_name + "_test_2");
}

TEST_F(DBWORKERS_TEST_CASE, functional_test_write_read) {
  size_t worker_id = 1;
  std::string cur_test_bank_name = bank_name + "_test_1";
  workers_bd->AddNewBank(cur_test_bank_name, bank_password);

  Worker worker(worker_id, 123);
  workers_bd->WriteWorker(cur_test_bank_name, bank_password, worker);
  Worker* got_wk = workers_bd->GetWorker(cur_test_bank_name, worker_id);
  ASSERT_TRUE(got_wk != nullptr &&
              worker.GetId() == got_wk->GetId() &&
              worker.GetPassword() == got_wk->GetPassword());
}

TEST_F(DBWORKERS_TEST_CASE, functional_test_delete) {
  size_t worker_id = 1;
  std::string cur_test_bank_name = bank_name + "_test_2";
  workers_bd->AddNewBank(cur_test_bank_name, bank_password);

  Worker worker(1, 123);
  workers_bd->WriteWorker(cur_test_bank_name, bank_password, worker);

  Worker* got_wk_1 = workers_bd->GetWorker(cur_test_bank_name, worker_id);
  ASSERT_TRUE(got_wk_1 != nullptr &&
      worker.GetId() == got_wk_1->GetId() &&
      worker.GetPassword() == got_wk_1->GetPassword());
  delete got_wk_1;

  workers_bd->DeleteWorker(cur_test_bank_name, bank_password, worker_id);

  Worker* got_wk_2 = workers_bd->GetWorker(cur_test_bank_name, worker_id);
  ASSERT_TRUE(got_wk_2 == nullptr);
  delete got_wk_2;
}