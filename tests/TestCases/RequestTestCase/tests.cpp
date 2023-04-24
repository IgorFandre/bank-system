#include <gtest/gtest.h>
#include "../../../Request/Request.h"
#include "RequestTestCase.h"

void REQUEST_TEST_CASE::SetUpTestSuite() {
  assert("Bank 'impossible_name_for_bank' exists. We can't test request." && !std::filesystem::exists("Data/impossible_name_for_bank"));
}

void REQUEST_TEST_CASE::TearDownTestSuite() {
  std::string data = "Data";
  if (std::filesystem::exists(data) && std::filesystem::is_empty(data)) {
    std::filesystem::remove(data);
  }
}

void REQUEST_TEST_CASE::TearDown() {
  std::filesystem::remove_all("Data/impossible_name_for_bank");
}

TEST_F(REQUEST_TEST_CASE, write_and_read_requests) {
  for (int i = 1; i <= 100; ++i) {
    Request req("impossible_name_for_bank", i, "cringanul chutka " + std::to_string(i));
    req.WriteRequest();
  }
  for (int i = 1; i <= 100; ++i) {
    ASSERT_EQ("cringanul chutka " + std::to_string(i),
              Request::ReadLastRequest("impossible_name_for_bank").text);
  }
  ASSERT_EQ(Request::ReadLastRequest("impossible_name_for_bank"), Request("impossible_name_for_bank", 0, ""));
}