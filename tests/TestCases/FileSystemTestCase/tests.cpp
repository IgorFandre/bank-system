#include "../../../Filesystem/Filesystem.h"
#include "FileSystemTestCase.h"

const std::string FILESYSTEM_TEST_CASE::testing_dir = "test_lib_filesystem";

void FILESYSTEM_TEST_CASE::SetUp() {
  std::filesystem::create_directories(testing_dir);
}

void FILESYSTEM_TEST_CASE::TearDown() {
  std::filesystem::remove_all(testing_dir);
}

TEST_F(FILESYSTEM_TEST_CASE, check_directory) {
  const std::string path = FILESYSTEM_TEST_CASE::testing_dir + "/testing_dir_to_check";

  ASSERT_FALSE(std::filesystem::exists(path));

  ASSERT_FALSE(Filesystem::CheckDirectory(path));
  ASSERT_TRUE(std::filesystem::exists(path));

  ASSERT_TRUE(Filesystem::CheckDirectory(path));
  ASSERT_TRUE(std::filesystem::exists(path));
}

TEST_F(FILESYSTEM_TEST_CASE, check_file) {
  const std::string path = FILESYSTEM_TEST_CASE::testing_dir + "/testing_file_to_check.json";

  ASSERT_FALSE(std::filesystem::exists(path));

  ASSERT_FALSE(Filesystem::CheckFile(path));
  ASSERT_TRUE(std::filesystem::exists(path));

  ASSERT_TRUE(Filesystem::CheckFile(path));
  ASSERT_TRUE(std::filesystem::exists(path));
}