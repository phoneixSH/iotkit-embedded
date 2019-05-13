/*
 * Copyright (C) 2015-2019 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include <process.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include "infra_config.h"
#include "infra_compat.h"
#include "infra_defs.h"
#include "wrappers_defs.h"

void HAL_Printf(_IN_ const char *fmt, ...);
#define hal_emerg(...)      HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_crit(...)       HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_err(...)        HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_warning(...)    HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_info(...)       HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")
#define hal_debug(...)      HAL_Printf("[prt] "), HAL_Printf(__VA_ARGS__), HAL_Printf("\r\n")


#define __DEMO__

#ifdef __DEMO__
    #ifdef DYNAMIC_REGISTER
        char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1ZETBPbycq";
        char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "L68wCVXYUaNg1Ey9";
        char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "example1";
        char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "";
    #else
        #ifdef DEVICE_MODEL_ENABLED
            char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1RIsMLz2BJ";
            char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "fSAF0hle6xL0oRWd";
            char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "example1";
            char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "RDXf67itLqZCwdMCRrw0N5FHbv5D7jrE";
        #else
            char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1MZxOdcBnO";
            char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "h4I4dneEFp7EImTv";
            char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "test_01";
            char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "t9GmMf2jb3LgWfXBaZD2r3aJrfVWBv56";
        #endif
    #endif
#endif

void *HAL_MutexCreate(void)
{
    HANDLE mutex;

    if (NULL == (mutex = CreateMutex(NULL, FALSE, NULL))) {
        hal_err("create mutex error");
    }

    return mutex;
}

void HAL_MutexDestroy(_IN_ void *mutex)
{
    if (0 == CloseHandle(mutex)) {
        hal_err("destroy mutex error");
    }
}

void HAL_MutexLock(_IN_ void *mutex)
{
    if (WAIT_FAILED == WaitForSingleObject(mutex, INFINITE)) {
        hal_err("lock mutex error");
    }
}

void HAL_MutexUnlock(_IN_ void *mutex)
{
    ReleaseMutex(mutex);
}

void *HAL_Malloc(_IN_ uint32_t size)
{
    return malloc(size);
}

void *HAL_Realloc(_IN_ void *ptr, _IN_ uint32_t size)
{
    return realloc(ptr, size);
}

void HAL_Free(_IN_ void *ptr)
{
    free(ptr);
}

uint64_t HAL_UptimeMs(void)
{
    return (uint64_t)(GetTickCount());
}

void HAL_SleepMs(_IN_ uint32_t ms)
{
    Sleep(ms);
}

uint32_t orig_seed = 2;
void HAL_Srandom(uint32_t seed)
{
    orig_seed = seed;
}

uint32_t HAL_Random(uint32_t region)
{
    orig_seed = 1664525 * orig_seed + 1013904223;
    return (region > 0) ? (orig_seed % region) : 0;
}

void HAL_Printf(_IN_ const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    fflush(stdout);
}


int HAL_Snprintf(_IN_ char *str, const int len, const char *fmt, ...)
{
    int ret;
    va_list args;

    va_start(args, fmt);
    ret = _vsnprintf(str, len - 1, fmt, args);
    va_end(args);

    return ret;
}


int HAL_Vsnprintf(_IN_ char *str, _IN_ const int len, _IN_ const char *fmt, va_list ap)
{
    int ret;

    ret = _vsnprintf(str, len - 1, fmt, ap);

    return ret;
}


int HAL_SetProductKey(_IN_ char *product_key)
{
    int len = strlen(product_key);
#ifdef __DEMO__
    if (len > IOTX_PRODUCT_KEY_LEN) {
        return -1;
    }
    memset(_product_key, 0x0, IOTX_PRODUCT_KEY_LEN + 1);
    strncpy(_product_key, product_key, len);
#endif
    return len;
}


int HAL_SetDeviceName(_IN_ char *device_name)
{
    int len = strlen(device_name);
#ifdef __DEMO__
    if (len > IOTX_DEVICE_NAME_LEN) {
        return -1;
    }
    memset(_device_name, 0x0, IOTX_DEVICE_NAME_LEN + 1);
    strncpy(_device_name, device_name, len);
#endif
    return len;
}


int HAL_SetDeviceSecret(_IN_ char *device_secret)
{
    int len = strlen(device_secret);
#ifdef __DEMO__
    if (len > IOTX_DEVICE_SECRET_LEN) {
        return -1;
    }
    memset(_device_secret, 0x0, IOTX_DEVICE_SECRET_LEN + 1);
    strncpy(_device_secret, device_secret, len);
#endif
    return len;
}


int HAL_SetProductSecret(_IN_ char *product_secret)
{
    int len = strlen(product_secret);
#ifdef __DEMO__
    if (len > IOTX_PRODUCT_SECRET_LEN) {
        return -1;
    }
    memset(_product_secret, 0x0, IOTX_PRODUCT_SECRET_LEN + 1);
    strncpy(_product_secret, product_secret, len);
#endif
    return len;
}

int HAL_GetProductKey(_OU_ char *product_key)
{
    int len = strlen(_product_key);
    memset(product_key, 0x0, IOTX_PRODUCT_KEY_LEN);

#ifdef __DEMO__
    strncpy(product_key, _product_key, len);
#endif

    return len;
}

int HAL_GetProductSecret(_OU_ char *product_secret)
{
    int len = strlen(_product_secret);
    memset(product_secret, 0x0, IOTX_PRODUCT_SECRET_LEN);

#ifdef __DEMO__
    strncpy(product_secret, _product_secret, len);
#endif

    return len;
}

int HAL_GetDeviceName(_OU_ char *device_name)
{
    int len = strlen(_device_name);
    memset(device_name, 0x0, IOTX_DEVICE_NAME_LEN);

#ifdef __DEMO__
    strncpy(device_name, _device_name, len);
#endif

    return strlen(device_name);
}

int HAL_GetDeviceSecret(_OU_ char *device_secret)
{
    int len = strlen(_device_secret);
    memset(device_secret, 0x0, IOTX_DEVICE_SECRET_LEN);

#ifdef __DEMO__
    strncpy(device_secret, _device_secret, len);
#endif

    return len;
}


int HAL_GetFirmwareVersion(char *version)
{
    char *ver = "app-1.0.0-20180101.1000";
    int len = strlen(ver);
    memset(version, 0x0, IOTX_FIRMWARE_VER_LEN);
    strncpy(version, ver, IOTX_FIRMWARE_VER_LEN);
    version[len] = '\0';
    return strlen(version);
}

#if 1

void *HAL_SemaphoreCreate(void)
{
    return CreateSemaphore(NULL, 0, 1, NULL);
}

void HAL_SemaphoreDestroy(_IN_ void *sem)
{
    CloseHandle(sem);
}

void HAL_SemaphorePost(_IN_ void *sem)
{
    ReleaseSemaphore(sem, 1, NULL);

}

int HAL_SemaphoreWait(_IN_ void *sem, _IN_ uint32_t timeout_ms)
{
    uint32_t timeout = timeout_ms;
    if (timeout == (uint32_t) - 1) {
        timeout = INFINITE;
    }
    return WaitForSingleObject(sem, timeout);
}
#define DEFAULT_THREAD_SIZE 4096
int HAL_ThreadCreate(
            _OU_ void **thread_handle,
            _IN_ void *(*work_routine)(void *),
            _IN_ void *arg,
            _IN_ hal_os_thread_param_t *hal_os_thread_param,
            _OU_ int *stack_used)
{
    SIZE_T stack_size;
    (void)stack_used;

    if (!hal_os_thread_param || hal_os_thread_param->stack_size == 0) {
        stack_size = DEFAULT_THREAD_SIZE;
    } else {
        stack_size = hal_os_thread_param->stack_size;
    }
    thread_handle = CreateThread(NULL, stack_size,
                                 (LPTHREAD_START_ROUTINE)work_routine,
                                 arg, 0, NULL);
    if (thread_handle == NULL) {
        return -1;
    }
    return 0;
}

void HAL_ThreadDetach(_IN_ void *thread_handle)
{
    (void)thread_handle;
}

void HAL_ThreadDelete(_IN_ void *thread_handle)
{
    CloseHandle(thread_handle);
}
#endif  /* #if 0 */

