cmake_minimum_required(VERSION 3.14)
project(MyProject)

# Find cURL (via vcpkg)
find_package(CURL REQUIRED)

# Add your executable
add_executable(my_app main.cpp)

# Link against cURL
target_link_libraries(my_app PRIVATE CURL::libcurl)

# If building statically on Windows:
if(WIN32 AND CURL_STATIC)
    target_compile_definitions(my_app PRIVATE CURL_STATICLIB)
    target_link_libraries(my_app PRIVATE ws2_32 crypt32)
endif()