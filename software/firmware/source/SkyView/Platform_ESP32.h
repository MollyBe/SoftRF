/*
 * Platform_ESP32.h
 * Copyright (C) 2019-2023 Linar Yusupov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#if defined(ESP32)

#ifndef PLATFORM_ESP32_H
#define PLATFORM_ESP32_H

#if defined(ARDUINO)
#include <Arduino.h>
#endif /* ARDUINO */

#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

/* Maximum of tracked flying objects is now SoC-specific constant */
#define MAX_TRACKING_OBJECTS  9

#define SerialInput           Serial1

/* Peripherals */

/* TTGO T5 and T5S SPI pins mapping */
#define SOC_GPIO_PIN_MOSI_T5S 23
#define SOC_GPIO_PIN_MISO_T5S 12
#define SOC_GPIO_PIN_SCK_T5S  18
#define SOC_GPIO_PIN_SS_T5S   5

/* TTGO T5S EPD pins mapping */
#define SOC_EPD_PIN_DC_T5S    17
#define SOC_EPD_PIN_RST_T5S   16
#define SOC_EPD_PIN_BUSY_T5S  4

/* TTGO T5S microSD pins mapping */
#define SOC_SD_PIN_MOSI_T5S   15
#define SOC_SD_PIN_MISO_T5S   2
#define SOC_SD_PIN_SCK_T5S    14
#define SOC_SD_PIN_SS_T5S     13

/* TTGO T5S I2S-out pins mapping */
#define SOC_GPIO_PIN_BCLK     26
#define SOC_GPIO_PIN_LRCLK    25
#define SOC_GPIO_PIN_DOUT     19

/* TTGO T5S buttons mapping */
#define SOC_BUTTON_MODE_T5S   37
#define SOC_BUTTON_UP_T5S     38
#define SOC_BUTTON_DOWN_T5S   39

/* TTGO T5S green LED mapping */
#define SOC_GPIO_PIN_LED_T5S  22

#if defined(CONFIG_IDF_TARGET_ESP32)
#define SOC_GPIO_PIN_GNSS_RX  21
#define SOC_GPIO_PIN_GNSS_TX  22

#define SOC_BUTTON_MODE_DEF   0

/* Waveshare ESP32 SPI pins mapping */
#define SOC_GPIO_PIN_MOSI_WS  14
#define SOC_GPIO_PIN_MISO_WS  12
#define SOC_GPIO_PIN_SCK_WS   13
#define SOC_GPIO_PIN_SS_WS    15

/* Waveshare ESP32 EPD pins mapping */
#define SOC_EPD_PIN_DC_WS     27
#define SOC_EPD_PIN_RST_WS    26
#define SOC_EPD_PIN_BUSY_WS   25

#elif defined(CONFIG_IDF_TARGET_ESP32S2)
#define SOC_GPIO_PIN_GNSS_RX  1
#define SOC_GPIO_PIN_GNSS_TX  2

#define SOC_BUTTON_MODE_DEF   0

/* Waveshare ESP32-S2 SPI pins mapping */
#define SOC_GPIO_PIN_MOSI_WS  35
#define SOC_GPIO_PIN_MISO_WS  33
#define SOC_GPIO_PIN_SCK_WS   36
#define SOC_GPIO_PIN_SS_WS    34

/* Waveshare ESP32-S2 EPD pins mapping */
#define SOC_EPD_PIN_DC_WS     37
#define SOC_EPD_PIN_RST_WS    38
#define SOC_EPD_PIN_BUSY_WS   39

#elif defined(CONFIG_IDF_TARGET_ESP32S3)
#define SOC_GPIO_PIN_GNSS_RX  9
#define SOC_GPIO_PIN_GNSS_TX  8

#define SOC_BUTTON_MODE_DEF   0

/* Waveshare ESP32-S3 SPI pins mapping */
#define SOC_GPIO_PIN_MOSI_WS  35
#define SOC_GPIO_PIN_MISO_WS  33
#define SOC_GPIO_PIN_SCK_WS   36
#define SOC_GPIO_PIN_SS_WS    34

/* Waveshare ESP32-S3 EPD pins mapping */
#define SOC_EPD_PIN_DC_WS     37
#define SOC_EPD_PIN_RST_WS    38
#define SOC_EPD_PIN_BUSY_WS   39

#elif defined(CONFIG_IDF_TARGET_ESP32C3)
#define SOC_GPIO_PIN_GNSS_RX  10  /* D4 */
#define SOC_GPIO_PIN_GNSS_TX  7

#define SOC_BUTTON_MODE_DEF   9  /* D3 */

/* Waveshare ESP32-C3 SPI pins mapping */
#define SOC_GPIO_PIN_MOSI_WS  5  /* D7 */
#define SOC_GPIO_PIN_MISO_WS  4  /* D6 */
#define SOC_GPIO_PIN_SCK_WS   3  /* D5 */
#define SOC_GPIO_PIN_SS_WS    8  /* D8 */

/* Waveshare ESP32-C3 EPD pins mapping */
#define SOC_EPD_PIN_DC_WS     18 /* D2 */
#define SOC_EPD_PIN_RST_WS    19 /* D1 */
#define SOC_EPD_PIN_BUSY_WS   2  /* D0 */
#else
#error "This ESP32 family build variant is not supported!"
#endif /* CONFIG_IDF_TARGET_ESP32 */

/* Boya Microelectronics Inc. */
#define BOYA_ID               0x68
#define BOYA_BY25Q32AL        0x4016

/* ST / SGS/Thomson / Numonyx / XMC(later acquired by Micron) */
#define ST_ID                 0x20
#define XMC_XM25QH128C        0x4018
#define XMC_XM25QH32B         0x4016

#define MakeFlashId(v,d)      ((v  << 16) | d)
#define CCCC(c1, c2, c3, c4)  ((c4 << 24) | (c3 << 16) | (c2 << 8) | c1)

#define MAX_FILENAME_LEN      64
#define WAV_FILE_PREFIX       "/Audio/"

#define POWER_SAVING_WIFI_TIMEOUT 600000UL /* 10 minutes */

/* these are data structures to process wav file */
typedef enum headerState_e {
    HEADER_RIFF, HEADER_FMT, HEADER_DATA, DATA
} headerState_t;

typedef struct wavRiff_s {
    uint32_t chunkID;
    uint32_t chunkSize;
    uint32_t format;
} wavRiff_t;

typedef struct wavProperties_s {
    uint32_t chunkID;
    uint32_t chunkSize;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
} wavProperties_t;

extern bool loopTaskWDTEnabled;

extern WebServer server;

//#define BUILD_SKYVIEW_HD

#if defined(CONFIG_IDF_TARGET_ESP32C3)
#define EXCLUDE_AUDIO
#endif /* CONFIG_IDF_TARGET_ESP32C3 */

#endif /* PLATFORM_ESP32_H */

#endif /* ESP32 */
