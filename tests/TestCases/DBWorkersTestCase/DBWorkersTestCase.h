#pragma once

#include <gtest/gtest.h>

#include "../../../DataBases/Interfaces/DataBaseWorkers.h"
#include "../../../DataBases/JsonDataBases/JsonDBWorkers.h"

class DBWORKERS_TEST_CASE : public ::testing::Test {
 public:
  static std::shared_ptr<DataBaseWorkers> workers_bd;
  static std::string bank_name;
  static std::string bank_password;

  static void SetUpTestSuite();
  static void TearDownTestSuite();

  void TearDown() override;
};