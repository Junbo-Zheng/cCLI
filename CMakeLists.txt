cmake_minimum_required(VERSION 3.16)

message(
        STATUS
        "Current CMake version : ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}"
)
message(STATUS "Current Source Dir    : ${CMAKE_CURRENT_SOURCE_DIR}")

project(
        cCLI
        VERSION 1.0
        LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Just fot test, should disable in projects
option(CLI_CMD_DEMO_TEST     "enable cli cmd demo test"     ON)

option(CLI_CMD_HELP_REGISTER "enable cli cmd help register" ON)
option(CLI_LOG_WITH_COLOR    "enable cli log with color"    OFF)

add_compile_options(-Wall -Wextra -Werror -Wno-format -g)

set(cCLI_SRC src/cli.c src/cli_log.c src/cli_util.c)

if(CLI_CMD_DEMO_TEST)
    set(cCLI_SRC ${cCLI_SRC} demo.c)
endif()

add_executable(${PROJECT_NAME} ${cCLI_SRC})

set(CLI_LOG_LEVEL      "5"     CACHE STRING "")
set(CLI_CMD_ARGC_MAX   "10"    CACHE STRING "")
set(CLI_CONSOLE_PROMPT "cli> " CACHE STRING "")

if(CLI_CMD_HELP_REGISTER)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DCONFIG_CLI_CMD_HELP_REGISTER=1)
endif()

if(CLI_LOG_WITH_COLOR)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DCONFIG_CLI_LOG_WITH_COLOR=1)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC -DCONFIG_CLI_LOG_LEVEL=${CLI_LOG_LEVEL})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DCONFIG_CLI_CMD_ARGC_MAX=${CLI_CMD_ARGC_MAX})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DCONFIG_CLI_CONSOLE_PROMPT="${CLI_CONSOLE_PROMPT}")

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_include_directories(${PROJECT_NAME} PRIVATE external/)

option(ENABLE_SANITIZER "Enables sanitizer" OFF)
if (ENABLE_SANITIZER)
    target_compile_options(
            ${PROJECT_NAME} PUBLIC -fsanitize=address -fno-omit-frame-pointer
            -fsanitize=undefined)
    target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
    target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=undefined)
endif()
