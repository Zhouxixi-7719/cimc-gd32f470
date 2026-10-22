#include "LogicBusiness.h"

static uint16_t g_dev_id    = DEV_ID_DEFAULT;
static uint8_t  g_baud_code = BAUD_CODE_DEFAULT;
static uint32_t g_utc_time  = 0;

static float   g_ratio_ch0   = 1.0f;   /* CH0 变比,默认 1.0 */
static float   g_ratio_ch1   = 1.0f;   /* CH1 变比,默认 1.0 */
static uint8_t g_report_code = 0x01;   /* 上报间隔:01=1s,02=3s,03=5s */

extern float drv_adc_read_ch0(void);
extern float drv_adc_read_ch1(void);
extern float drv_pt100_read_temp(void);
extern void my_dac_set(uint16_t value);

void function_Init(void)
{
    /*初始化:直接使用默认值*/
    g_dev_id    = DEV_ID_DEFAULT;
    g_baud_code = BAUD_CODE_DEFAULT;
    g_utc_time  = 0;
}

uint8_t function_current_baud_code(void)
{
    return g_baud_code;
}

uint32_t baud_code_to_value(uint8_t code)
{
    switch(code)
    {
        case BAUD_CODE_4800:    return 4800U;
        case BAUD_CODE_9600:    return 9600U;
        case BAUD_CODE_19200:   return 19200U;
        case BAUD_CODE_115200:  return 115200U;
        default:                return 19200U;  /*若传回非法值，则返回默认波特率*/
    }
}


/*设备重启*/
void fn_system_rebort(void)
{
    for(volatile uint32_t i = 0;i < 200000;i++) {}
    /*为了防止OK没发出，保险起见，让系统死等*/
    NVIC_SystemReset();    
}

/*查询固件版本*/
uint8_t fn_get_fw_version(uint8_t* out)
{
    out[0] = FW_VER_0;
    out[1] = FW_VER_1;
    out[2] = FW_VER_2;
    out[3] = FW_VER_3;
    return 4;
}

/*设置设备时间*/
void fn_set_time(const uint8_t *utc4)
{
    g_utc_time = ((uint32_t)utc4[0] << 24) | ((uint32_t)utc4[1] << 16) | ((uint32_t)utc4[2] << 8) | ((uint32_t)utc4[3]);      
}

/*查询设备时间*/
uint8_t fn_get_time(uint8_t* out)
{
    out[0] = (uint8_t)(g_utc_time >> 24);
    out[1] = (uint8_t)(g_utc_time >> 16);
    out[2] = (uint8_t)(g_utc_time >> 8);
    out[3] = (uint8_t)(g_utc_time);
    return 4;
}

/*设置设备ID*/
int fn_set_dev_id(uint16_t new_id)
{
    /*0001~FFFE*/
    if(new_id >= 0x0001U && new_id <= 0xFFFEU)
    {
        g_dev_id = new_id;
        return 1;
    }
    return 0;    /*超出范围不应答*/
}

/*查询设备ID*/
uint16_t fn_get_dev_id(void)
{
    return g_dev_id;
}

/*设置波特率*/
void fn_set_baud(uint8_t code)
{
    if(code == BAUD_CODE_4800 || code == BAUD_CODE_9600 || code == BAUD_CODE_19200 || code == BAUD_CODE_115200)
    {
        g_baud_code = code;
    }
}


/*查询波特率*/
uint8_t fn_get_baud(void)
{
    return g_baud_code;
}



void float_to_be(float f, uint8_t *out)
{
    uint8_t le[4];
    memcpy(le, &f, 4);
    out[0] = le[3]; out[1] = le[2]; out[2] = le[1]; out[3] = le[0];
}


float be_to_float(const uint8_t *in)
{
    uint8_t le[4];
    le[0] = in[3]; le[1] = in[2]; le[2] = in[1]; le[3] = in[0];
    float f; memcpy(&f, le, 4); return f;
}

uint8_t fn_read_ch0(uint8_t *out)
{
    float val = drv_adc_read_ch0() * g_ratio_ch0;
    float_to_be(val, out);
    return 4;
}

uint8_t fn_read_ch1(uint8_t *out)
{
    float val = drv_adc_read_ch1() * g_ratio_ch1;
    float_to_be(val, out);
    return 4;
}

uint8_t fn_read_ch2(uint8_t *out)
{
    float temp = drv_pt100_read_temp();
    float_to_be(temp, out);
    return 4;
}

/* 0x0241 设置 CH0 变比*/
void fn_set_ratio_ch0(const uint8_t *f4)
{
    g_ratio_ch0 = be_to_float(f4);
    /* [TODO-FLASH] flash_write_param(PARAM_RATIO_CH0, g_ratio_ch0); */
}

/* 0x0242 设置 CH1 变比 */
void fn_set_ratio_ch1(const uint8_t *f4)
{
    g_ratio_ch1 = be_to_float(f4);
    /* [TODO-FLASH] flash_write_param(PARAM_RATIO_CH1, g_ratio_ch1); */
}

/* 0x0261 设置上报间隔*/
void fn_set_report_interval(uint8_t code)
{
    if (code == 0x01 || code == 0x02 || code == 0x03) {
        g_report_code = code;
    }
}

/*  供自动上报(H模块)使用的辅助函数 */
uint32_t fn_get_report_interval_ms(void)   /* 间隔码 -> 毫秒 */
{
    switch (g_report_code) {
        case 0x01: return 1000U;
        case 0x02: return 3000U;
        case 0x03: return 5000U;
        default:   return 1000U;
    }
}

float fn_get_ratio_ch0(void) { return g_ratio_ch0; }  /* 变比读取,统一数据源 */
float fn_get_ratio_ch1(void) { return g_ratio_ch1; }

void fn_set_dac(uint16_t value)
{
    my_dac_set(value);
}