#ifdef __DEMO__
    static FILE *fp;

    #define otafilename "/tmp/alinkota.bin"
#endif

void HAL_Firmware_Persistence_Start(void)
{
#ifdef __DEMO__
    fp = fopen(otafilename, "w");
    //    assert(fp);
#endif
    return;
}

int HAL_Firmware_Persistence_Write(_IN_ char *buffer, _IN_ uint32_t length)
{
#ifdef __DEMO__
    unsigned int written_len = 0;
    written_len = fwrite(buffer, 1, length, fp);

    if (written_len != length) {
        return -1;
    }
#endif
    return 0;
}

int HAL_Firmware_Persistence_Stop(void)
{
#ifdef __DEMO__
    if (fp != NULL) {
        fclose(fp);
    }
#endif

    return 0;
}

int HAL_Kv_Get(const char *key, void *buffer, int *buffer_len)
{
    return 0;
}

int HAL_Kv_Set(const char *key, const void *val, int len, int sync)
{
    return 0;
}


void HAL_UTC_Set(int64_t ms)
{

}

int64_t HAL_UTC_Get(void)
{
    return 0;
}

int HAL_GetNetifInfo(char *nif_str)
{
    const char *net_info = "WiFi|03ACDEFF0032";
    memset(nif_str, 0x0, IOTX_NETWORK_IF_LEN);
#ifdef __DEMO__
    /* if the device have only WIFI, then list as follow, note that the len MUST NOT exceed NIF_STRLEN_MAX */
    strncpy(nif_str, net_info, strlen(net_info));
    /* if the device have ETH, WIFI, GSM connections, then list all of them as follow, note that the len MUST NOT exceed NIF_STRLEN_MAX */
    // const char *multi_net_info = "ETH|0123456789abcde|WiFi|03ACDEFF0032|Cellular|imei_0123456789abcde|iccid_0123456789abcdef01234|imsi_0123456789abcde|msisdn_86123456789ab");
    // strncpy(nif_str, multi_net_info, strlen(multi_net_info));
#endif
    return strlen(nif_str);
}

