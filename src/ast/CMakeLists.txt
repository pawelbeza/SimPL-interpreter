add_subdirectory("expression")
add_subdirectory("statement")

set(HEADER
        ${HEADER}
        ${CMAKE_CURRENT_SOURCE_DIR}
        PARENT_SCOPE
        )

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/Variable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Program.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function.cpp
        PARENT_SCOPE
        )

