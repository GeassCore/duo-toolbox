#include "csr.h"
#include "pinctrl-duo.h"
#include "drv_uart.h"

#define FW_JUMP_ADDR 0x83f40000

static inline uint64_t counter(void)
{
	uint64_t cnt;
	 __asm__ __volatile__("csrr %0, time\n" : "=r"(cnt) :: "memory");
	return cnt;
}

static void sdelay(unsigned long us)
{
	uint64_t t1 = counter();
	uint64_t t2 = t1 + us * 24;
	do {
		t1 = counter();
	} while(t2 >= t1);
}

static void board_pinmux_config(void)
{
    PINMUX_CONFIG(SD1_GPIO1, UART4_TX);
    PINMUX_CONFIG(SD1_GPIO0, UART4_RX);
}

static void sys_clock_init(void)
{
    //mmio_write_32(0x30020a8, 0x70109);
}

static void sys_jtag_init(void)
{
    PINMUX_CONFIG(UART0_TX, JTAG_TMS);
    PINMUX_CONFIG(UART0_RX, JTAG_TCK);
    PINMUX_CONFIG(IIC0_SCL, JTAG_TDI);
    PINMUX_CONFIG(IIC0_SDA, JTAG_TDO);
}

static void sys_led_ctrl(uint32_t sw)
{
    uint32_t val = 0;
    val = mmio_read_32(0x03020004);
    val |= ( (sw & 0x1) << 15);
    mmio_write_32(0x03020004, val);
    val = mmio_read_32(0x03020000);
    val |= ( (sw & 0x1) << 15);
    mmio_write_32(0x03020000, val);
}

void start_kernel(void)
{
    uint32_t sw = 0;
    sys_clock_init();
    board_pinmux_config();

    dw8250_uart_init();
    dw8250_uart_putc('h');
    dw8250_uart_putc('e');
    dw8250_uart_putc('h');
    dw8250_uart_putc('e');
    sys_led_ctrl(1);
    sys_jtag_init();

    while (1)
    {
        sdelay(1000000);
        sw =!sw;
        sys_led_ctrl(sw);
        dw8250_uart_putc('a'+ sw);
    }


    void (*entry)() = (void *)0x80210000;
    entry();
}

