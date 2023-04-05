/*
 * Copyright (C) 2023 Junbo Zheng. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef _CLI_LOG_H_
#define _CLI_LOG_H_

#include <stdint.h>
#include <stdio.h>

#ifndef CONFIG_CLI_CONSOLE_PROMPT
#define CONFIG_CLI_CONSOLE_PROMPT "cli> "
#endif /* CONFIG_CLI_CONSOLE_PROMPT */

#ifdef CONFIG_CLI_LOG_WITH_COLOR
#define CLI_LOG_COLOR_RED    "\033[31m"
#define CLI_LOG_COLOR_GREEN  "\033[32m"
#define CLI_LOG_COLOR_YELLOW "\033[33m"
#define CLI_LOG_COLOR_BLUE   "\033[34m"
#else
#define CLI_LOG_COLOR_RED
#define CLI_LOG_COLOR_GREEN
#define CLI_LOG_COLOR_YELLOW
#define CLI_LOG_COLOR_BLUE
#endif

typedef enum {
    CLI_LOG_LEVEL_OFF = 0,
    CLI_LOG_LEVEL_ERR,
    CLI_LOG_LEVEL_WARN,
    CLI_LOG_LEVEL_INFO,
    CLI_LOG_LEVEL_DEBUG,
    CLI_LOG_LEVEL_ALL
} cli_log_level_t;

#define LOG_ERROR(fmt, args...)                                         \
    do {                                                                \
        if (cli_log_level_get() >= CLI_LOG_LEVEL_ERR)                   \
            printf(CLI_LOG_COLOR_RED "[ERROR] [%s:%d]: " fmt, __func__, \
                   __LINE__, ##args);                                   \
    } while (0)

#define LOG_WARN(fmt, args...)                                            \
    do {                                                                  \
        if (cli_log_level_get() >= CLI_LOG_LEVEL_WARN)                    \
            printf(CLI_LOG_COLOR_YELLOW "[WARN] [%s:%d]: " fmt, __func__, \
                   __LINE__, ##args);                                     \
    } while (0)

#define LOG_INFO(fmt, args...)                                           \
    do {                                                                 \
        if (cli_log_level_get() >= CLI_LOG_LEVEL_INFO)                   \
            printf(CLI_LOG_COLOR_GREEN "[INFO] [%s:%d]: " fmt, __func__, \
                   __LINE__, ##args);                                    \
    } while (0)

#define LOG_DEBUG(fmt, args...)                                          \
    do {                                                                 \
        if (cli_log_level_get() >= CLI_LOG_LEVEL_DEBUG)                  \
            printf(CLI_LOG_COLOR_BLUE "[DEBUG] [%s:%d]: " fmt, __func__, \
                   __LINE__, ##args);                                    \
    } while (0)

#define LOG_HEX_DUMP(str, data, size)      \
    do {                                   \
        cli_log_hex_dump(str, data, size); \
    } while (0)

#define CLI_CONSOLE_PROMPT()                     \
    do {                                         \
        printf("%s", CONFIG_CLI_CONSOLE_PROMPT); \
    } while (0)

cli_log_level_t cli_log_level_get(void);

void cli_log_level_set(cli_log_level_t level);

void cli_log_hex_dump(const char* str, const void* data, uint32_t size);

#endif /* _CLI_LOG_H_ */
