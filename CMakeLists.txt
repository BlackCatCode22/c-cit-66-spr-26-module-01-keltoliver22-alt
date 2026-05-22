cat << 'EOF' > CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(GlobalWeatherDashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate the system's native web request libraries
find_package(CURL REQUIRED)

add_executable(weather_dashboard main.cpp)

# Tells CMake to look right in your folder for crow_all.h and asio.hpp
target_include_directories(weather_dashboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(weather_dashboard PRIVATE CURL::libcurl pthread)
EOF