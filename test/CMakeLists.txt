project(simpl_lib_test)

find_package(GTest REQUIRED)

set(SOURCE LexerTests.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC
        ${GTEST_BOTH_LIBRARIES}
        pthread
        simpl_lib
        )

add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)
