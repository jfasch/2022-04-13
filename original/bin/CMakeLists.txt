ADD_EXECUTABLE(userdb-write-binaryfile userdb-write-binaryfile.cpp)
TARGET_LINK_LIBRARIES(userdb-write-binaryfile userdb)

ADD_EXECUTABLE(userdb-read-binaryfile userdb-read-binaryfile.cpp)
TARGET_LINK_LIBRARIES(userdb-read-binaryfile userdb)

ADD_EXECUTABLE(userdb-finduser-binaryfile userdb-finduser-binaryfile.cpp)
TARGET_LINK_LIBRARIES(userdb-finduser-binaryfile userdb)



