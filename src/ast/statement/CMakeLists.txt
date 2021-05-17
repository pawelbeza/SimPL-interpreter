set(HEADER
        ${HEADER}
        ${CMAKE_CURRENT_SOURCE_DIR}
        PARENT_SCOPE
        )

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/PrintStatement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VariableAssignment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ReturnStatement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IfStatement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WhileStatement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionCallStatement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
        PARENT_SCOPE
        )

