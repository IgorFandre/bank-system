#pragma once

#include <gtest/gtest.h>

#include "../../../DataBases/Interfaces/DataBaseAccounts.h"
#include "../../../DataBases/JsonDataBases/JsonDBAccounts.h"

class DBACCOUNT_TEST_CASE : public ::testing::Test {
public:
  static std::shared_ptr<DataBaseAccounts> account_bd;
  static std::string bank_name;

  static void SetUpTestSuite();
  static void TearDownTestSuite();

  void TearDown() override;
};