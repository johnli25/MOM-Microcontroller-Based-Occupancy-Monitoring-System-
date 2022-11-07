#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include "driver/gpio.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include "LinkedList.h"


#define LED_GPIO_PIN                     13
#define WIFI_CHANNEL_SWITCH_INTERVAL    500
#define WIFI_CHANNEL_MAX                 14
#define NUM_IGNORABLE_OUIS               74
#define BYTES_IN_OUI                      3
#define BYTES_IN_MAC                      6
#define MAC_LIST_LEN                    256


typedef struct {
  unsigned frame_ctrl:16;
  unsigned duration_id:16;
  uint8_t addr1[6]; /* receiver address */
  uint8_t addr2[6]; /* sender address */
  uint8_t addr3[6]; /* filtering address */
  unsigned sequence_ctrl:16;
  uint8_t addr4[6]; /* optional */
} wifi_ieee80211_mac_hdr_t;

typedef struct {
  wifi_ieee80211_mac_hdr_t hdr;
  uint8_t payload[0]; /* network data ended with 4 bytes csum (CRC32) */
} wifi_ieee80211_packet_t;

uint8_t ignorable_ouis[NUM_IGNORABLE_OUIS][BYTES_IN_OUI] = {
  {0,11,134},
  {0,26,30},
  {0,36,108},
  {216,199,200},
  {108,243,127},
  {36,222,198},
  {156,28,18},
  {24,100,114},
  {172,163,30},
  {148,180,15},
  {240,92,25},
  {132,212,126},
  {4,189,136},
  {64,227,214},
  {112,58,14},
  {32,76,3},
  {180,93,80},
  {56,33,199},
  {124,87,60},
  {144,32,194},
  {244,46,127},
  {188,159,228},
  {248,96,240},
  {208,21,166},
  {136,58,48},
  {184,58,90},
  {16,79,88},
  {232,38,137},
  {208,211,224},
  {184,212,231},
  {36,98,206},
  {100,232,129},
  {204,208,131},
  {140,133,193},
  {28,40,175},
  {40,222,101},
  {252,127,241},
  {56,16,240},
  {52,138,18},
  {204,136,199},
  {236,2,115},
  {68,91,237},
  {96,38,239},
  {208,77,198},
  {188,215,165},
  {148,100,36},
  {24,122,59},
  {168,91,247},
  {148,96,213},
  {108,196,159},
  {236,80,170},
  {72,47,107},
  {240,97,192},
  {136,37,16},
  {212,224,83},
  {176,31,140},
  {72,180,195},
  {12,151,95},
  {52,58,32},
  {32,156,180},
  {116,158,117},
  {220,183,172},
  {68,18,68},
  {164,14,117},
  {240,26,160},
  {56,189,122},
  {84,215,227},
  {160,160,1},
  {184,39,235},
  {220,166,50},
  {58,53,65},
  {228,95,1},
  {40,205,193},
  {255,255,255},
};

typedef struct {
  uint8_t mac_addr[BYTES_IN_MAC];
  uint64_t timestamp;  
} mac_list_item_t;

#endif // WIFI_SCANNER_H