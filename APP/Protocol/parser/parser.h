#ifndef __PARSER_H__
#define __PARSER_H__

#include "HeaderFiles.h"

#define PROTO_HEAD          0xA5B6U     /*开始标志*/
#define PROTO_TAIL          0xB6A5U     /*结束标志*/
#define PROTO_VERSION       0x02U       /*固件版本*/
#define PROTO_ADDR_BROADCAST 0xFFFFU     /*广播地址*/

#define FT_CMD              0x01U       /*命令下发帧*/
#define FT_ACK              0x02U       /*应答帧*/
#define FT_HEARTBEAT        0x05U       /*心跳帧*/
#define FT_ERROR            0xFFU       /*异常警报、错误应答帧*/
#define ACK_OK              0xFFU       /*设备回复OK*/

#define CMD_HEARTBEAT       0x8888U     /*设备心跳/上电通知帧*/
#define CMD_FIND_DEVICE     0xFFFFU     /*上位机广播寻找设备*/
#define CMD_ERROR           0xEEEEU     /*错误应答（异常状态指示）*/

#define PROTO_MAX_CONTENT 64            /*单帧内容最大字节数*/
#define PROTO_MAX_FRAME   (13 + PROTO_MAX_CONTENT)      /*一个命令帧的最大字节数*/
#define PROTO_MAX_ASCII   (PROTO_MAX_FRAME * 2)         /*ASCII码每节占两个字符*/

/*帧结构*/
typedef struct 
{
    uint16_t head;                      /*PROTO_HEAD*/
    uint16_t id;                        /*设备iD*/
    uint8_t  frame_type;                /*帧类型*/
    uint16_t cmd;                       /*命令字*/
    uint8_t  len;                       /*报文长度*/
    uint8_t  version;                   /*固件版本*/
    uint8_t  content[PROTO_MAX_CONTENT];/*内容字段*/
    uint16_t crc;                       /*CRC*/
    uint16_t tail;                      /*PROTO_TAIL*/
} proto_frame_t;

/*解析码，用于解析之后返回给命令分发处*/
typedef enum 
{
    PR_OK = 0,                          /*帧合法*/
    PR_ERR_FORMAT,                      /*找不到帧头帧尾，ASCII字符长度错误*/
    PR_ERR_CRC,                         /*CRC错误帧*/
    PR_ERR_LEN,                         /*长度错误帧*/
    PR_ERR_TAIL,                        /*帧尾错误*/
    PR_ERR_ADDR,                        /*广播ID不匹配*/
} proto_result_t;


/*设备运行时所需上下文*/
typedef struct
{
    uint16_t pre_id;                    /*设备当前ID*/
    uint8_t  auto_reporting;            /*设备是否处于自动上报状态*/
}proto_ctx_t;

/*命令字*/
#define CMD_REBOOT          0x0101U     /*设备重启*/
//#define CMD_RESTORE_SETTING 0x0102U    /*恢复出产设置*/
//#define CMD_QUERY_INFO      0x0103U    /*查询设备信息*/
#define CMD_QUERY_VER       0x0104U     /*查询固件版本*/
#define CMD_SET_TIME        0x0105U     /*设置设备时间*/
#define CMD_GET_TIME        0x0106U     /*查询设备时间*/
#define CMD_SET_ID          0x01A1U     /*设置设备ID*/
#define CMD_SET_BAUD        0x01A2U     /*设置波特率*/
#define CMD_GET_ID          0x0111U     /*查询设备ID*/
#define CMD_GET_BAUD        0x0112U     /*查询波特率*/
#define CMD_GET_CH0         0x0201U     /*查询CH0数据*/
#define CMD_GET_CH1         0x0202U     /*查询CH1数据(ADC通道0：滑动变阻器)*/
#define CMD_GET_CH2         0x0221U     /*查询特定通道数据(PT100)*/
#define CMD_SET_RATIO_CH0   0x0241U     /*设置CH0变比*/
#define CMD_SET_RATIO_CH1   0x0242U     /*设置CH1变比*/
#define CMD_SET_INTERVAL    0x0261U     /*设置数据上报时间间隔*/
#define CMD_SET_DAC         0x0301U     /*设置DAC输出电压*/
#define CMD_AUTO_START      0x0302U     /*定时自动上报数据开始*/
#define CMD_AUTO_STOP       0x0303U     /*定时自动上报数据停止*/
#define CMD_SLEEP           0x03AAU     /*进入睡眠模式*/
#define CMD_GET_THRESH_ALL  0x0400U     /*读取阈值参数（批量读取仅 CH0、CH1）*/
#define CMD_GET_THRESH_CH0  0x0401U     /*读取 CH0 阈值参数*/
#define CMD_GET_THRESH_CH1  0x0402U     /*读取 CH1 阈值参数*/
#define CMD_GET_THRESH_CH3  0x0403U     /*读取 CH2 阈值参数*/
#define CMD_SET_THRESH_CH0  0x0411U     /*写入 CH0 阈值参数*/
#define CMD_SET_THRESH_CH1  0x0412U     /*写入 CH1 阈值参数*/
#define CMD_SET_THRESH_CH2  0x0413U     /*写入 CH2 阈值参数*/
#define CMD_OTA_REQUEST     0x0501U     /*升级请求*/
#define CMD_OTA_PREPARE     0x0502U     /*准备传输固件数据包*/
#define CMD_OTA_EXECUTE     0x0503U     /*执行升级流程*/
#define CMD_ALARM_SWITCH    0x0601U     /*是否主动上报告警*/
#define CMD_ALARM_QUERY     0x0602U     /*查询告警记录*/
#define CMD_ALARM_CLEAR     0x0603U     /*查清除告警记录*/
//#define CMD_OPERA_QUERY     0x0603U     /*查询操作日志*/
//#define CMD_OPERA_CLEAR     0x0603U     /*清除操作日志*/




uint16_t CRC_16_Modbus(const uint8_t* buf,size_t len);  //CRC测验
size_t Bin_to_ASCII(const uint8_t *bin,size_t bin_len,char* out);
size_t ASCII_to_Bin(const char *ascii,size_t ascii_len,uint8_t *out);

/*整合数据帧*/
size_t frame_to_bin(uint16_t id,uint8_t frame_type,uint16_t cmd,const uint8_t* content,uint8_t len,uint8_t *bin);

/*数据帧打包为字符串*/
size_t Proto_Pack(uint16_t id,uint8_t frame_type,uint16_t cmd,const uint8_t* content,uint8_t len,char *ascii_to_out);

/*专门发送ok应答帧*/
size_t Proto_ok(uint16_t id,uint16_t cmd,char* ascii_to_out);

/*错误应答帧*/
size_t Proto_error(uint16_t id,char* ascii_to_out);

/*心跳应答帧*/
size_t Proto_Pack_HeartBate(uint16_t id,char* ascii_to_out);

/*解包*/
proto_result_t proto_unpack(const char* ascii,size_t ascii_len,proto_frame_t *frame);

/*主命令分发*/
void proto_dispatch(const char *in_ascii,size_t in_len,proto_ctx_t *ctx,char* out_ascii,size_t *out_len);


#endif

