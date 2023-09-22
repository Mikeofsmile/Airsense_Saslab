
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/apps/sntp.h"
#include "../Library/sntp_time_sysc.h"
#include "../Library/tasks_common.h"
#include "../Library/http_server.h"
#include "../Library/wifi_app.h"


static const char TAG[] = "sntp_time_sync";

// SNTP operating mode set status
static bool sntp_op_mode_set = false;
void sntp_init_func()
{
    ESP_LOGI(__func__, "Initializing SNTP.");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_init();
}

esp_err_t sntp_setTime(struct tm *timeInfo, time_t *timeNow)
{
    for (size_t i = 0; (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET) && (i < RETRY_SET_TIME_SYSTEM); i++)
    {
        ESP_LOGI(__func__, "Waiting for system time to be set...");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    time(timeNow);
    localtime_r(timeNow, timeInfo);

    char timeString[64];

    // Set timezone to VietNam Standard Time
    setenv("TZ", "GMT-07", 1);
    tzset();
    localtime_r(timeNow, timeInfo);
    strftime(timeString, sizeof(timeString), "%c", timeInfo);
    ESP_LOGI(__func__, "The current date/time in Viet Nam is: %s ", timeString);
    return ESP_OK;
}

static void sntp_time_sync_init_sntp(void)
{
	ESP_LOGI(TAG, "Initializing the SNTP service");

	if (!sntp_op_mode_set)
	{
		// Set the operating mode
		sntp_setoperatingmode(SNTP_OPMODE_POLL);
		sntp_op_mode_set = true;
	}

	sntp_setservername(0, "pool.ntp.org");

	// Initialize the servers
	sntp_init();

	// Let the http_server know service is initialized
	http_server_monitor_send_message(HTTP_MSG_TIME_SERVICE_INITIALIZED);
}

/**
 * Gets the current time and if the current time is not up to date,
 * the sntp_time_synch_init_sntp function is called.
 */

static void sntp_time_sync_obtain_time(void)
{
	time_t now = 0;
	struct tm time_info = {0};

	time(&now);
	localtime_r(&now, &time_info);

	// Check the time, in case we need to initialize/reinitialize
	if (sntp_op_mode_set == false || time_info.tm_year < (2016 - 1900))
	{
		sntp_time_sync_init_sntp();
		// Set the local time zone
		setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
		tzset();
	}
}

/**
 * The SNTP time synchronization task.
 * @param arg pvParam.
 */
static void sntp_time_sync(void *pvParam)
{
	while (1)
	{
		sntp_time_sync_obtain_time();
		vTaskDelay(10000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

char* sntp_time_sync_get_time(void)
{
	static char time_buffer[100] = {0};

	time_t now = 0;
	struct tm time_info = {0};

	time(&now);
	localtime_r(&now, &time_info);

	if (time_info.tm_year < (2016 - 1900))
	{
		ESP_LOGI(TAG, "Time is not set yet");
	}
	else
	{
		strftime(time_buffer, sizeof(time_buffer), "%d.%m.%Y %H:%M:%S", &time_info);
		ESP_LOGI(TAG, "Current time info: %s", time_buffer);
	}

	return time_buffer;
}

void sntp_time_sync_task_start(void)
{
	xTaskCreatePinnedToCore(&sntp_time_sync, "sntp_time_sync", SNTP_TIME_SYNC_TASK_STACK_SIZE, NULL, SNTP_TIME_SYNC_TASK_PRIORITY, NULL, SNTP_TIME_SYNC_TASK_CORE_ID);
}
