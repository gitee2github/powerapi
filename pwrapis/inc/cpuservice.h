/* *****************************************************************************
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * PowerAPI licensed under the Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 * http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
 * PURPOSE.
 * See the Mulan PSL v2 for more details.
 * Author: queyanwen
 * Create: 2022-06-23
 * Description: provide cpu service
 * **************************************************************************** */
#ifndef __PAPIS_CPU_SERVICE_H__
#define __PAPIS_CPU_SERVICE_H__
#include "pwrmsg.h"

void GetCpuinfo(PwrMsg *req);
void GetCpuUsage(PwrMsg *req);
void GetLLCMiss(PwrMsg *req);
void GetCpuFreqGovernor(PwrMsg *req);
void SetCpuFreqGovernor(PwrMsg *req);
#endif
