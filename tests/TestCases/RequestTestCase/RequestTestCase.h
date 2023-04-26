#pragma once

#include <gtest/gtest.h>

class REQUEST_TEST_CASE : public ::testing::Test {
 public:
  static std::string bank_name;

  static void SetUpTestSuite();
  static void TearDownTestSuite();

};