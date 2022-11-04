/* *****************************************************************************
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022 All rights reserved.
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

#include "pwrtask.h"
#include <string.h>
#include "pwrlog.h"
#include "pwrerr.h"
#include "sockclient.h"

int CreateDcTask(PWR_COM_BasicDcTaskInfo *basicDcTaskInfo, int *taskId)
{
    ReqInputParam input;
    input.optType = COM_CREATE_DC_TASK;
    input.dataLen = sizeof(PWR_COM_BasicDcTaskInfo);
    input.data = (char *)basicDcTaskInfo;

    RspOutputParam output;
    uint32_t size = sizeof(int);
    output.rspBuffSize = &size;
    output.rspData = (void *)taskId;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "CreateDcTask failed. ret:%d", ret);
    } else {
        PwrLog(DEBUG, "CreateDcTask Succeed.");
    }
    return ret;
}

int DeleteDcTask(int taskId)
{
    ReqInputParam input;
    input.optType = COM_DELETE_DC_TASK;
    input.dataLen = sizeof(taskId);
    input.data = (char *)&taskId;
    RspOutputParam output;
    output.rspBuffSize = NULL;
    output.rspData = NULL;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "DeleteDcTask failed. ret:%d", ret);
    } else {
        PwrLog(DEBUG, "DeleteDcTask Succeed.");
    }
    return ret;
}