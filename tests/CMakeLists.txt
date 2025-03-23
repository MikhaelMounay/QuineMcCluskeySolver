
file(GLOB_RECURSE TESTS *.cpp *.h)

add_executable(QuineMcCluskeySolverTests ${TESTS})

target_link_libraries(QuineMcCluskeySolverTests gtest gtest_main APP_SRC)
