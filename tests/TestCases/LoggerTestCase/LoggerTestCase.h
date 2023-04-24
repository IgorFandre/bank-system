#pragma once

#include <gtest/gtest.h>

class LOGGER_TEST_CASE : public ::testing::Test {
 public:

  static void SetUpTestSuite();
  static void TearDownTestSuite();

  void TearDown() override;
};