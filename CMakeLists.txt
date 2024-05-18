cmake_minimum_required(VERSION 3.29) 
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(net-stuff LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for compiler type and add the respective flags
if(MSVC)
  # MSVC compiler (Visual Studio)
  add_compile_options(/WX /bigobj)
  
else()
  # GCC, Clang, and others
  add_compile_options(-Werror)
endif()

#add_subdirectory(proxy_beast_asio)
add_subdirectory(lin_sock_webserver)