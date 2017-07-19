

#ifndef _ALIOT_COMMON_TIMER_H_
#define _ALIOT_COMMON_TIMER_H_

#include "iot_import.h"

typedef struct {
    uint32_t time;
} iotx_time_t;


void iotx_time_start(iotx_time_t *timer);

uint32_t utils_time_spend(iotx_time_t *start);

uint32_t iotx_time_left(iotx_time_t *end);

uint32_t utils_time_is_expired(iotx_time_t *timer);

void iotx_time_init(iotx_time_t *timer);

void utils_time_cutdown(iotx_time_t *timer, uint32_t millisecond);

uint32_t utils_time_get_ms(void);

#endif /* _ALIOT_COMMON_TIMER_H_ */
