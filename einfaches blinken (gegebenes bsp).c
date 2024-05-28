```
// SPDX-FileCopyrightText: 2022-2023 Cesanta Software Limited
// SPDX-License-Identifier: MIT

#include <stdbool.h>
#include <stdint.h>

#define LED_PIN_1 2



#define BIT(x) ((uint32_t) 1U << (x))		//erstellt bitmaske (Bit(2)->000010) 
#define REG(x) ((volatile uint32_t *) (x))	//macht aus adresse einen zeiger auf int32

#define C3_SYSTEM 0x600c0000
#define C3_SENSITIVE 0x600c1000
#define C3_INTERRUPT 0x600c2000
#define C3_EXTMEM 0x600c4000
#define C3_MMU_TABLE 0x600c5000
#define C3_AES 0x6003a000
#define C3_SHA 0x6003b000
#define C3_RSA 0x6003c000
#define C3_HMAC 0x6003e000
#define C3_DIGITAL_SIGNATURE 0x6003d000
#define C3_GDMA 0x6003f000
#define C3_ASSIST_DEBUG 0x600ce000
#define C3_DEDICATED_GPIO 0x600cf000
#define C3_WORLD_CNTL 0x600d0000
#define C3_DPORT_END 0x600d3FFC
#define C3_UART 0x60000000
#define C3_SPI1 0x60002000
#define C3_SPI0 0x60003000
#define C3_GPIO 0x60004000
#define C3_FE2 0x60005000
#define C3_FE 0x60006000
#define C3_RTCCNTL 0x60008000
#define C3_IO_MUX 0x60009000
#define C3_RTC_I2C 0x6000e000
#define C3_UART1 0x60010000
#define C3_I2C_EXT 0x60013000
#define C3_UHCI0 0x60014000
#define C3_RMT 0x60016000
#define C3_LEDC 0x60019000
#define C3_EFUSE 0x60008800
#define C3_NRX 0x6001CC00
#define C3_BB 0x6001D000
#define C3_TIMERGROUP0 0x6001F000
#define C3_TIMERGROUP1 0x60020000
#define C3_SYSTIMER 0x60023000
#define C3_SPI2 0x60024000
#define C3_SYSCON 0x60026000
#define C3_APB_CTRL 0x60026000
#define C3_TWAI 0x6002B000
#define C3_I2S0 0x6002D000
#define C3_APB_SARADC 0x60040000
#define C3_AES_XTS 0x600CC000

struct gpio {  // 5.14 (incomplete)			// definiert die structur eines gpios
  volatile uint32_t BT_SELECT, OUT, OUT_W1TS, OUT_W1TC, RESERVED0[4], ENABLE, ENABLE_W1TS,
      ENABLE_W1TC, RESERVED1[3], STRAP, IN, RESERVED2[1], STATUS, STATUS_W1TS, STATUS_W1TC,
      RESERVED3[3], PCPU_INT, PCPU_NMI_INT,
      // TODO(cpq): complete next
      STATUS_NEXT, PIN[22], FUNC_IN[128], FUNC_OUT[22], DATE, CLOCK_GATE;
};
#define GPIO ((struct gpio *) C3_GPIO)  // wennn aufgerufen wird -> wandelt C3_GPIO in eins von den definierten structuren um

enum { GPIO_OUT_EN = 8, GPIO_OUT_FUNC = 341, GPIO_IN_FUNC = 85 };		// definiert die werte die festlegen was ein pin macht

static inline void gpio_output_enable(int pin, bool enable) {			// setzt high / low
  GPIO->ENABLE &= ~BIT(pin);							//es wird in die def. structur gebracht -> Enable und negation von bitmaske werden bitwise & verknüpft 
  GPIO->ENABLE |= (enable ? 1U : 0U) << pin;					//es wird in die def. structur gebracht -> Enable und wahrheitswert von pinstate werden  verknüoft und um pin nach links verschoben
  // SETBITS(GPIO->ENABLE, BIT(pin), (enable ? BIT(pin) : 0U));
}

static inline void gpio_output(int pin) {
  REG(C3_GPIO)[GPIO_OUT_FUNC + pin] = BIT(9) | 128;  // Simple out, TRM 5.5.3	//es wird ein zeiger aus C3_GPIO gemacht der als out_funt konfiguriert wird (+pinoffset) und die flags an bit 9 und 128 bekommt
  gpio_output_enable(pin, 1);							// pin wird enabled										
}

static inline void gpio_toggle(int pin) {					//bitwise xor verknüpftes Out und bit an stelle vom pin 
  GPIO->OUT ^= BIT(pin);
}

int main(void) {
  gpio_output(LED_PIN_1);

  for (;;) {
    volatile int i = 0;
    for(; i < 1000000; ++i) ;
    gpio_toggle(LED_PIN_1);
    
  }

  return 0;
}
```