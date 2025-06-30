// main/camera_init.c

#include "esp_camera.h"
#include "esp_log.h"

static const char *TAG = "camera";

void init_camera(void)
{
    camera_config_t config = {
        // AI-Thinker ESP32-CAM 핀맵
        .pin_pwdn       = 32,
        .pin_reset      = -1,
        .pin_xclk       = 0,
        .pin_sccb_sda   = 26,
        .pin_sccb_scl   = 27,
        .pin_d7         = 35,
        .pin_d6         = 34,
        .pin_d5         = 39,
        .pin_d4         = 36,
        .pin_d3         = 21,
        .pin_d2         = 19,
        .pin_d1         = 18,
        .pin_d0         = 5,
        .pin_vsync      = 25,
        .pin_href       = 23,
        .pin_pclk       = 22,

        .xclk_freq_hz   = 20000000,
        .pixel_format   = PIXFORMAT_JPEG,

        // 해상도: VGA (640×480)
        .frame_size     = FRAMESIZE_VGA,
        .jpeg_quality   = 12,
        .fb_count       = 1,                // 버퍼 1개

        // **DRAM 강제 할당**: CAMERA_FB_IN_DRAM 또는 CAMERA_FB_DRAM
        .fb_location    = CAMERA_FB_IN_DRAM,
    };

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed: %s", esp_err_to_name(err));
        return;
    }
    ESP_LOGI(TAG, "Camera initialized (VGA · DRAM)");
}
