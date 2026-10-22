#include "DAC.h"

void my_dac_init(void)
{
    /* enable GPIOA clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* enable DAC clock */
    rcu_periph_clock_enable(RCU_DAC);

    /* configure PA4 as DAC output */
    gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_4);

    /* initialize DAC */
    dac_deinit(DAC0);
    /* DAC trigger config */
    dac_trigger_source_config(DAC0, DAC_OUT0, DAC_TRIGGER_SOFTWARE);
    /* DAC trigger enable */
    dac_trigger_enable(DAC0, DAC_OUT0);
    /* DAC wave mode config */
    dac_wave_mode_config(DAC0, DAC_OUT0, DAC_WAVE_DISABLE);
    /* DAC output buffer config */
    dac_output_buffer_enable(DAC0, DAC_OUT0);

    /* DAC enable */
    dac_enable(DAC0, DAC_OUT0);
}

void my_dac_set(uint16_t value)
{
    if (value > 4095) value = 4095;
    dac_data_set(DAC0, DAC_OUT0, DAC_ALIGN_12B_R, value);
    dac_software_trigger_enable(DAC0, DAC_OUT0);
}


