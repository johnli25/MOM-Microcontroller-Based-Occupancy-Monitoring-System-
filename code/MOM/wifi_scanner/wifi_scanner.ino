#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define LED_GPIO_PIN                     13
#define WIFI_CHANNEL_SWITCH_INTERVAL    500
#define WIFI_CHANNEL_MAX                 14
#define NUM_IGNORABLE_OUIS               73
#define BYTES_IN_OUI                      3
#define BYTES_IN_MAC                      6
#define MAC_LIST_LEN                    128

uint8_t level = 0, channel = 1;

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

static uint8_t ignorable_ouis[NUM_IGNORABLE_OUIS][BYTES_IN_OUI] = {
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
};

static uint8_t seen_macs[MAC_LIST_LEN][BYTES_IN_MAC];
static int seen_macs_tail;

static esp_err_t event_handler(void *ctx, system_event_t *event);
static void wifi_sniffer_init(void);
static void wifi_sniffer_set_channel(uint8_t channel);
static const char *wifi_sniffer_packet_type2str(wifi_promiscuous_pkt_type_t type);
static void wifi_sniffer_packet_handler(void *buff, wifi_promiscuous_pkt_type_t type);
static bool is_ignorable_oui(uint8_t oui0, uint8_t oui1, uint8_t oui2);
static void mac_list_init(void);
static void add_mac_to_list(uint8_t mac0, uint8_t mac1, uint8_t mac2, uint8_t mac3, uint8_t mac4, uint8_t mac5);

void mac_list_init(void) {
  for (int i = 0; i < MAC_LIST_LEN; i++) {
    for (int j = 0; j < BYTES_IN_MAC; j++) {
      seen_macs[i][j] = 0;
    }
  }
  seen_macs_tail = 0;
}

void add_mac_to_list(uint8_t mac0, uint8_t mac1, uint8_t mac2, uint8_t mac3, uint8_t mac4, uint8_t mac5) {
  
}

bool is_ignorable_oui(uint8_t oui0, uint8_t oui1, uint8_t oui2) {
  int match_count;
  for (int i = 0; i < NUM_IGNORABLE_OUIS; i++) {
    match_count = 0;
    if (ignorable_ouis[i][0] == oui0) {
      match_count++;
    }
    if (ignorable_ouis[i][1] == oui1) {
      match_count++;
    }
    if (ignorable_ouis[i][2] == oui2) {
      match_count++;
    }
    if (match_count == BYTES_IN_OUI) {
      return true;
    }
  }
  return false;
}

esp_err_t event_handler(void *ctx, system_event_t *event)
{
  return ESP_OK;
}

void wifi_sniffer_init(void)
{
  nvs_flash_init();
  tcpip_adapter_init();
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
  ESP_ERROR_CHECK( esp_wifi_set_country_code("US", false) );
  ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_NULL) );
  ESP_ERROR_CHECK( esp_wifi_start() );
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&wifi_sniffer_packet_handler);
}

void wifi_sniffer_set_channel(uint8_t channel)
{
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
}

const char * wifi_sniffer_packet_type2str(wifi_promiscuous_pkt_type_t type)
{
  switch(type) {
  case WIFI_PKT_MGMT: return "MGMT";
  case WIFI_PKT_DATA: return "DATA";
  default:  
  case WIFI_PKT_MISC: return "MISC";
  }
}

void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type)
{
  // if (type != WIFI_PKT_MGMT)
    // return;

  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buff;
  const wifi_ieee80211_packet_t *ipkt = (wifi_ieee80211_packet_t *)ppkt->payload;
  const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;

  if (ppkt->rx_ctrl.rssi <= -60)
    return;

  if (is_ignorable_oui(hdr->addr2[0], hdr->addr2[1], hdr->addr2[2]))
    return;

  printf("PACKET TYPE=%s, CHAN=%02d, RSSI=%02d,"
    " ADDR1=%02x:%02x:%02x:%02x:%02x:%02x,"
    " ADDR2=%02x:%02x:%02x:%02x:%02x:%02x,"
    " ADDR3=%02x:%02x:%02x:%02x:%02x:%02x\n",
    wifi_sniffer_packet_type2str(type),
    ppkt->rx_ctrl.channel,
    ppkt->rx_ctrl.rssi,
    /* ADDR1 */
    hdr->addr1[0],hdr->addr1[1],hdr->addr1[2],
    hdr->addr1[3],hdr->addr1[4],hdr->addr1[5],
    /* ADDR2 */
    hdr->addr2[0],hdr->addr2[1],hdr->addr2[2],
    hdr->addr2[3],hdr->addr2[4],hdr->addr2[5],
    /* ADDR3 */
    hdr->addr3[0],hdr->addr3[1],hdr->addr3[2],
    hdr->addr3[3],hdr->addr3[4],hdr->addr3[5]
  );
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  delay(10);
  wifi_sniffer_init();
  mac_list_init();
  pinMode(LED_GPIO_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  delay(500);
  if (digitalRead(LED_GPIO_PIN) == LOW)
    digitalWrite(LED_GPIO_PIN, HIGH);
  else
    digitalWrite(LED_GPIO_PIN, LOW);
  vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  wifi_sniffer_set_channel(channel);
  channel = (channel % WIFI_CHANNEL_MAX) + 5;
}