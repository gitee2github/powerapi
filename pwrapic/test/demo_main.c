/* *****************************************************************************
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022 All rights reserved.
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
 * Description: PowerAPI DEMO for testing the interface.
 * **************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "powerapi.h"

static int g_run = 1;

static const char *GetLevelName(int level)
{
    static char debug[] = "DEBUG";
    static char info[] = "INFO";
    static char warning[] = "WARNING";
    static char error[] = "ERROR";
    switch (level) {
        case 0:
            return debug;
        case 1:
            return info;
        case 2:
            return warning;
        case 3:
            return error;
        default:
            return info;
    }
}

void LogCallback(int level, const char *fmt, va_list vl)
{
    char logLine[4096] = {0};
    char message[4000] = {0};

    if (vsnprintf(message, sizeof(message) - 1, fmt, vl) < 0) {
        return;
    }

    printf("%s: %s\n", GetLevelName(level), message);
}

static void SignalHandler()
{
    g_run = 0;
}

static void SetupSignal()
{
    // regist signal handler
    signal(SIGINT, SignalHandler);
    signal(SIGUSR1, SignalHandler);
    signal(SIGUSR2, SignalHandler);
    signal(SIGTERM, SignalHandler);
    signal(SIGKILL, SignalHandler);
}

// PWR_CPU_GetUsage
static void TEST_PWR_CPU_GetInfo()
{
    int ret;
    PWR_CPU_Info *info = (PWR_CPU_Info *)malloc(sizeof(PWR_CPU_Info));
    bzero(info, sizeof(PWR_CPU_Info));
    ret = PWR_CPU_GetInfo(info);
    printf("PWR_CPU_GetInfo ret: %d\n arch:%s\n coreNum: %d\n maxFreq:%f\n minFreq:%d\n modelName: %s\n numaNum: %d\n "
        "threadsPerCore:%d\n",
        ret, info->arch, info->coreNum, info->maxFreq, info->minFreq, info->modelName, info->numaNum,
        info->threadsPerCore);
    for (int i = 0; i < info->numaNum; i++) {
        printf("numa node %d  cpuList: %s\n", info->numa[i].nodeNo, info->numa[i].cpuList);
    }
    free(info);
}

// PWR_CPU_GetUsage
static void TEST_PWR_CPU_GetUsage()
{
    int ret;
    int buffSize = sizeof(PWR_CPU_Usage) + 128 * sizeof(PWR_CPU_CoreUsage);
    PWR_CPU_Usage *u = (PWR_CPU_Usage *)malloc(buffSize);
    bzero(u, buffSize);
    ret = PWR_CPU_GetUsage(u, buffSize);
    printf("PWR_CPU_GetUsage ret: %d, CPU avgUsage:%f, coreNum: %d \n", ret, u->avgUsage, u->coreNum);
    for (int i = 0; i < u->coreNum; i++) {
        printf("core%d usage: %f\n", u->coreUsage[i].coreNo, u->coreUsage[i].usage);
    }
    free(u);
}

// PWR_CPU_GetFreqAbility
static void TEST_PWR_CPU_GetFreqAbility(void)
{
    int ret = 0;
    int len = sizeof(PWR_CPU_FreqAbility) + 5 * 128;
    PWR_CPU_FreqAbility *freqAbi = (PWR_CPU_FreqAbility *)malloc(len);
    if(!freqAbi) {
        return -1;
    }
    bzero(freqAbi, len);
    ret = PWR_CPU_GetFreqAbility(freqAbi, len);
    printf("PWR_CPU_GetFreqAbility ret: %d, freqDrv:%s, govNum: %d, freqDomainNum:%d \n", ret, freqAbi->curDriver,
        freqAbi->avGovNum, freqAbi->freqDomainNum);
    for (int i = 0; i < freqAbi->avGovNum; i++) {
        printf("gov index: %d, gov: %s\n", i, freqAbi->avGovList[i]);
    }
    for (int i = 0; i < freqAbi->freqDomainNum; i++) {
        char *freqDomainInfo = freqAbi->freqDomain + i * freqAbi->freqDomainStep;
        int policyId = *((int *)freqDomainInfo);
        char *affectCpuList = freqDomainInfo + sizeof(int);
        printf("FreqDomain %d, affectCpuList：%s\n", policyId, affectCpuList);
    }
    free(freqAbi);
}

static void TEST_PWR_CPU_SetAndGetFreqGov()
{
    int ret = 0;
    char gov[MAX_ELEMENT_NAME_LEN] = {0};
    ret = PWR_CPU_GetFreqGovernor(gov, MAX_ELEMENT_NAME_LEN);
    printf("PWR_CPU_GetFreqGovernor ret: %d, gov:%s\n", ret, gov);
    strncpy(gov, "ondemand", MAX_ELEMENT_NAME_LEN - 1);
    ret = PWR_CPU_SetFreqGovernor(gov);
    printf("PWR_CPU_SetFreqGovernor ret: %d\n", ret);
    bzero(gov, MAX_ELEMENT_NAME_LEN);
    ret = PWR_CPU_GetFreqGovernor(gov, MAX_ELEMENT_NAME_LEN);
    printf("PWR_CPU_GetFreqGovernor ret: %d, gov:%s\n", ret, gov);
}

// PWR_CPU_GetFreq PWR_CPU_SetFreq
#define TEST_FREQ 2400;
static void TEST_PWR_CPU_SetAndGetCurFreq()
{
    int ret = 0;
    uint32_t len = 128;
    PWR_CPU_CurFreq curFreq[len];
    bzero(curFreq, len * sizeof(PWR_CPU_CurFreq));
    int spec = 0;
    ret = PWR_CPU_GetFreq(curFreq, &len, spec);
    printf("PWR_CPU_GetFreq ret: %d, len:%d\n", ret, len);
    for (int i = 0; i < len; i++) {
        printf("Freq Policy %d curFreq:%d\n", curFreq[i].policyId, curFreq[i].curFreq);
    }
    len = 128;
    bzero(curFreq, len * sizeof(PWR_CPU_CurFreq));
    curFreq[0].policyId = 0;
    curFreq[0].curFreq = TEST_FREQ;
    ret = PWR_CPU_SetFreq(curFreq, 1);
    printf("PWR_CPU_SetFreq ret: %d\n", ret);
    len = 1;
    spec = 1;
    curFreq[0].curFreq = 0;
    ret = PWR_CPU_GetFreq(curFreq, &len, spec);
    printf("Freq Policy %d curFreq:%d\n", curFreq[0].policyId, curFreq[0].curFreq);
}

static void TEST_PWR_CPU_DmaSetAndGetLatency()
{
    int ret = 0;
    int la = -1;
    ret = PWR_CPU_DmaGetLatency(&la);
    printf("PWR_CPU_DmaGetLatency ret: %d, Latency:%d\n", ret, la);
    ret = PWR_CPU_DmaSetLatency(2000);
    printf("PWR_CPU_DmaSetLatency ret: %d\n", ret);
    la = -1;
    ret = PWR_CPU_DmaGetLatency(&la);
    printf("PWR_CPU_DmaGetLatency ret: %d, Latency:%d\n", ret, la);
}

int main(int argc, const char *args[])
{
    PWR_SetLogCallback(LogCallback);
    while (PWR_Register() != SUCCESS) {
        sleep(3);
        printf("main registed failed!\n");
        continue;
    }
    printf("main regist succeed.\n");

    // PWR_CPU_GetUsage
    TEST_PWR_CPU_GetUsage();

    // PWR_CPU_GetFreqAbility
    TEST_PWR_CPU_GetFreqAbility();

    // PWR_CPU_GetFreqGovernor PWR_CPU_SetFreqGovernor
    TEST_PWR_CPU_SetAndGetFreqGov();

    // PWR_CPU_GetCurFreq PWR_CPU_SetCurFreq
    TEST_PWR_CPU_SetAndGetCurFreq();

    // PWR_CPU_DmaSetLatency PWR_CPU_DmaGetLatency
    TEST_PWR_CPU_DmaSetAndGetLatency();

    // todo: 其他接口测试

    while (g_run) {
        sleep(5);
    }
    PWR_UnRegister();
    return 0;
}