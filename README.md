# Storage Examples

esp32-cam 에다가 sd  카드 삽입해서 저장하는 예제입니다.
참고로 sd 카드는 sandisk를 사용했습니다.

Storage and management of user and system data in module’s flash and on external memory / devices.
This directory contains a range of examples ESP-IDF projects. These are intended to demonstrate the storage features, and to provide code that you can copy and adapt into your own projects.

# Example Layout

The examples are grouped into sub-directories by category. Each category directory contains one or more example projects:

* `fatfs_basic` minimal example of FatFS usage on SPI FLASH
* `fatfs_advanced` example demonstrates how to use advanced features for working with FatFS such as automatic partition generation
* `custom_flash_driver` example demonstrates how to implement your own flash chip driver by overriding the default driver.
* `emmc` example demonstrates how to use an eMMC chip with an ESP device.
* `ext_flash_fatfs` example demonstrates how to use FATFS partition with external SPI FLASH chip.
* `fatfsgen` example demonstrates how to use FATFS partition generator
* `nvs_bootloader` example demonstrates how to read data from NVS in the bootloader code.
* `nvs_rw_blob` example demonstrates how to read and write a single integer value and a blob (binary large object) using NVS to preserve them between ESP module restarts.
* `nvs_rw_value` example demonstrates how to read and write a single integer value using NVS.
* `nvs_rw_value_cxx` example demonstrates how to read and write a single integer value using NVS (it uses the C++ NVS handle API).
* `nvs_console` example demonstrates how to use NVS through an interactive console interface.
* `partition_api` examples demonstrate how to use different partition APIs.
* `parttool` example demonstrates common operations the partitions tool allows the user to perform.
* `sd_card` examples demonstrate how to use an SD card with an ESP device.
* `semihost_vfs` example demonstrates how to use semihosting VFS driver with ESP device.
* `spiffs` example demonstrates how to use SPIFFS with ESP device.
* `spiffsgen` example demonstrates how to use the SPIFFS image generation tool spiffsgen.py to automatically create a SPIFFS.
* `wear_levelling` example demonstrates how to use wear levelling library and FATFS library to store files in a partition inside SPI flash.

# More

See the [README.md](../README.md) file in the upper level [examples](../) directory for more information about examples.
