FetchContent_MakeAvailable(googletest)
set(CMAKE_BUILD_TYPE Debug)

enable_testing()

add_executable(main main.c token.c stack.c process-tokens.c dictionary.c)

target_link_libraries(
  main
  -lm
)

add_executable(
  stack_tests
  stack_tests.cc
  stack.c
  token.c
  dictionary.c
  process-tokens.c
)

set(CMAKE_C_FLAGS_DEBUG "-g")

target_link_libraries(
  stack_tests
  gtest_main
  -lpthread
) 

include(GoogleTest)
gtest_discover_tests(stack_tests)
