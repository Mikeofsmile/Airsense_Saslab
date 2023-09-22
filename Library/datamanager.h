#ifndef __DATAMANAGER_H__
#define __DATAMANAGER_H__

#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include <string.h>

struct dataSensor_st
{
    uint64_t timeStamp;

    float temperature_object;
    float temperature_ambient;
    float LPG;
    float CH4;
#if(0)
    uint32_t CO2;
    uint32_t NO;
    uint32_t CO;
    uint32_t SO2;
#endif
};

const char dataSensor_templateSaveToSDCard[] = "%s,%0.2f,%0.2f,%0.2f,%0.2f";


#endif