uint32_t HAL_Wifi_Get_IP(_OU_ char ip_str[NETWORK_ADDR_LEN], _IN_ const char *ifname)
{
    return 0;
}

void   *HAL_Timer_Create(const char *name, void(*func)(void *), void *user_data)
{
    return 0;
}

int     HAL_Timer_Start(void *t, int ms)
{
    return 0;
}


int     HAL_Timer_Stop(void *t)
{
    return 0;
}

int     HAL_Timer_Delete(void *timer)
{
    return 0;
}

intptr_t HAL_UDP_create_without_connect(_IN_ const char *host, _IN_ unsigned short port)
{
    return 0;
}

int HAL_UDP_sendto(_IN_ intptr_t sockfd,
                   _IN_ const NetworkAddr *p_remote,
                   _IN_ const unsigned char *p_data,
                   _IN_ unsigned int datalen,
                   _IN_ unsigned int timeout_ms)
{
    return 0;
}

int HAL_UDP_recvfrom(_IN_ intptr_t sockfd,
                     _OU_ NetworkAddr *p_remote,
                     _OU_ unsigned char *p_data,
                     _IN_ unsigned int datalen,
                     _IN_ unsigned int timeout_ms)
{
    return 0;
}

int HAL_UDP_joinmulticast(_IN_ intptr_t sockfd,
                          _IN_ char *p_group)
{
    return 0;
}

int HAL_UDP_close_without_connect(_IN_ intptr_t sockfd)
{
    return 0;
}

void  HAL_Reboot(void)
{
    return;
}

char *HAL_Wifi_Get_Mac(_OU_ char mac_str[HAL_MAC_LEN])
{
    return 0;
}

int     HAL_Kv_Del(const char *key)
{
    return 0;
}


int HAL_Aes128_Cbc_Encrypt(
            _IN_ p_HAL_Aes128_t aes,
            _IN_ const void *src,
            _IN_ size_t blockNum,
            _OU_ void *dst)
{
    return 0;
}

void *HAL_Fopen(const char *path, const char *mode)
{
    return (void *)fopen(path, mode);
}

uint32_t HAL_Fread(void *buff, uint32_t size, uint32_t count, void *stream)
{
    return fread(buff, size, count, (FILE *)stream);
}

uint32_t HAL_Fwrite(const void *ptr, uint32_t size, uint32_t count, void *stream)
{
    return fwrite(ptr, size, count, (FILE *)stream);
}

int HAL_Fseek(void *stream, long offset, int framewhere)
{
    return fseek((FILE *)stream, offset, framewhere);
}

int HAL_Fclose(void *stream)
{
    return fclose((FILE *)stream);
}

long HAL_Ftell(void *stream)
{
    return ftell((FILE *)stream);
}