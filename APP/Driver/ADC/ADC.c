#include "ADC.h"

#define ADC_VREF        (3.3f)    /* 参考电压 (V) */
#define ADC_FULL_SCALE  (4095.0f) /* 12位 ADC 满量程 */
#define PT100_RREF      (1000.0f)

void ADC_port_init(void)
{
	rcu_periph_clock_enable(RCU_GPIOC);   // GPIOC时钟使能
	rcu_periph_clock_enable(RCU_ADC0);    // 使能ADC时钟
	
	// gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_2);   // 配置PC0为模拟输入
	gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_0);   // 配置PC0为模拟输入
    
    gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_1);
    
    gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_2);
	
	adc_clock_config(ADC_ADCCK_PCLK2_DIV8);   // adc时钟配置
	
	ADC_Init();  // ADC配置
	
	

}


void ADC_Init(void)
{
    adc_deinit();    // 复位ADC
	
    adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);    	// 使能连续转换模式
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);   			// 数据右对齐 
    adc_channel_length_config(ADC0, ADC_ROUTINE_CHANNEL, 1);  			// 通道配置，规则组


    adc_end_of_conversion_config(ADC0,ADC_EOC_SET_CONVERSION);       //EOC在单子转换完成后置位
    
    adc_external_trigger_config(ADC0, ADC_ROUTINE_CHANNEL, EXTERNAL_TRIGGER_DISABLE);   		  // 禁用外部触发    
    
    adc_enable(ADC0);   		// 使能ADC接口
	
    delay_1ms(1);  				// 等待1ms

    adc_calibration_enable(ADC0);    // ADC校准和复位ADC校准
}

/*单次软件触发*/
static uint16_t adc_single_read(uint8_t channel)
{
    
    adc_routine_channel_config(ADC0, 0, channel, ADC_SAMPLETIME_56); // 重新配置规则组通道（规则组长度固定为1） 
 
   
    adc_software_trigger_enable(ADC0, ADC_ROUTINE_CHANNEL);          // 软件触发一次转换 
 
  
    uint32_t timeout = 100000;
    while(SET != adc_flag_get(ADC0, ADC_FLAG_EOC))                  //等待 EOC（转换完成标志）
    {                                                               //超时返回
        if(--timeout == 0) return 0;  
    }
 
    return adc_routine_data_read(ADC0);                              //通过都读寄存器操作清除标志位     
}

float drv_adc_read_ch0(void)
{
    uint16_t raw = adc_single_read(ADC_CHANNEL_10);
    return (float)raw * ADC_VREF / ADC_FULL_SCALE;
}

float drv_adc_read_ch1(void)
{
    uint16_t raw = adc_single_read(ADC_CHANNEL_11);
    return (float)raw * ADC_VREF / ADC_FULL_SCALE;
}

float drv_pt100_read_temp(void)
{
    uint16_t raw = adc_single_read(ADC_CHANNEL_12);
    float vadc = (float)raw * ADC_VREF / ADC_FULL_SCALE;
 
    /* 防止除零：Vadc 不应等于 Vref */
    if(vadc >= ADC_VREF) {
        return -273.15f;  /* 异常返回绝对零度，上层可检测 */
    }
 
    /* 由电压反推 PT100 阻值 */
    float r_pt100 = PT100_RREF * vadc / (ADC_VREF - vadc);
 
    /* PT100 线性近似：T = (R - R0) / alpha
     * R0 = 100Ω（0°C），alpha = 0.3851 Ω/°C
     * 工程精度：-50~150°C 误差 < 1°C */
    float temperature = (r_pt100 - 100.0f) / 0.3851f;
 
    return temperature;
}
