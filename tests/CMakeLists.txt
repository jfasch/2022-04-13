ADD_EXECUTABLE(
  run-tests

  test-find.cpp
  test-funny-overflow-file.cpp
  test-csv.cpp
)

TARGET_LINK_LIBRARIES(
  run-tests

  userdb
  gtest_main
)
