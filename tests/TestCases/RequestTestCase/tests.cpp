#include <gtest/gtest.h>
#include "../../../Request/Request.h"
#include "RequestTestCase.h"

std::string REQUEST_TEST_CASE::bank_name = "impossible_name_for_bank";

void REQUEST_TEST_CASE::SetUpTestSuite() {
  assert(!std::filesystem::exists("Data" + bank_name));
}

void REQUEST_TEST_CASE::TearDownTestSuite() {
  std::string data = "Data";
  std::filesystem::remove_all(data + "/" + bank_name);
  if (std::filesystem::exists(data) && std::filesystem::is_empty(data)) {
    std::filesystem::remove(data);
  }
}

TEST_F(REQUEST_TEST_CASE, write_and_read_requests) {
  for (int i = 1; i <= 100; ++i) {
    Request req(bank_name, i, "cringanul chutka " + std::to_string(i));
    req.WriteRequest();
  }
  for (int i = 1; i <= 100; ++i) {
    ASSERT_EQ("cringanul chutka " + std::to_string(i),
              Request::ReadLastRequest(bank_name).text);
  }
  ASSERT_EQ(Request::ReadLastRequest(bank_name), Request(bank_name, 0, ""));
}