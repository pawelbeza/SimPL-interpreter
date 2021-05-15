add_subdirectory("expression")

set(HEADER
        ${HEADER}

        ${CMAKE_CURRENT_SOURCE_DIR}

        ${CMAKE_CURRENT_SOURCE_DIR}/statement

        PARENT_SCOPE
        )

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/Variable.cpp
        PARENT_SCOPE
        )

