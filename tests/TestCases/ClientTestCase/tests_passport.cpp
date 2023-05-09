#include <gtest/gtest.h>

#include "../../../Client/Passport.h"

TEST(TEST_PASSPORT, check_copy) {
  Passport passport{7777, 777777, "Ivan", "Ivanov",
                    "Петрозаводск,УлицаПушкина,ДомКолотушкина"};
  Passport passport_copy(passport);
  ASSERT_EQ(passport, passport_copy);
}

TEST(TEST_PASSPORT, check_status) {
  Passport pas_empty;
  ASSERT_EQ(pas_empty.GetPassportStatus(), Status::Unconfirmed);

  Passport pas_1{7777, 777777, "Ivan", "Ivanov",
                 "Петрозаводск,УлицаПушкина,ДомКолотушкина"};
  ASSERT_EQ(pas_1.GetPassportStatus(), Status::Confirmed);

  Passport pas_2{7777, 777777, "Ivan", "Ivanov", "0"};
  ASSERT_EQ(pas_2.GetPassportStatus(), Status::Unconfirmed);

  Passport pas_3{7777, 777777, "Ivan", "Ivanov", ""};
  ASSERT_EQ(pas_3.GetPassportStatus(), Status::Unconfirmed);

  Passport pas_4{7777, -1, "Ivan", "Ivanov",
                 "Петрозаводск,УлицаПушкина,ДомКолотушкина"};
  ASSERT_EQ(pas_4.GetPassportStatus(), Status::Unconfirmed);

  Passport pas_5{-1, 0, "Ivan", "Ivanov",
                 "Петрозаводск,УлицаПушкина,ДомКолотушкина"};
  ASSERT_EQ(pas_5.GetPassportStatus(), Status::Unconfirmed);

  Passport pas_6{0, 0, "Ivan", "Ivanov",
                 "Петрозаводск,УлицаПушкина,ДомКолотушкина"};
  ASSERT_EQ(pas_6.GetPassportStatus(), Status::Confirmed);
}