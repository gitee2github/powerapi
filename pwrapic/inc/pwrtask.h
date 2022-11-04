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
 * Create: 2022-11-01
 * Description: Provide service for PowerAPI refer to TASK.
 * **************************************************************************** */
#ifndef POWERAPI_COMM_H__
#define POWERAPI_COMM_H__

#include "pwrdata.h"

int CreateDcTask(PWR_COM_BasicDcTaskInfo *basicDcTaskInfo, int *taskId);
int DeleteDcTask(int taskId);

#endif
