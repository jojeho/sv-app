#LINK_LIBRARIES(boost_coroutine)
#LINK_LIBRARIES(boost_serialization)
#LINK_LIBRARIES(pthread)
#set(Boost_USE_STATIC_LIBS        OF)
#set(Boost_USE_MULTITHREADED      OF)
#set(Boost_USE_STATIC_RUNTIME    ON)
#include_directories("${DEV_DIR}/prj/sv2/app/src")

include_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/include/mongocxx/v_noabi/")
include_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/include/bsoncxx/v_noabi/")
link_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/lib/")

#LINK_LIBRARIES(boost_system)
#LINK_LIBRARIES(boost_filesystem)

LINK_LIBRARIES(boost_regex)
LINK_LIBRARIES(mongocxx)
LINK_LIBRARIES(bsoncxx)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(boost_thread)
LINK_LIBRARIES(boost_serialization)




add_executable(client  client.cpp)

#add_executable(t  test.cpp)
#add_executable(m  test2.cpp)
#add_library(my_dashine SHARED test2.cpp)
