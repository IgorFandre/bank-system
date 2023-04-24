#pragma once

#include <gtest/gtest.h>

class FILESYSTEM_TEST_CASE : public ::testing::Test {
 public:
  static const std::string testing_dir;

  void SetUp() override;
  void TearDown() override;
};