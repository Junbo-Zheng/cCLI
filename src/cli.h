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

#ifndef _CLI_H_
#define _CLI_H_

#include <stdint.h>

#include "list.h"

typedef void (*cli_cmd_func_t)(const char** data);

typedef struct cli_cmd {
    const char*    cmd;     /* cli cmd string  */
    const char*    brief;   /* cli cmd description */
    cli_cmd_func_t func;    /* cli cmd function */
} cli_cmd_t;

typedef struct {
    cli_cmd_t        cli_cmd;
    struct list_head list;
} cli_list_t;

void cli_init(void);

void cli_readline(const char* data, uint16_t data_len);

int cli_register(const char* cmd, const char* brief, cli_cmd_func_t func);

#endif /* _CLI_H_ */
