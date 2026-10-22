//#include "param.h"

//extern void     flash_erase_param_sector(void);
//extern void     flash_write_param(const uint8_t *data, uint32_t len);
//extern void     flash_read_param(uint8_t *data, uint32_t len);
//extern uint16_t CRC_16_Modbus(const uint8_t *buf, uint32_t len);  /* 复用协议层CRC */


//void param_set_default(void)
//{
//    g_param.magic      = PARAM_MAGIC;
//    g_param.dev_id     = DEV_ID_DEFAULT;
//    g_param.baud_code  = BAUD_CODE_DEFAULT;
//    g_param._pad       = 0;
//    g_param.ratio_ch0  = 1.0f;
//    g_param.ratio_ch1  = 1.0f;
//    g_param.thresh_ch0 = 0.0f;
//    g_param.thresh_ch1 = 0.0f;
//    g_param.crc        = 0;
//    g_param._pad2      = 0;
//}

//static uint16_t param_calc_crc(void)
//{
//    uint32_t crc_offset = (uint32_t)((uint8_t*)&g_param.crc - (uint8_t*)&g_param);
//    return CRC_16_Modbus((const uint8_t*)&g_param, crc_offset);
//}

//void param_load(void)
//{
//    flash_read_param((uint8_t*)&g_param, sizeof(sys_param_t));  /* 整块读回 */

//    /* 校验:magic对 且 crc对 -> 数据有效 */
//    if (g_param.magic == PARAM_MAGIC) {
//        uint16_t saved_crc = g_param.crc;
//        uint16_t calc = param_calc_crc();
//        if (saved_crc == calc) {
//            return;   /* 有效,直接用读回的参数 */
//        }
//    }
//    /* 首次上电 或 数据损坏 -> 用默认值并写一次Flash */
//    param_set_default();
//    param_save();
//}


//void param_save(void)
//{
//    g_param.crc = param_calc_crc();          /* 先算好CRC */
//    flash_erase_param_sector();              /* 擦整扇区 */
//    flash_write_param((const uint8_t*)&g_param, sizeof(sys_param_t));  /* 整块写回 */
//}

