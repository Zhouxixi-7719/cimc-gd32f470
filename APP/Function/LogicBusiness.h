#ifndef __LOGICBUSINESS_H__
#define __LOGICBUSINESS_H__

#include "HeaderFiles.h"

#define DEV_ID_DEFAULT          0x0001U         /*队伍ID初始值*/

/*波特率映射*/
#define BAUD_CODE_4800          0x11U
#define BAUD_CODE_9600          0x12U
#define BAUD_CODE_19200         0x13U
#define BAUD_CODE_115200        0x14U
#define BAUD_CODE_DEFAULT       BAUD_CODE_19200 /*出场默认值*/

/*固件版本  初始版本为2.0.1.0*/
#define FW_VER_0                0x02U
#define FW_VER_1                0x00U
#define FW_VER_2                0x01U
#define FW_VER_3                0x00U

/*初始化，全局参数恢复默认值*/
void function_Init(void);

/*读取当前波特率码的映射*/
uint8_t function_current_baud_code(void);

/*返回波特率码实际数值*/
uint32_t baud_code_to_value(uint8_t code);


void fn_system_rebort(void);
uint8_t fn_get_fw_version(uint8_t* out);
void fn_set_time(const uint8_t *utc4);
uint8_t fn_get_time(uint8_t* out);
int fn_set_dev_id(uint16_t new_id);
uint16_t fn_get_dev_id(void);
void fn_set_baud(uint8_t code);
uint8_t fn_get_baud(void);


void float_to_be(float f, uint8_t *out);

float be_to_float(const uint8_t *in);

uint8_t fn_read_ch0(uint8_t *out);

uint8_t fn_read_ch1(uint8_t *out);

uint8_t fn_read_ch2(uint8_t *out);

/* 0x0241 设置 CH0 变比*/
void fn_set_ratio_ch0(const uint8_t *f4);

/* 0x0242 设置 CH1 变比 */
void fn_set_ratio_ch1(const uint8_t *f4);

/* 0x0261 设置上报间隔*/
void fn_set_report_interval(uint8_t code);

/*  供自动上报(H模块)使用的辅助函数 */
uint32_t fn_get_report_interval_ms(void);   

float fn_get_ratio_ch0(void);
float fn_get_ratio_ch1(void);
    
void fn_set_dac(uint16_t value);


#endif

