#define FRAME_TYPE_MANAGEMENT 0
#define FRAME_TYPE_CONTROL 1
#define FRAME_TYPE_DATA 2
#define FRAME_SUBTYPE_PROBE_REQUEST 0x04
#define FRAME_SUBTYPE_PROBE_RESPONSE 0x05
#define FRAME_SUBTYPE_BEACON 0x08
#define FRAME_SUBTYPE_AUTH 0x0b
#define FRAME_SUBTYPE_DEAUTH 0x0c
#define FRAME_SUBTYPE_DATA 0x14
typedef struct framectrl_80211
{
    //buf[0]
    u8 Protocol:2;
    u8 Type:2;
    u8 Subtype:4;
    //buf[1]
    u8 ToDS:1;
    u8 FromDS:1;
    u8 MoreFlag:1;
    u8 Retry:1;
    u8 PwrMgmt:1;
    u8 MoreData:1;
    u8 Protectedframe:1;
    u8 Order:1;
} framectrl_80211,*lpframectrl_80211;

typedef struct probe_request_80211
{
  struct framectrl_80211 framectrl;
  uint16 duration;
  uint8 rdaddr[6];
  uint8 tsaddr[6];
  uint8 bssid[6];
  uint16 number;
} probe_request, *pprobe_request;

typedef struct beacon_frame_80211
{
    struct framectrl_80211 framectrl;
    uint8 timestamp[8];
    uint16 dtim;
    uint16 capability; 
} beacon_frame, *pbeacon_frame;

typedef struct tagged_parameter
{
  /* SSID parameter */
  uint8 tag_number;
  uint8 tag_length;
} tagged_parameter, *ptagged_parameter;

struct RxControl {
    signed rssi:8;//��ʾ�ð����ź�ǿ��
    unsigned rate:4;
    unsigned is_group:1;
    unsigned:1;
    unsigned sig_mode:2;//��ʾ�ð��Ƿ���11n�İ���0��ʾ��11n����0��ʾ11n
    unsigned legacy_length:12;//��������11n�İ�������ʾ���ĳ���
    unsigned damatch0:1;
    unsigned damatch1:1;
    unsigned bssidmatch0:1;
    unsigned bssidmatch1:1;
    unsigned MCS:7;//������11n�İ�������ʾ���ĵ��Ʊ������У���Чֵ��0-76
    unsigned CWB:1;//������11n�İ�������ʾ�Ƿ�ΪHT40�İ�
    unsigned HT_length:16;//������11n�İ�������ʾ���ĳ���
    unsigned Smoothing:1;
    unsigned Not_Sounding:1;
    unsigned:1;
    unsigned Aggregation:1;
    unsigned STBC:2;
    unsigned FEC_CODING:1;//������11n�İ�������ʾ�Ƿ�ΪLDPC�İ�
    unsigned SGI:1;
    unsigned rxend_state:8;
    unsigned ampdu_cnt:8;
    unsigned channel:4;//��ʾ�ð����ڵ��ŵ�
    unsigned:12;
};

struct sniffer_buf{
  struct RxControl rx_ctrl;
  u8 buf[48];//����ieee80211��ͷ
  u16 cnt;//���ĸ���
  u16 len[1];//���ĳ���
};

