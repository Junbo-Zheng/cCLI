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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "cli_log.h"
#include "cli_util.h"

#ifndef CONFIG_CLI_CMD_ARGC_MAX
#define CONFIG_CLI_CMD_ARGC_MAX 10
#endif /* CONFIG_CLI_CMD_ARGC_MAX */

static cli_list_t cli_list_head = { 0 };

static cli_cmd_t* cli_cmd_check(char** cmd)
{
    struct list_head *pos, *n;

    list_for_each_safe(pos, n, &cli_list_head.list)
    {
        cli_list_t* cli_list = list_entry(pos, cli_list_t, list);
        if (!strcasecmp((char*)cli_list->cli_cmd.cmd, cmd[0])) {
            return &cli_list->cli_cmd;
        }
    }

    LOG_WARN("Not find cli cmd, please type 'help' for help.\n");
    return NULL;
}

void cli_readline(const char* data, uint16_t data_len)
{
    if ((data[data_len - 2] != '\r') || (data[data_len - 1] != '\n')) {
        return;
    }

    if (data_len > 2) {
        char cmd_str[128] = { 0 };
        uint8_t cmd_count = 0;
        char* cmd[CONFIG_CLI_CMD_ARGC_MAX] = { 0 };

        memcpy(cmd_str, data, data_len - 2);

        char* ptr = strtok((char*)cmd_str, " ");
        while (ptr) {
            if (cmd_count + 1 >= CONFIG_CLI_CMD_ARGC_MAX) {
                LOG_ERROR("cli command parameters is out of bounds\n");
                CLI_CONSOLE_PROMPT();
                return;
            }

            cmd[cmd_count++] = ptr;
            ptr = strtok(NULL, " ");
        }

        cli_cmd_t* cli_cmd = cli_cmd_check(cmd);
        if (cli_cmd && cli_cmd->func) {
            cli_cmd->func((const char**)&cmd[1]);
        }
    }

    CLI_CONSOLE_PROMPT();
}

int cli_register(const char* cmd, const char* brief, cli_cmd_func_t func)
{
    cli_list_t* cli_list
        = calloc(1, sizeof(cli_list_t) + strlen((const char*)brief));
    if (cli_list == NULL) {
        LOG_ERROR("calloc fail\n");
        return -1;
    }

    cli_list->cli_cmd.cmd   = cmd;
    cli_list->cli_cmd.brief = brief;
    cli_list->cli_cmd.func  = func;

    list_add_tail(&cli_list->list, &cli_list_head.list);

    return 0;
}

#ifdef CONFIG_CLI_CMD_HELP_REGISTER
static void cli_help(const char** data)
{
    UNUSED(data[0]);

    struct list_head *pos, *n;

    list_for_each_safe(pos, n, &cli_list_head.list)
    {
        cli_list_t* cli_list = list_entry(pos, cli_list_t, list);
        if (cli_list && cli_list->cli_cmd.func) {
            LOG_DEBUG("%s -> %s\n", cli_list->cli_cmd.cmd,
                      cli_list->cli_cmd.brief);
        }
    }
}
#endif /* CONFIG_CLI_CMD_HELP_REGISTER */

void cli_init(void)
{
    INIT_LIST_HEAD(&cli_list_head.list);

#ifdef CONFIG_CLI_CMD_HELP_REGISTER
    cli_register("help", "help", cli_help);
#endif /* CONFIG_CLI_CMD_HELP_REGISTER */

    LOG_INFO("cli init, build time: %s\n", __TIMESTAMP__);

    CLI_CONSOLE_PROMPT();
}
