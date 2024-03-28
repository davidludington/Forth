FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main main.c token.c stack.c push-tokens.c dictionary.c)

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

target_link_libraries(
  stack_tests
  gtest_main
  -lpthread
) 

include(GoogleTest)
gtest_discover_tests(stack_tests)
