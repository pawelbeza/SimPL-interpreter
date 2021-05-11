project(simpl_lib)

set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer/Lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token/Token.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token/TokenTypeFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/Parser.cpp
        )

set(HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/token
        ${CMAKE_CURRENT_SOURCE_DIR}/parser
        )

add_subdirectory("ast")

add_library(${PROJECT_NAME} STATIC ${SOURCE})

message(STATUS "foo include dir: ${HEADER}")

target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER})