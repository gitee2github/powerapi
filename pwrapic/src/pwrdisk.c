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
 * Create: 2022-06-23
 * Description: Provide service for PowerAPI refer to disk.
 * **************************************************************************** */

#include "pwrdisk.h"
#include <string.h>
#include "pwrlog.h"
#include "pwrerr.h"
#include "sockclient.h"

int GetDiskList(char diskList[][MAX_ELEMENT_NAME_LEN], uint32_t *len)
{
    ReqInputParam input;
    input.optType = DISK_GET_LIST;
    input.dataLen = 0;
    input.data = NULL;

    RspOutputParam output;
    uint32_t size = MAX_ELEMENT_NAME_LEN * (*len);
    output.rspBuffSize = &size;
    output.rspData = (void *)diskList;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "GetDiskList failed. ret:%d", ret);
        *len = size / MAX_ELEMENT_NAME_LEN;
    } else {
        PwrLog(DEBUG, "GetDiskList Succeed.");
    }
    return ret;
}

int GetDiskLoad(PWR_DISK_Load load[], uint32_t *len, int spec)
{
    uint32_t size = sizeof(PWR_DISK_Load) * (*len);
    ReqInputParam input;
    input.optType = DISK_GET_LOAD;
    if (spec) {
        input.dataLen = size;
        input.data = (char *)load;
    } else {
        input.dataLen = 0;
        input.data = NULL;
    }
    RspOutputParam output;
    output.rspBuffSize = &size;
    output.rspData = (void *)load;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "GetDiskLoad failed. ret:%d", ret);
        *len = size / sizeof(PWR_DISK_Load);
    } else {
        PwrLog(DEBUG, "GetDiskLoad Succeed.");
    }
    return ret;
}

int GetDiskPwrLevel(PWR_DISK_PwrLevel pwrLevel[], uint32_t *len, int spec)
{
    uint32_t size = sizeof(PWR_DISK_PwrLevel) * (*len);
    ReqInputParam input;
    input.optType = DISK_GET_POWER_LEVEL;
    if (spec) {
        input.dataLen = size;
        input.data = (char *)pwrLevel;
    } else {
        input.dataLen = 0;
        input.data = NULL;
    }
    RspOutputParam output;
    output.rspBuffSize = &size;
    output.rspData = (void *)pwrLevel;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "GetDiskPwrLevel failed. ret:%d", ret);
        *len = size / sizeof(PWR_DISK_PwrLevel);
    } else {
        PwrLog(DEBUG, "GetDiskPwrLevel Succeed.");
    }
    return ret;
}

int SetDiskPwrLevel(PWR_DISK_PwrLevel pwrLevel[], uint32_t len)
{
    ReqInputParam input;
    input.optType = DISK_SET_POWER_LEVEL;
    input.dataLen = sizeof(PWR_DISK_PwrLevel) * len;
    input.data = (char *)pwrLevel;
    RspOutputParam output;
    output.rspBuffSize = NULL;
    output.rspData = NULL;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "SetDiskPwrLevel failed. ret:%d", ret);
    } else {
        PwrLog(DEBUG, "SetDiskPwrLevel Succeed.");
    }
    return ret;
}

int GetDiskScsiPolicy(PWR_DISK_ScsiPolicy scsiPolicy[], uint32_t *len, int spec)
{
    uint32_t size = sizeof(PWR_DISK_ScsiPolicy) * (*len);
    ReqInputParam input;
    input.optType = DISK_GET_SCSI_POLICY;
    if (spec) {
        input.dataLen = size;
        input.data = (char *)scsiPolicy;
    } else {
        input.dataLen = 0;
        input.data = NULL;
    }
    RspOutputParam output;
    output.rspBuffSize = &size;
    output.rspData = (void *)scsiPolicy;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "GetDiskScsiPolicy failed. ret:%d", ret);
        *len = size / sizeof(PWR_DISK_ScsiPolicy);
    } else {
        PwrLog(DEBUG, "GetDiskScsiPolicy Succeed.");
    }
    return ret;
}

int SetDiskScsiPolicy(PWR_DISK_ScsiPolicy scsiPolicy[], uint32_t len)
{
    ReqInputParam input;
    input.optType = DISK_SET_SCSI_POLICY;
    input.dataLen = sizeof(PWR_DISK_ScsiPolicy) * len;
    input.data = (char *)scsiPolicy;
    RspOutputParam output;
    output.rspBuffSize = NULL;
    output.rspData = NULL;

    int ret = SendReqAndWaitForRsp(input, output);
    if (ret != SUCCESS) {
        PwrLog(ERROR, "SetDiskScsiPolicy failed. ret:%d", ret);
    } else {
        PwrLog(DEBUG, "SetDiskScsiPolicy Succeed.");
    }
    return ret;
}