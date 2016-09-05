include_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/include/mongocxx/v_noabi/")
include_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/include/bsoncxx/v_noabi/")
link_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/lib/")

LINK_LIBRARIES(mongocxx)
LINK_LIBRARIES(bsoncxx)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(boost_thread)
LINK_LIBRARIES(boost_serialization)

### for interprocesss
LINK_LIBRARIES(rt)

add_executable(gp  gp.cpp)

