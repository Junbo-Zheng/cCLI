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

#include "cli_log.h"

#include <assert.h>

#ifndef CONFIG_CLI_LOG_LEVEL
#define CONFIG_CLI_LOG_LEVEL CLI_LOG_LEVEL_ALL
#endif /* CONFIG_CLI_LOG_LEVEL */

static cli_log_level_t cli_log_level = CONFIG_CLI_LOG_LEVEL;

void cli_log_level_set(cli_log_level_t level)
{
    cli_log_level = level;
}

cli_log_level_t cli_log_level_get(void)
{
    return cli_log_level;
}

void cli_log_hex_dump(const char* str, const void* data, uint32_t size)
{
    assert(data);

    printf("hexdump %s %u bytes from %p:\n", str, size, data);

    const uint8_t* c = data;

    while (size > 0) {
        unsigned i;

        for (i = 0; i < 16; i++) {
            if (i < size) {
                printf("%02x ", c[i]);
            } else {
                printf("   ");
            }
        }

        for (i = 0; i < 16; i++) {
            if (i < size) {
                printf("%c", c[i] >= 32 && c[i] < 127 ? c[i] : '.');
            } else {
                printf(" ");
            }
        }

        printf("\n");

        c += 16;

        if (size <= 16) {
            break;
        }

        size -= 16;
    }
}
