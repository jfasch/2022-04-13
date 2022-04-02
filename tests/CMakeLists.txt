ADD_EXECUTABLE(test-funny-overflow test-funny-overflow.cpp)
TARGET_LINK_LIBRARIES(test-funny-overflow userdb)

ADD_EXECUTABLE(test-funny-overflow-file test-funny-overflow-file.cpp)
TARGET_LINK_LIBRARIES(test-funny-overflow-file userdb)

ADD_EXECUTABLE(test-truncate-on-overflow-file test-truncate-on-overflow-file.cpp)
TARGET_LINK_LIBRARIES(test-truncate-on-overflow-file userdb)

ADD_EXECUTABLE(test-csv test-csv.cpp)
TARGET_LINK_LIBRARIES(test-csv userdb)
