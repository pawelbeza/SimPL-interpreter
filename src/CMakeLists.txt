project(simpl_lib)

add_subdirectory("ast")
add_subdirectory("lexer")
add_subdirectory("parser")
add_subdirectory("token")

add_library(${PROJECT_NAME} STATIC ${SOURCE})

message(STATUS "foo include dir: ${HEADER}")

target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER})