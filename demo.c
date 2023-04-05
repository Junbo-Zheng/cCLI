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
#include <string.h>

#include <time.h>

#include "cli.h"
#include "cli_log.h"
#include "cli_util.h"

static void test_func(const char** data)
{
    UNUSED(data);
    printf("cli test func\n");
}

static void date_func(const char** data)
{
    UNUSED(data);
    printf("cli date func\n");

    time_t cur_time;
    time(&cur_time);
    printf("%s", ctime(&cur_time));
}

static void hello_func(const char** data)
{
    UNUSED(data);
    printf("cli hello func\n");
}

static void str2dec_func(const char** data)
{
    printf("cli str2dec func, %s(str) %d(dec) %x(dec) %d(hex) %x(hex)\n",
           data[0], cli_str2dec(data[0]), cli_str2dec(data[0]),
           cli_str2hex(data[0]), cli_str2hex(data[0]));
}
static void str2hex_func(const char** data)
{
    printf("cli str2hex func, %s(str) %d(dec) %x(dec) %d(hex) %x(hex)\n",
           data[0], cli_str2dec(data[0]), cli_str2dec(data[0]),
           cli_str2hex(data[0]), cli_str2hex(data[0]));
}

int main(void)
{
    cli_init();

    cli_register("test", "cli test", test_func);
    cli_register("date", "cli date", date_func);
    cli_register("hello", "hello",   hello_func);

    cli_register("str2dec", "str to dec", str2dec_func);
    cli_register("str2hex", "str to hex", str2hex_func);

    while (1) {
        char buf[1024] = { 0 };
        fgets(buf, sizeof(buf) - 1, stdin);

        int len = (int)strlen(buf);
        buf[len - 1] = 0x0d;
        buf[len]     = 0x0a;

        // LOG_HEX_DUMP("input", (const void*)buf, len);
        cli_readline(buf, strlen((const char*)buf));
    }

    return 0;
}
