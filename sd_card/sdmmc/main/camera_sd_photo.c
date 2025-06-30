#include "esp_camera.h"
#include "esp_log.h"
#include "sdmmc_cmd.h"    // sdmmc_card_t 정의
#include "esp_err.h"      // esp_err_t 정의
#include <time.h>
#include <stdio.h>

static const char *TAG = "cam_sd";

// sd 카드 마운트 함수에서 넘겨 받은 전역 포인터
extern sdmmc_card_t* card;

esp_err_t save_photo_to_sd()
{
    // 1) 카메라에서 프레임 버퍼 얻기
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera capture failed");
        return ESP_FAIL;
    }

    // 2) 타임스탬프 기반 파일명 생성
    char filename[64];
    time_t now = time(NULL);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);
    strftime(filename, sizeof(filename),
             "/sdcard/photo_%Y%m%d_%H%M%S.jpg", &timeinfo);

    // 3) 파일 열기
    FILE *f = fopen(filename, "wb");
    if (!f) {
        ESP_LOGE(TAG, "Failed to open file for writing: %s", filename);
        esp_camera_fb_return(fb);
        return ESP_FAIL;
    }

    // 4) JPEG 데이터 쓰기
    size_t written = fwrite(fb->buf, 1, fb->len, f);
    fclose(f);
    esp_camera_fb_return(fb);

    // 5) 쓰기 확인
    if (written != fb->len) {
        ESP_LOGE(TAG, "Incomplete write: %u of %u bytes",
                 (unsigned)written, (unsigned)fb->len);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Saved photo to %s", filename);
    return ESP_OK;
}
