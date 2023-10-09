#include "drv_uart.h"
#include "rtos_types.h"

#define UART_RX             0    /* In: Receive buffer */
#define UART_TX             0    /* Out: Transmit buffer */

#define UART_DLL            0    /* Out: Divisor Latch Low */
#define UART_DLM            1    /* Out: Divisor Latch High */

#define UART_IER            1    /* Out: Interrupt Enable Register */
#define UART_IER_RDI        0x01 /* Enable receiver data interrupt */

#define UART_SSR            0x22 /* In: Software Reset Register */
#define UART_USR            0x1f /* UART Status Register */

#define UART_LCR            3    /* Out: Line Control Register */
#define UART_LCR_DLAB       0x80 /* Divisor latch access bit */
#define UART_LCR_SPAR       0x20 /* Stick parity (?) */
#define UART_LCR_PARITY     0x8  /* Parity Enable */
#define UART_LCR_STOP       0x4  /* Stop bits: 0=1 bit, 1=2 bits */
#define UART_LCR_WLEN8      0x3  /* Wordlength: 8 bits */

#define UART_MCR            4    /* Out: Modem Control Register */
#define UART_MCR_RTS        0x02 /* RTS complement */

#define UART_LSR            5    /* In: Line Status Register */
#define UART_LSR_BI         0x10 /* Break interrupt indicator */
#define UART_LSR_DR         0x01 /* Receiver data ready */

#define UART_IIR            2    /* In: Interrupt ID Register */
#define UART_IIR_NO_INT     0x01 /* No interrupts pending */
#define UART_IIR_BUSY       0x07 /* DesignWare APB Busy Detect */
#define UART_IIR_RX_TIMEOUT 0x0c /* OMAP RX Timeout interrupt */

#define UART_FCR            2    /* Out: FIFO Control Register */
#define UART_FCR_EN_FIFO    0x01 /* Enable the FIFO */
#define UART_FCR_CLEAR_RCVR 0x02 /* Clear the RCVR FIFO */
#define UART_FCR_CLEAR_XMIT 0x04 /* Clear the XMIT FIFO */

static inline uint32_t dw8250_read32(uint32_t addr, uint32_t offset)
{
    return *((volatile uint32_t *)(addr + (offset << UART_REG_SHIFT)));
}

static inline  void dw8250_write32(uint32_t addr, uint32_t offset, uint32_t value)
{
    *((volatile uint32_t *)(addr + (offset << UART_REG_SHIFT))) = value;

    if (offset == UART_LCR)
    {
        int tries = 1000;

        /* Make sure LCR write wasn't ignored */
        while (tries--)
        {
            unsigned int lcr = dw8250_read32(addr, UART_LCR);

            if ((value & ~UART_LCR_SPAR) == (lcr & ~UART_LCR_SPAR))
            {
                return;
            }

            dw8250_write32(addr, UART_FCR, UART_FCR_EN_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
            dw8250_read32(addr, UART_RX);

            *((volatile uint32_t *)(addr + (offset << UART_REG_SHIFT))) = value;
        }
    }
}

int dw8250_uart_init()
{
    uint32_t base, rate;

    base = UART4_BASE;

    /* Resset UART */
    dw8250_write32(base, UART_SSR, 1);
    dw8250_write32(base, UART_SSR, 0);

    dw8250_write32(base, UART_IER, !UART_IER_RDI);
    dw8250_write32(base, UART_FCR, UART_FCR_EN_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);

    /* Disable flow ctrl */
    dw8250_write32(base, UART_MCR, 0);
    /* Clear RTS */
    dw8250_write32(base, UART_MCR, dw8250_read32(base, UART_MCR) | UART_MCR_RTS);

    rate = UART_INPUT_CLK / 16 / 115200;

    /* Enable access DLL & DLH */
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) | UART_LCR_DLAB);
    dw8250_write32(base, UART_DLL, (rate & 0xff));
    dw8250_write32(base, UART_DLM, (rate & 0xff00) >> 8);
    /* Clear DLAB bit */
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) & (~UART_LCR_DLAB));

    dw8250_write32(base, UART_LCR, (dw8250_read32(base, UART_LCR) & (~UART_LCR_WLEN8)) | UART_LCR_WLEN8);
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) & (~UART_LCR_STOP));
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) & (~UART_LCR_PARITY));

    dw8250_write32(base, UART_IER, UART_IER_RDI);

    return 0;
}

int dw8250_uart_putc(char c)
{
    uint32_t base;
    base = UART4_BASE;
    while ((dw8250_read32(base, UART_USR) & 0x2) == 0)
    {
    }

    dw8250_write32(base, UART_TX, c);

    return 0;
}