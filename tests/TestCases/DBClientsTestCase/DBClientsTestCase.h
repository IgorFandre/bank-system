#pragma once

#include <gtest/gtest.h>

#include "../../../DataBases/Interfaces/DataBaseClients.h"
#include "../../../DataBases/JsonDataBases/JsonDBClients.h"

class DBCLIENTS_TEST_CASE : public ::testing::Test {
public:
  static std::shared_ptr<DataBaseClients> clients_bd;
  static std::string bank_name;

  static void SetUpTestSuite();
  static void TearDownTestSuite();

  void TearDown() override;
};