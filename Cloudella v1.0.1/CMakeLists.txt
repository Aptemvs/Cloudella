cmake_minimum_required(VERSION 3.23)
project(Cloudella)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cloudella main.cpp Node.cpp Node.h Vault.cpp Vault.h)

include_directories(${Cloudella_SOURCE_DIR}/json_library/include/nlohmann)
target_include_directories(Cloudella PRIVATE ${Cloudella_SOURCE_DIR}/json_library/include)