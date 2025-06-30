// main/app_main.c

#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/apps/sntp.h"
#include <time.h>

// camera_init.c, camera_sd_photo.c 에서 제공하는 함수들
void init_camera(void);
esp_err_t save_photo_to_sd(void);

static const char *TAG = "main";
sdmmc_card_t* card;  // SD 마운트 후에 값이 채워집니다

static void mount_sdcard(void)
{
    esp_vfs_fat_sdmmc_mount_config_t mount_cfg = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_cfg = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_cfg.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_cfg, &mount_cfg, &card);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "SD mount failed: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "SD mounted: %s", card->cid.name);
    }
}

static void sync_time(void)
{
    // SNTP 클라이언트 모드
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_setservername(1, "time.google.com");
    sntp_init();

    // 시간 동기화 완료 대기
    for (int i = 0; i < 10; i++) {
        time_t now = time(NULL);
        if (now > 8 * 3600 * 2) {  // 1970년 2일치 넘어가면 성공
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }

    // 타임존 설정 (Korea Standard Time)
    setenv("TZ", "KST-9", 1);
    tzset();

    time_t now = time(NULL);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);
    ESP_LOGI(TAG, "Current time: %s", asctime(&timeinfo));
}

static void cam_task(void *arg)
{
    while (1) {
        if (save_photo_to_sd() == ESP_OK) {
            // save_photo_to_sd 내부에서 로그 출력
        }
        vTaskDelay(pdMS_TO_TICKS(5000));  // 5초마다 촬영
    }
}

void app_main(void)
{
    // 1) NVS 초기화
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    // 2) SD 카드 마운트
    mount_sdcard();

    // 3) 카메라 초기화
    init_camera();

    // 4) SNTP를 통한 시간 동기화
    sync_time();

    // 5) 사진 촬영 태스크 생성
    xTaskCreate(cam_task, "cam_task", 8192, NULL, 5, NULL);
}
