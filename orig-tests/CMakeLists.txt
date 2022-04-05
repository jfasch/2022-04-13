ADD_EXECUTABLE(test-find test-find.cpp)
TARGET_LINK_LIBRARIES(test-find userdb)

ADD_EXECUTABLE(test-funny-overflow-file test-funny-overflow-file.cpp)
TARGET_LINK_LIBRARIES(test-funny-overflow-file userdb)

ADD_EXECUTABLE(test-csv test-csv.cpp)
TARGET_LINK_LIBRARIES(test-csv userdb)
