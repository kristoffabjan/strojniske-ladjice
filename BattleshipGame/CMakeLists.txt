cmake_minimum_required(VERSION 3.10)

# set the project name
project(BattleshipGame)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# add all cpp files in src to the executable
file(GLOB SOURCES 
"src/players/*.cpp"
"src/*.cpp"
)
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/play.cpp")

add_library(Battleship ${SOURCES})

add_executable(BattleshipGame src/main.cpp)
add_executable(PlayBattleship src/play.cpp)
target_link_libraries(BattleshipGame Battleship)
target_link_libraries(PlayBattleship Battleship)

add_executable(BattleshipGameTest ${SOURCES} tests/setupBoard_test.cpp)
add_executable(BattleshipValidSetupTest ${SOURCES} tests/isSetupValid_test.cpp)
add_executable(BattleshipCheckValidTest ${SOURCES} tests/checkValid_test.cpp)