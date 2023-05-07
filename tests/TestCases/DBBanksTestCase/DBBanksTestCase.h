#pragma once

#include <gtest/gtest.h>

#include "../../../DataBases/Interfaces/DataBaseBanks.h"
#include "../../../DataBases/JsonDataBases/JsonDBBanks.h"

class DBBANKS_TEST_CASE : public ::testing::Test {
 public:
  static std::shared_ptr<DataBaseBanks> banks_bd;
  static std::string bank_name;

  static void SetUpTestSuite();
  static void TearDownTestSuite();

  void TearDown() override;
};