project(simpl_lib)

set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer/Lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token/Token.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token/TokenTypeFactory.cpp
        )

set(HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/token
        )

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/token
)