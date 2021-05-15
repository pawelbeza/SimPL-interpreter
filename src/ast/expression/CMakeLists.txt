set(HEADER
        ${HEADER}
        ${CMAKE_CURRENT_SOURCE_DIR}
        PARENT_SCOPE
        )

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/MathFactorExpression.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MathTermExpression.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MathExpression.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogicFactorExpression.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RelationalExpression.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AndExpression.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogicExpression.cpp
        PARENT_SCOPE
        )