cmake_minimum_required(VERSION 3.14)
project(FamilyFinanceManager VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件列表
set(SOURCES
    src/main.cpp
    src/Record.cpp
    src/IncomeRecord.cpp
    src/ExpenseRecord.cpp
    src/InputHelper.cpp
    src/DisplayHelper.cpp
    src/RecordStorage.cpp
    src/FinanceManager.cpp
    src/ReportGenerator.cpp
    src/MenuSystem.cpp
)

# 头文件列表
set(HEADERS
    include/Record.h
    include/IncomeRecord.h
    include/ExpenseRecord.h
    include/InputHelper.h
    include/DisplayHelper.h
    include/RecordStorage.h
    include/FinanceManager.h
    include/ReportGenerator.h
    include/MenuSystem.h
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Windows特定设置
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE FALSE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# 创建数据目录
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data)

# 安装规则
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY DESTINATION bin/data)
