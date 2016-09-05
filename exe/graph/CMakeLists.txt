LINK_LIBRARIES(boost_system)
LINK_LIBRARIES(boost_thread)


### for inter process
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(rt)
LINK_LIBRARIES(slope)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
#add_definitions(${GTK3_CFLAGS_OTHER})
# Add an executable compiled from hello.c


#LINK_LIBRARIES(${GTK3_LIBRARIES})

add_executable(myd draw.cpp)

# Link the target to the GTK+ li
target_link_libraries(myd ${GTK3_LIBRARIES})




