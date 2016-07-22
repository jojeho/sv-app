#LINK_LIBRARIES(boost_coroutine)
#LINK_LIBRARIES(boost_serialization)
#LINK_LIBRARIES(pthread)
#set(Boost_USE_STATIC_LIBS        OF)
#set(Boost_USE_MULTITHREADED      OF)
#set(Boost_USE_STATIC_RUNTIME    ON)
#include_directories("${DEV_DIR}/prj/sv2/app/src")

#include_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/include/mongocxx/v_noabi/")
#include_directories("${DEV_DIR}/src/mongo-cxx-driver/build/install/include/bsoncxx/v_noabi/")
link_directories("${DEV_DIR}/src/boost_1_61_0_cygwin/stage/lib")
#LINK_LIBRARIES(boost_system)
#LINK_LIBRARIES(boost_filesystem)
#add_library(cygboost_system SHARED IMPORTED)
#add_library(cygboost_filesystem SHARED IMPORTED)

#set_target_properties(cygboost_system cygboost_filesystem PROPERTIES IMPORTED_LOCATION ${DEV_DIR}/src/boot_1_61_0_cygwin/stage/lib/ )
#LINK_LIBRARIES(boost_regex)
#LINK_LIBRARIES(mongocxx)
#LINK_LIBRARIES(bsoncxx)

#link_directories("/cygdrive/d/dev/src/mongo-cxx-driver/build/install/lib")

#add_executable(t  test.cpp)
#target_link_libraries(t boost_system boost_filesystem)

#add_executable(m  test2.cpp)

add_library(my_dashine SHARED test2.cpp)
