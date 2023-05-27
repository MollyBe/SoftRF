/*
 * Platform_RP2040.h
 * Copyright (C) 2023 Linar Yusupov
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
#if defined(ARDUINO_ARCH_RP2040)

#ifndef PLATFORM_RP2040_H
#define PLATFORM_RP2040_H

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#define Serial_setDebugOutput(x) ({})
#define WIFI_STA_TIMEOUT         20000
extern WebServer server;
#else
#include <Arduino.h>
#define EXCLUDE_WIFI
#define EXCLUDE_BLUETOOTH
#endif /* ARDUINO_RASPBERRY_PI_PICO_W */

/* Maximum of tracked flying objects is now SoC-specific constant */
#define MAX_TRACKING_OBJECTS  8

#define SOC_ADC_VOLTAGE_DIV   (3.0) // 20K + 10K voltage divider of VSYS

#define SerialInput           Serial1
#define SerialOutput          Serial2

#if !defined(ARDUINO_ARCH_MBED)
#define USBSerial             Serial
#else
#define USBSerial             SerialUSB
#endif /* ARDUINO_ARCH_MBED */

#define INA219_ADDRESS_ALT    (0x43) // 1000011 (A0=SCL, A1=GND)

#define MAX_FILENAME_LEN      64
#define WAV_FILE_PREFIX       "/Audio/"

#define POWER_SAVING_WIFI_TIMEOUT 600000UL /* 10 minutes */

enum RP2040_board_id {
  RP2040_RAK11300,
  RP2040_RESERVED1,
  RP2040_RPIPICO,
  RP2040_RPIPICO_W,
  RP2040_WEACT,
};

/* Console I/O */
#define SOC_GPIO_PIN_CONS_RX  (5u)
#define SOC_GPIO_PIN_CONS_TX  (4u)

/* Peripherals */
#define SOC_GPIO_PIN_GNSS_RX  (1u)
#define SOC_GPIO_PIN_GNSS_TX  (0u)

/* Raspberry Pico W SPI pins mapping */
#define SOC_W_PIN_MOSI        (24u)
#define SOC_W_PIN_SCK         (29u)
#define SOC_W_PIN_SS          (25u)

/* Waveshare Pico SPI pins mapping */
#define SOC_EPD_PIN_MOSI_WS   (11u)
#define SOC_EPD_PIN_MISO_WS   (28u)
#define SOC_EPD_PIN_SCK_WS    (10u)
#define SOC_EPD_PIN_SS_WS     (9u)

/* Waveshare Pico EPD pins mapping */
#define SOC_EPD_PIN_DC_WS     (8u)
#define SOC_EPD_PIN_RST_WS    (12u)
#define SOC_EPD_PIN_BUSY_WS   (13u)

/* Waveshare Pico UPS-B I2C1 */
#define SOC_GPIO_PIN_SDA      (6u)
#define SOC_GPIO_PIN_SCL      (7u)

/* Waveshare Pico keys mapping */
#define SOC_GPIO_PIN_KEY0     (15u)
#define SOC_GPIO_PIN_KEY1     (17u)
#define SOC_GPIO_PIN_KEY2     (2u)

#define SOC_GPIO_PIN_BUTTON   (23u)

#define SOC_GPIO_PIN_USBH_DP  (20u)  // Pin used as D+ for host, D- = D+ + 1
#define SOC_GPIO_PIN_USBH_DN  (21u)

#define SOC_GPIO_PIN_VSYS     (29u) // Pico
#define SOC_GPIO_PIN_CYW43_EN (25u) // Pico W

#define SOC_GPIO_PIN_STATUS   PIN_LED // Pico/WeAct - 25, W - 32 (CYW43 GPIO 0)
#define SOC_GPIO_PIN_BATTERY  SOC_GPIO_PIN_VSYS

#define SOC_GPIO_PIN_PWM_OUT  (3u)
#define EXCLUDE_AUDIO               // pending

#if !defined(ARDUINO_ARCH_MBED)
#define USE_BOOTSEL_BUTTON
#else
#define EXCLUDE_EEPROM
#endif /* ARDUINO_ARCH_MBED */

/* Experimental */
#if defined(USE_TINYUSB)
#define USE_USB_HOST
#endif /* USE_TINYUSB */

#endif /* PLATFORM_RP2040_H */
#endif /* ARDUINO_ARCH_RP2040 */
