idf_component_register(SRCS
    "camera_init.c"
    "camera_sd_photo.c"
    "app_main.c"
INCLUDE_DIRS ""
REQUIRES
    esp32-camera
    driver
    sdmmc
    fatfs
    nvs_flash
    lwip      # LwIP 안에 SNTP 앱이 포함됨
)
