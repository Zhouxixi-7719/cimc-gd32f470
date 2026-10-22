#include "HeaderFiles.h"

char Team_ID[] = "2026341610";
extern uint8_t recv_flag;
extern  uint32_t g_ms_tick;
extern uint8_t recv_real_buf[];
extern uint16_t recv_real_len;
static proto_ctx_t ctx;
uint8_t DataSend[256];


void System_Init(void)
{
    systick_config();     // 时钟配置
	OLED_Init();          
    LED_Init();
    usart_init();
    extern uint16_t fn_get_dev_id(void);
    ADC_port_init();
    my_dac_init();
    my_dac_init();
    my_dac_set(2048);   // 中间值,约 1.65V
}


void UsrFunction(void)
{
	
//    uint8_t test_frame[] = {0xA5, 0xB6, 0x00, 0x01, 0x05, 0x88};
    ctx.pre_id         = fn_get_dev_id();;   
    ctx.auto_reporting = 0;    
    char hb[PROTO_MAX_ASCII+1];
    size_t n = Proto_Pack_HeartBate(ctx.pre_id,hb);
    usart_send_str((uint8_t*)hb, n);
    
	while(1)
	{
        OLED_ShowString(0,0,(u8*)Team_ID,16);
        OLED_Refresh();
		
		if(g_ms_tick >= 500)
        {
            g_ms_tick = 0;
//            RS485_SendData((uint8_t*)test_frame,sizeof(test_frame));

        }
        
        if(recv_flag)
        {    
            size_t olen = 0;         
            recv_flag = 0; 
            char out[PROTO_MAX_ASCII+1];
            proto_dispatch((const char*)recv_real_buf, recv_real_len, &ctx, out, &olen);
            if (olen > 0) usart_send_str((uint8_t*)out,olen);
        }
        
	}
}



