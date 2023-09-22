/*
 * tasks_common.h
 *
 *  Created on: Oct 17, 2021
 *      Author: kjagu
 */

#ifndef MAIN_TASKS_COMMON_H_
#define MAIN_TASKS_COMMON_H_

// WiFi application task
#define WIFI_APP_TASK_STACK_SIZE			4096
#define WIFI_APP_TASK_PRIORITY				5
#define WIFI_APP_TASK_CORE_ID				0

// HTTP Server task
#define HTTP_SERVER_TASK_STACK_SIZE			8192
#define HTTP_SERVER_TASK_PRIORITY			4
#define HTTP_SERVER_TASK_CORE_ID			0

// HTTP Server Monitor task
#define HTTP_SERVER_MONITOR_STACK_SIZE		4096
#define HTTP_SERVER_MONITOR_PRIORITY		3
#define HTTP_SERVER_MONITOR_CORE_ID			0

// Wifi Reset Button task
#define WIFI_RESET_BUTTON_TASK_STACK_SIZE	2048
#define WIFI_RESET_BUTTON_TASK_PRIORITY		6
#define WIFI_RESET_BUTTON_TASK_CORE_ID		0


// SNTP Time Sync task
#define SNTP_TIME_SYNC_TASK_STACK_SIZE		4096
#define SNTP_TIME_SYNC_TASK_PRIORITY		4
#define SNTP_TIME_SYNC_TASK_CORE_ID			1



#define MQ_MEASUREMENT_INTERVAL_MS 4000

/**
 * CO2 sensor has to warm up, so data should not be sent to thingspeak in the very first minutes. Sensor data
 * in the first few minutes are not reliable.
 *
 * WARM_UP_ITERATIONS=3 means that we skip the first 3 thingspeak cycles (eg. 3 minutes, if THINGSPEAK_REPORT_INTERVAL
 * is one minute)
 */
#define WARM_UP_ITERATIONS 3


#endif /* MAIN_TASKS_COMMON_H_ */
