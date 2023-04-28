cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           main
  SOURCE_DIR        "/mnt/c/Users/t8832181/CLionProjects/ex2_os/cmake-build-debug/tests/googletest-src"
  BINARY_DIR        "/mnt/c/Users/t8832181/CLionProjects/ex2_os/cmake-build-debug/tests/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
