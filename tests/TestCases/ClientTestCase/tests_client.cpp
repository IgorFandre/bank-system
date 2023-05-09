#include <gtest/gtest.h>

#include "../../../Client/Client.h"

TEST(TEST_CLIENT, check_getters) {
  Passport p_1{1, 1, "a", "b", "c"};
  Client cl_1{5, "1234", p_1};

  ASSERT_EQ(*cl_1.GetPassport(), p_1);
  ASSERT_EQ(cl_1.GetPassword(), "1234");
  ASSERT_EQ(cl_1.GetID(), 5);
  ASSERT_EQ(cl_1.GetStatus(), Status::Confirmed);
}

TEST(TEST_CLIENT, check_equal) {
  Passport p_1{1, 1, "a", "b", "c"};
  Client cl_1{1, "1234", p_1};
  Client cl_2{1, "1234", p_1};

  ASSERT_EQ(cl_1, cl_2);
}

TEST(TEST_CLIENT, check_status) {
  Passport p_1{1, 1, "a", "b", "c"};
  Client cl_1{1, "1234", p_1};

  ASSERT_EQ(cl_1.GetStatus(), Status::Confirmed);

  cl_1.ChangeStatus(true);

  ASSERT_EQ(cl_1.GetStatus(), Status::Blocked);
}

TEST(TEST_CLIENT, check_password) {
  Passport p_1{1, 1, "a", "b", "c"};
  Client cl_1{1, "1234", p_1};

  ASSERT_EQ(cl_1.GetPassword(), "1234");
  ASSERT_TRUE(cl_1.CheckPassword("1234"));
}