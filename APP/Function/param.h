//#ifndef __PARAM_H__
//#define __PARAM_H__

//#include "HeaderFiles.h"

///* 参数区地址(0x08010000~0x08010FFF) */
//#define PARAM_FLASH_ADDR   0x08010000U
//#define PARAM_MAGIC        0x50415241U   /* "PARA" 标志,判断Flash是否已初始化 */

///* 默认值 */
//#define DEV_ID_DEFAULT     0x0001U

///* 所有需持久化的参数,打包成一个结构体整体读写 */
//typedef struct {
//    uint32_t magic;        /* 标志位:等于 PARAM_MAGIC 表示Flash里有有效数据 */
//    uint16_t dev_id;
//    uint8_t  baud_code;
//    uint8_t  _pad;         /* 对齐填充 */
//    float    ratio_ch0;
//    float    ratio_ch1;
//    float    thresh_ch0;
//    float    thresh_ch1;
//    uint16_t crc;          /* 对前面所有字节(不含crc自身)的CRC16校验 */
//    uint16_t _pad2;        /* 4字节对齐 */
//} sys_param_t;

///* 全局参数实例(RAM中的工作副本) */
//extern sys_param_t g_param;

///* 开机调用:从Flash读回。 */
//void param_load(void);

///* 把当前 g_param 保存到Flash(擦扇区+写回) */
//void param_save(void);

///* 恢复默认值(写进g_param,不自动存Flash) */
//void param_set_default(void);

//#endif
