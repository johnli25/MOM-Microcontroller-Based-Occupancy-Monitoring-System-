#include "wifi_scanner.h"

uint8_t level = 0, channel = 1;
hw_timer_t * uptime_timer = NULL;
hw_timer_t * interrupt_timer = NULL;
LinkedList<mac_list_item_t> mac_list = LinkedList<mac_list_item_t>();

void interrupt_timer_callback(void) {
  printf("Interrupt callback.");
}

void timer_init(void) {
  uptime_timer = timerBegin(0, 80, true);
  interrupt_timer = timerBegin(1, 80, false);
  timerAttachInterrupt(interrupt_timer, &interrupt_timer_callback, true);
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

void add_mac_to_list(uint8_t mac0, uint8_t mac1, uint8_t mac2, uint8_t mac3, uint8_t mac4, uint8_t mac5) {
  mac_list_item_t seen_mac;
  int i;
  if (is_ignorable_oui(mac0, mac1, mac2)) {
    return;
  }
  seen_mac.mac_addr[0] = mac0;
  seen_mac.mac_addr[1] = mac1;
  seen_mac.mac_addr[2] = mac2;
  seen_mac.mac_addr[3] = mac3;
  seen_mac.mac_addr[4] = mac4;
  seen_mac.mac_addr[5] = mac5;
  seen_mac.timestamp = timerReadMilis(uptime_timer);
  for (i = 0; i < mac_list.size(); i++) {
    mac_list_item_t curr = mac_list.get(i);
    if (curr.mac_addr[0] == mac0 && curr.mac_addr[1] == mac1 && curr.mac_addr[2] == mac2 && 
      curr.mac_addr[3] == mac3 && curr.mac_addr[4] == mac4 && curr.mac_addr[5] == mac5) {
      mac_list.set(i, seen_mac);
      break;
    }
  }
  if (i == mac_list.size()) {
    mac_list.add(seen_mac);
  }
}

void print_seen_macs() {
  int i;
  mac_list_item_t curr;
  printf("Seen MACs as of uptime");
  Serial.print(timerReadMilis(uptime_timer));
  Serial.println(":");
  for (i = 0; i < mac_list.size(); i++) {
    curr = mac_list.get(i);
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n", curr.mac_addr[0], curr.mac_addr[1], curr.mac_addr[2], curr.mac_addr[3], curr.mac_addr[4], curr.mac_addr[5]);
  }
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

  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buff;
  const wifi_ieee80211_packet_t *ipkt = (wifi_ieee80211_packet_t *)ppkt->payload;
  const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;

  if (ppkt->rx_ctrl.rssi <= -60)
    return;

  add_mac_to_list(hdr->addr1[0], hdr->addr1[1], hdr->addr1[2], hdr->addr1[3], hdr->addr1[4], hdr->addr1[5]);
  add_mac_to_list(hdr->addr2[0], hdr->addr2[1], hdr->addr2[2], hdr->addr2[3], hdr->addr2[4], hdr->addr2[5]);
  add_mac_to_list(hdr->addr3[0], hdr->addr3[1], hdr->addr3[2], hdr->addr3[3], hdr->addr3[4], hdr->addr3[5]);

  // printf("PACKET TYPE=%s, CHAN=%02d, RSSI=%02d,"
  //   " ADDR1=%02x:%02x:%02x:%02x:%02x:%02x,"
  //   " ADDR2=%02x:%02x:%02x:%02x:%02x:%02x,"
  //   " ADDR3=%02x:%02x:%02x:%02x:%02x:%02x\n",
  //   wifi_sniffer_packet_type2str(type),
  //   ppkt->rx_ctrl.channel,
  //   ppkt->rx_ctrl.rssi,
  //   /* ADDR1 */
  //   hdr->addr1[0],hdr->addr1[1],hdr->addr1[2],
  //   hdr->addr1[3],hdr->addr1[4],hdr->addr1[5],
  //   /* ADDR2 */
  //   hdr->addr2[0],hdr->addr2[1],hdr->addr2[2],
  //   hdr->addr2[3],hdr->addr2[4],hdr->addr2[5],
  //   /* ADDR3 */
  //   hdr->addr3[0],hdr->addr3[1],hdr->addr3[2],
  //   hdr->addr3[3],hdr->addr3[4],hdr->addr3[5]
  // );
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  delay(10);
  timer_init();
  delay(100);
  wifi_sniffer_init();
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
  print_seen_macs();
  channel = (channel % WIFI_CHANNEL_MAX) + 5;
}