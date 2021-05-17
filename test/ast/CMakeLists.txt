add_subdirectory(expression)
add_subdirectory(statement)

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/VariableTest.cpp
        PARENT_SCOPE
        )