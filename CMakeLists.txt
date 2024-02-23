cmake_minimum_required(VERSION 3.16)

project(
  cCLI
  VERSION 1.0
  LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Just fot test, should disable in projects
option(CLI_CMD_DEMO_TEST "enable cli cmd demo test" ON)

option(ENABLE_SANITIZER "Enables sanitizer" OFF)
option(CLI_LOG_WITH_COLOR "enable cli log with color" OFF)
option(CLI_CMD_HELP_REGISTER "enable cli cmd help register" ON)

add_compile_options(-Wall -Wextra -Werror -Wno-format -g)

set(cCLI_SRC src/cli.c src/cli_log.c src/cli_util.c)

if(CLI_CMD_DEMO_TEST)
  set(cCLI_SRC ${cCLI_SRC} demo.c)
endif()

add_executable(${PROJECT_NAME} ${cCLI_SRC})

set(CLI_LOG_LEVEL
    "5"
    CACHE STRING "")
set(CLI_CMD_ARGC_MAX
    "10"
    CACHE STRING "")
set(CLI_CONSOLE_PROMPT
    "cli> "
    CACHE STRING "")

if(CLI_CMD_HELP_REGISTER)
  target_compile_definitions(${PROJECT_NAME}
                             PUBLIC -DCONFIG_CLI_CMD_HELP_REGISTER=1)
endif()

if(CLI_LOG_WITH_COLOR)
  target_compile_definitions(${PROJECT_NAME}
                             PUBLIC -DCONFIG_CLI_LOG_WITH_COLOR=1)
endif()

target_compile_definitions(${PROJECT_NAME}
                           PUBLIC -DCONFIG_CLI_LOG_LEVEL=${CLI_LOG_LEVEL})
target_compile_definitions(${PROJECT_NAME}
                           PUBLIC -DCONFIG_CLI_CMD_ARGC_MAX=${CLI_CMD_ARGC_MAX})
target_compile_definitions(
  ${PROJECT_NAME} PUBLIC -DCONFIG_CLI_CONSOLE_PROMPT="${CLI_CONSOLE_PROMPT}")

target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_include_directories(${PROJECT_NAME} PRIVATE external/)

if(ENABLE_SANITIZER)
  add_compile_options(-fsanitize=address)
  add_compile_options(-fsanitize=undefined)
  add_compile_options(-fno-omit-frame-pointer)
  add_compile_options(-fsanitize-address-use-after-scope)
endif()
