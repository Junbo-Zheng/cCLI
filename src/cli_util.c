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

#include "cli_util.h"

uint32_t cli_str2dec(const char* data)
{
    uint8_t* p_data = (uint8_t*)data;
    uint32_t value = 0;
    while (*p_data >= '0' && *p_data <= '9') {
        value *= 10;
        value += *p_data - '0';
        p_data++;
    }

    return value;
}

uint32_t cli_str2hex(const char* data)
{
    uint32_t ret = 0;

    uint8_t* p_data = (uint8_t*)data;
    int32_t temp = 0;

    while (('\0' != *p_data) && (7 >= (p_data - (uint8_t*)data))) {
        if ((*p_data >= '0') && (*p_data <= '9')) {
            temp = *p_data - '0';
        } else if ((*p_data >= 'a') && (*p_data <= 'f')) {
            temp = *p_data - 'a' + 0x0a;
        } else if ((*p_data >= 'a') && (*p_data <= 'f')) {
            temp = *p_data - 'a' + 0x0a;
        } else {
            return 0;
        }

        ret <<= 4;
        ret += temp;

        p_data++;
    }

    return ret;
}
