cmake_minimum_required(VERSION 3.5...3.16)
project(calculate_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")


enable_testing()

add_executable(
  calculate_test calculate_test.cc ../models/calculateModel.cc ../presenters/calculatePresenter.cc
)
add_executable(
  loan_test loan_test.cc ../models/loanModel.cc ../presenters/loanPresenter.cc
)
add_executable(
  deposit_test deposit_test.cc ../models/depositModel.cc ../presenters/depositPresenter.cc
)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core PrintSupport)
target_link_libraries(loan_test gtest pthread Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(calculate_test gtest pthread Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(deposit_test gtest pthread Qt${QT_VERSION_MAJOR}::Core)

add_test(NAME loan_test COMMAND loan_test)
add_test(NAME calculate_test COMMAND calculate_test)
add_test(NAME deposit_test COMMAND deposit_test)
