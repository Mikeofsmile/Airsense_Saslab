idf_component_register(SRCS "Airsense_Sanslab.c" "ds3231.c"
"i2cdev"        "datamanager.c"         "http_server.c"
"devicemanager.c"            "mlx90614_API.c"
"mlx90614_Driver.c"         "wifi_app.c"         "sntp_time_sync.c"
"wifi_reset_button.c"          "mqsensor.c" "ds3231timer.c"  "ads111x.c" "sdcard.c"
  INCLUDE_DIRS "."

EMBED_FILES(webpage/app.css webpage/app.js webpage/favicon.ico webpage/index.html webpage/jquery-3.3.1.min.js)

)
