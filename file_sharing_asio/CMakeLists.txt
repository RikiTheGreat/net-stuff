find_package(Boost REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(STATUS "Boost NOT Found !")
endif(Boost_FOUND)

add_executable(file_share main.cpp)
add_subdirectory(src)
target_include_directories(file_share PRIVATE src)
target_link_directories(file_share PRIVATE src)
target_link_libraries(file_share PRIVATE  ${Boost_LIBRARIES} fs)