set(TARGET BabylonCppTests)
message(STATUS "Tests ${TARGET}")

file(GLOB_RECURSE sources *.h *.cpp)
babylon_add_test(${TARGET} ${sources})
target_link_libraries(${TARGET} PRIVATE BabylonCpp json_hpp)
