#include "ESP8266WiFi.h"
extern "C" {
#include "user_interface.h"
}
#include "network_80211.h"

// expand int[6] to argument list (for snprintf)
#define args6(a) a[0], a[1], a[2], a[3], a[4], a[5]

void handle_pkt(uint8_t *buf, uint16 len) {
  char ssid_buf[32];
  lpframectrl_80211 framectrl;
  if (len < 64) return;

  buf += sizeof(struct RxControl);
  struct probe_request_80211 *probe_buf = (struct probe_request_80211*) buf;

  if (FRAME_TYPE_MANAGEMENT == probe_buf->framectrl.Type) {

    /* Management frame */
    if (FRAME_SUBTYPE_PROBE_REQUEST == probe_buf->framectrl.Subtype) {
      uint8* tsaddr = probe_buf->tsaddr;

      char srcaddr[18];
      snprintf(srcaddr, sizeof(srcaddr), "%02x:%02x:%02x:%02x:%02x:%02x", args6(tsaddr));

      /* Probe Request */
      ptagged_parameter tag = (ptagged_parameter)(buf + sizeof(probe_request));

      if (tag->tag_length != 0) {
        os_memset(ssid_buf, 0, 32);
        os_memcpy(ssid_buf, (uint8_t *)tag + 2, tag->tag_length);

        char logbuf[80];
        snprintf(logbuf, sizeof(logbuf), "Probe request from %s for %s", srcaddr, ssid_buf);
        Serial.println(logbuf);
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  delay(500);
  wifi_set_opmode(WIFI_STA);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(handle_pkt);
}

void loop() {  }
